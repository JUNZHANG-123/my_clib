#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <signal.h>

#include "lib/bluetooth.h"
#include "lib/hci.h"
#include "lib/hci_lib.h"

#define BLE_SCAN_TIMEOUT_S          5
#define BLE_SCAN_LIST_MAX           20

#define FLAGS_AD_TYPE 0x01
#define FLAGS_LIMITED_MODE_BIT 0x01
#define FLAGS_GENERAL_MODE_BIT 0x02

#define EIR_FLAGS                   0x01  /* flags */
#define EIR_UUID16_SOME             0x02  /* 16-bit UUID, more available */
#define EIR_UUID16_ALL              0x03  /* 16-bit UUID, all listed */
#define EIR_UUID32_SOME             0x04  /* 32-bit UUID, more available */
#define EIR_UUID32_ALL              0x05  /* 32-bit UUID, all listed */
#define EIR_UUID128_SOME            0x06  /* 128-bit UUID, more available */
#define EIR_UUID128_ALL             0x07  /* 128-bit UUID, all listed */
#define EIR_NAME_SHORT              0x08  /* shortened local name */
#define EIR_NAME_COMPLETE           0x09  /* complete local name */
#define EIR_TX_POWER                0x0A  /* transmit power level */
#define EIR_DEVICE_ID               0x10  /* device ID */

typedef struct
{
    char mac[18];
    char name[30];
} pp_ble_scan_dev_info_t;

typedef struct
{
    pp_ble_scan_dev_info_t dev[BLE_SCAN_LIST_MAX];
    int index;
} pp_ble_scan_list_t;
static pp_ble_scan_list_t g_scan_list = {.index=0};

static int scan_result_find_duplicates(char *mac)
{
    for (int i = 0; i < g_scan_list.index; i++)
    {
        if (strncmp(g_scan_list.dev[i].mac, mac, 18) == 0)
        {
            return 1;
        }

        if (i == (BLE_SCAN_LIST_MAX-1) )
        {
            return -1;
        }
    }
    printf("g_scan_dev_cnt=%d\n", g_scan_list.index);
    memset(g_scan_list.dev[g_scan_list.index].mac, 0, 18);
    strncpy(g_scan_list.dev[g_scan_list.index++].mac, mac, 18);
    if (g_scan_list.index >= BLE_SCAN_LIST_MAX)
    {
        g_scan_list.index = 0;
    }
    return 0;
}

static int read_flags(uint8_t *flags, const uint8_t *data, size_t size)
{
    size_t offset;

    if (!flags || !data)
        return -EINVAL;

    offset = 0;
    while (offset < size) {
        uint8_t len = data[offset];
        uint8_t type;

        /* Check if it is the end of the significant part */
        if (len == 0)
            break;

        if (len + offset > size)
            break;

        type = data[offset + 1];

        if (type == FLAGS_AD_TYPE) {
            *flags = data[offset + 2];
            return 0;
        }

        offset += 1 + len;
    }

    return -ENOENT;
}

static int check_report_filter(uint8_t procedure, le_advertising_info *info)
{
    uint8_t flags;

    /* If no discovery procedure is set, all reports are treat as valid */
    if (procedure == 0)
        return 1;

    /* Read flags AD type value from the advertising report if it exists */
    if (read_flags(&flags, info->data, info->length))
        return 0;

    switch (procedure) {
    case 'l': /* Limited Discovery Procedure */
        if (flags & FLAGS_LIMITED_MODE_BIT)
            return 1;
        break;
    case 'g': /* General Discovery Procedure */
        if (flags & (FLAGS_LIMITED_MODE_BIT | FLAGS_GENERAL_MODE_BIT))
            return 1;
        break;
    default:
        fprintf(stderr, "Unknown discovery procedure\n");
    }

    return 0;
}

static int eir_parse_name(uint8_t *eir, size_t eir_len,
                        char *buf, size_t buf_len)
{
    size_t offset;

    offset = 0;
    while (offset < eir_len) {
        uint8_t field_len = eir[0];
        size_t name_len;

        /* Check for the end of EIR */
        if (field_len == 0)
            break;

        if (offset + field_len > eir_len)
            goto failed;

        switch (eir[1]) {
        case EIR_NAME_SHORT:
        case EIR_NAME_COMPLETE:
            name_len = field_len - 1;
            if (name_len > buf_len)
                goto failed;

            memcpy(buf, &eir[2], name_len);
            return 0;
        }

        offset += field_len + 1;
        eir += field_len + 1;
    }

failed:
    snprintf(buf, buf_len, "(unknown)");
    return -1;
}

