#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ipp.h"
#include "common.h"


int ippAddAttr(ipp_attribute **req_attr, char *name, 
               void **value, int values_count, 
               ipp_tag_t group_tag, ipp_tag_t value_tag)
{
    ipp_attribute *attr;
    ipp_attribute *last_attr = *req_attr;

    attr = pp_calloc(sizeof(ipp_attribute), 1);
    if (attr == NULL) {
      goto bad_addattr;
    }

    attr->name_len = strlen(name);
    attr->name = pp_malloc(attr->name_len+1);
    if (attr->name == NULL) {
      goto bad_addattr;
    }
    snprintf(&attr->name[0], attr->name_len+1, "%s", name);

    attr->value_tag  = value_tag;
    attr->group_tag = group_tag;

    attr->values_count = values_count;
    if (attr->values_count == 0) {
       return 0;
    }

    if (value[0] == NULL) {
       attr->values_count = 0;
       return 0;
    }

    attr->values = pp_calloc(sizeof(ipp_value_t), values_count);
    if (attr->values == NULL) {
       goto bad_addattr;
    }

    switch (value_tag) {
        case IPP_TAG_TEXT:
        case IPP_TAG_NAME:
        case IPP_TAG_RESERVED_STRING:
        case IPP_TAG_KEYWORD:
        case IPP_TAG_URI:
        case IPP_TAG_URISCHEME:
        case IPP_TAG_CHARSET:
        case IPP_TAG_LANGUAGE:
        case IPP_TAG_MIMETYPE:
        case IPP_TAG_DATE:
        case IPP_TAG_BEGIN_COLLECTION:
          for (values_count=0; values_count<attr->values_count; values_count++) {
             if (value[values_count] == NULL) {
                continue;
             }
             attr->values[values_count].length = strlen((char *)value[values_count]);
             attr->values[values_count].data = pp_malloc(attr->values[values_count].length+1);
             if (attr->values[values_count].data == NULL) {
               goto bad_addattr;
             }
             sprintf(attr->values[values_count].data, "%s", (char *)value[values_count]);
          }
          break;

        case IPP_TAG_BOOLEAN:
          for (values_count=0; values_count<attr->values_count; values_count++) {
             if (value[values_count] == NULL) {
                continue;
             }
             attr->values[values_count].length = 1;
             attr->values[values_count].data = pp_malloc(2);
             if (attr->values[values_count].data == NULL) {
               goto bad_addattr;
             }
             *(char *)attr->values[values_count].data = *(char *)value[values_count] & 0xFF;
          }
          break;

        case IPP_TAG_INTEGER:
        case IPP_TAG_ENUM:
        case IPP_TAG_NOVALUE:
          for (values_count=0; values_count<attr->values_count; values_count++) {
             if (value[values_count] == NULL) {
                continue;
             }
             int *integer_data = (int *)value[values_count];
             attr->values[values_count].length = 4;
             attr->values[values_count].data = pp_malloc(4);
             if (attr->values[values_count].data == NULL) {
               goto bad_addattr;
             }

             *(char *)(attr->values[values_count].data+0) = (integer_data[0] >> 24) & 0xFF;
             *(char *)(attr->values[values_count].data+1) = (integer_data[0] >> 16) & 0xFF;
             *(char *)(attr->values[values_count].data+2) = (integer_data[0] >> 8) & 0xFF;
             *(char *)(attr->values[values_count].data+3) = integer_data[0] & 0xFF;
          }
          break;

        case IPP_TAG_RANGE:
          for (values_count=0; values_count<attr->values_count; values_count++) {
              if (value[values_count] == NULL) {
                continue;
             }
             int *range = (int *)value[values_count];
             attr->values[values_count].length = 8;
             attr->values[values_count].data = (char *)pp_malloc(8);
             if (attr->values[values_count].data == NULL) {
               goto bad_addattr;
             }

             *(char *)(attr->values[values_count].data+0) = (range[0] >> 24) & 0xFF;
             *(char *)(attr->values[values_count].data+1) = (range[0] >> 16) & 0xFF;
             *(char *)(attr->values[values_count].data+2) = (range[0] >> 8) & 0xFF;
             *(char *)(attr->values[values_count].data+3) = range[0] & 0xFF;

             *(char *)(attr->values[values_count].data+4) = (range[1] >> 24) & 0xFF;
             *(char *)(attr->values[values_count].data+5) = (range[1] >> 16) & 0xFF;
             *(char *)(attr->values[values_count].data+6) = (range[1] >> 8) & 0xFF;
             *(char *)(attr->values[values_count].data+7) = range[1] & 0xFF;
          }
          break;

        case IPP_TAG_RESOLUTION:
          for (values_count=0; values_count<attr->values_count; values_count++) {
             if (value[values_count] == NULL) {
                continue;
             }
             int *resolution = (int *)value[values_count];
             attr->values[values_count].length = 9;
             attr->values[values_count].data = pp_malloc(9);
             if (attr->values[values_count].data == NULL) {
               goto bad_addattr;
             }

            *(char *)(attr->values[values_count].data+0) = (resolution[0] >> 24) & 0xFF;
            *(char *)(attr->values[values_count].data+1) = (resolution[0] >> 16) & 0xFF;
            *(char *)(attr->values[values_count].data+2) = (resolution[0] >> 8) & 0xFF;
            *(char *)(attr->values[values_count].data+3) = resolution[0] & 0xFF;

            *(char *)(attr->values[values_count].data+4) = (resolution[1] >> 24) & 0xFF;
            *(char *)(attr->values[values_count].data+5) = (resolution[1] >> 16) & 0xFF;
            *(char *)(attr->values[values_count].data+6) = (resolution[1] >> 8) & 0xFF;
            *(char *)(attr->values[values_count].data+7) = resolution[1] & 0xFF;

            *(char *)(attr->values[values_count].data+8) = resolution[2] & 0xFF;
          }
          break;

        default:
          break;
    }

    if (last_attr == NULL) {
        *req_attr = attr;
    } else {
      while (last_attr->next != NULL) {
        last_attr = last_attr->next;
      }
      last_attr->next = attr;
    }

    return 0;

bad_addattr:

    if (attr->name) {
      pp_free(attr->name);
      attr->name = NULL;
    }

    if (attr->values) {
      for (values_count=0; 
           values_count<attr->values_count; 
           values_count++) {
        if (attr->values[values_count].data) {
          pp_free(attr->values[values_count].data);
          attr->values[values_count].data = NULL;
        }
      }
      pp_free(attr->values);
      attr->values = NULL;
    }

    if (attr) {
      pp_free(attr);
      attr = NULL;
    }

    return -1;
}