static int print_advertising_devices(int dd, uint8_t filter_type)
{
    unsigned char buf[HCI_MAX_EVENT_SIZE], *ptr;
    struct hci_filter nf, of;
    socklen_t olen;
    int len;
    struct timeval t1, t2;
    long delta_t = 0;
    int ret = 0;

    olen = sizeof(of);
    if (getsockopt(dd, SOL_HCI, HCI_FILTER, &of, &olen) < 0) {
        printf("Could not get socket options\n");
        return -1;
    }

    hci_filter_clear(&nf);
    hci_filter_set_ptype(HCI_EVENT_PKT, &nf);
    hci_filter_set_event(EVT_LE_META_EVENT, &nf);

    if (setsockopt(dd, SOL_HCI, HCI_FILTER, &nf, sizeof(nf)) < 0) {
        printf("Could not set socket options\n");
        return -1;
    }

    gettimeofday(&t1, NULL);
    while (1) {
        evt_le_meta_event *meta;
        le_advertising_info *info;
        char addr[18];

        while ((len = read(dd, buf, sizeof(buf))) < 0) {
            if (errno == EINTR) {
                len = 0;
                goto done;
            }

            if (errno == EAGAIN || errno == EINTR)
                continue;
            goto done;
        }

        ptr = buf + (1 + HCI_EVENT_HDR_SIZE);
        len -= (1 + HCI_EVENT_HDR_SIZE);

        meta = (void *) ptr;

        if (meta->subevent != 0x02)
            goto done;

        /* Ignoring multiple reports */
        info = (le_advertising_info *) (meta->data + 1);
        if (check_report_filter(filter_type, info)) {
            char name[30];

            memset(name, 0, sizeof(name));

            ba2str(&info->bdaddr, addr);
            ret = eir_parse_name(info->data, info->length,
                            name, sizeof(name) - 1);
            if (ret == 0)
            {
                ret = scan_result_find_duplicates(addr);
                if (ret == 0)
                {
                    printf("%s %s\n", addr, name);
                }
            }
        }

        gettimeofday(&t2, NULL);
        delta_t = t2.tv_sec-t1.tv_sec;
        if (delta_t > BLE_SCAN_TIMEOUT_S)
        {
            printf("time over\n");
            len = 0;
            goto done;
        }
    }

done:
    setsockopt(dd, SOL_HCI, HCI_FILTER, &of, sizeof(of));

    if (len < 0)
        return -1;

    return 0;
}

int pp_scan_start(void)
{
    int err, opt, dd;
    uint8_t own_type = LE_PUBLIC_ADDRESS;
    uint8_t scan_type = 0x01;
    uint8_t filter_type = 0;
    uint8_t filter_policy = 0x00;           // Accept all advertisements, except directed advertisements not addressed to this device (0x00)
    uint16_t interval = htobs(0x0010);      // 16 (10 msec)
    uint16_t window = htobs(0x0010);
    uint8_t filter_dup = 0x01;              // 过滤重复

    g_scan_list.index = 0;

    int dev_id = hci_devid("hci0");

    if (dev_id < 0)
        dev_id = hci_get_route(NULL);

    dd = hci_open_dev(dev_id);
    if (dd < 0) {
        perror("Could not open device");
        goto EXIT;
    }

    err = hci_le_set_scan_parameters(dd, scan_type, interval, window,
                        own_type, filter_policy, 10000);
    if (err < 0) {
        perror("Set scan parameters failed");
        goto EXIT;
    }

    err = hci_le_set_scan_enable(dd, 0x01, filter_dup, 10000);
    if (err < 0) {
        perror("Enable scan failed");
        goto EXIT;
    }

    printf("LE Scan ...\n");

    err = print_advertising_devices(dd, filter_type);
    if (err < 0) {
        perror("Could not receive advertising events");
        goto EXIT;
    }

    err = hci_le_set_scan_enable(dd, 0x00, filter_dup, 10000);
    if (err < 0) {
        perror("Disable scan failed");
        goto EXIT;
    }

    hci_close_dev(dd);
EXIT:
    return 0;
}