void ippReleaseAttr(ipp_attribute **req_attr)
{
    ipp_attribute *attr = *req_attr;
    if (attr == NULL) {
       return;
    }

    ipp_attribute *head_attr;
    int values_count;

    do {
        head_attr = attr->next;
        if (attr != NULL) {
          if (attr->name) {
             pp_free(attr->name);
          }

          if (attr->values) {
            for (values_count=0; 
                 values_count<attr->values_count; 
                 values_count++) {
                if (attr->values[values_count].data) {
                  pp_free(attr->values[values_count].data);
                  attr->values[values_count].data = NULL;
                }
            }
            pp_free(attr->values);
            attr->values = NULL;
          }
          pp_free(attr);
        }
        attr = head_attr;
    } while (head_attr);

    *req_attr = NULL;
}

int ippAttrToRespBuff(ipp_attribute *req_attr,
              unsigned int version, unsigned int op_status, 
              unsigned int request_id, char *buf, int buff_size)
{

    int buff_count = 0;
    ipp_attribute *attr = req_attr;
    ipp_tag_t curr_group_tag = IPP_TAG_CUPS_INVALID;
    int values_count = 0;

    /* Version */
    buf[buff_count++] = (version >> 8) & 0xFF;
    buf[buff_count++] = version & 0xFF;

    /* op_status */
    buf[buff_count++] = (op_status >> 8) & 0xFF;;
    buf[buff_count++] = op_status & 0xFF;

    /* request_id */
    buf[buff_count++] = (request_id >> 8) & 0xFF;
    buf[buff_count++] = (request_id >> 8) & 0xFF;
    buf[buff_count++] = (request_id >> 8) & 0xFF;
    buf[buff_count++] = request_id & 0xFF;

    while(attr && buff_count < buff_size) {
        if (attr->group_tag == IPP_TAG_ZERO) {
           continue;
        }

        /* group_tag */
        if (attr->group_tag != curr_group_tag) {
           curr_group_tag = attr->group_tag;
           buf[buff_count++] = attr->group_tag;
        }

        /* value_tag */
        buf[buff_count++] = attr->value_tag;

        /* name_len & name */
        buf[buff_count++] = attr->name_len >> 8;
        buf[buff_count++] = attr->name_len & 0x00FF;
        for (int i=0; i<attr->name_len; i++) {
           buf[buff_count++] = attr->name[i];
        }

        /* value length & value */
        values_count = 0;
        while (1) {
           buf[buff_count++] = attr->values[values_count].length >> 8;
           buf[buff_count++] = attr->values[values_count].length & 0x00FF;
           if (attr->values[values_count].length > 0) {
              for (int i=0; i<attr->values[values_count].length; i++) {
                buf[buff_count++] = *(char *)(attr->values[values_count].data+i);
              }
           }
           values_count++;
           if (values_count >= attr->values_count) {
              break;
           }
           buf[buff_count++] = attr->value_tag;
           buf[buff_count++] = 0x00;
           buf[buff_count++] = 0x00;
        }

        if (attr->next == NULL) break;
        attr = attr->next;
    }

    buf[buff_count++] = IPP_TAG_END;

    return buff_count;
}


int ippAddBoolean(ipp_attribute **req_attr, char *name, char value, ipp_tag_t group_tag)
{
    char *buff[1];
    buff[0] = &value;
    return (ippAddAttr(req_attr, name, (void **)buff, 1, group_tag, IPP_TAG_BOOLEAN));
}

int ippAddInteger(ipp_attribute **req_attr, char *name, int value, ipp_tag_t group_tag, ipp_tag_t value_tag)
{
    int *buff[1];
    buff[0] = &value;
    return (ippAddAttr(req_attr, name, (void **)buff, 1, group_tag, value_tag));
}

int ippAddString(ipp_attribute **req_attr, char *name, void *value, ipp_tag_t group_tag, ipp_tag_t value_tag)
{
    char *buff[1];
    buff[0] = value;
    return (ippAddAttr(req_attr, name, (void **)buff, 1, group_tag, value_tag));
}

int ippAddData(ipp_attribute **req_attr, char *name, void *value, ipp_tag_t group_tag)
{
    unsigned char *buff[1];
    if (value)
      buff[0] = value;
    return (ippAddAttr(req_attr, name, (void **)buff, value ? 1 : 0, group_tag, IPP_TAG_DATE));
}

int ippAddResolution(ipp_attribute **req_attr, char *name, int xres, int yres, int uints, ipp_tag_t group_tag)
{
    int *buff[3];
    buff[0] = &xres;
    buff[1] = &yres;
    buff[2] = &uints;
    return (ippAddAttr(req_attr, name, (void **)buff, 1, group_tag, IPP_TAG_RESOLUTION));
}

int ippAddRange(ipp_attribute **req_attr, char *name, int lower, int upper, ipp_tag_t group_tag)
{
    int *buff[2];
    buff[0] = &lower;
    buff[1] = &upper;
    return (ippAddAttr(req_attr, name, (void **)buff, 1, group_tag, IPP_TAG_RANGE));
}

int ippAddCollection(ipp_attribute **req_attr, char *name, void *value, ipp_tag_t group_tag)
{
    char *buff[1];
    buff[0] = value;
    return (ippAddAttr(req_attr, name, (void **)buff, 1, group_tag, IPP_TAG_BEGIN_COLLECTION));
}
