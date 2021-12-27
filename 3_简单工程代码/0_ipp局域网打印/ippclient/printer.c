#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ipp.h"

int add_printer_operations_supported(ipp_attribute **req_attr)
{
    int ops[] = /* operations-supported values */
    {
    IPP_OP_PRINT_JOB,
    IPP_OP_VALIDATE_JOB,
    IPP_OP_CREATE_JOB,
    IPP_OP_SEND_DOCUMENT,
    IPP_OP_CANCEL_JOB,
    IPP_OP_GET_JOB_ATTRIBUTES,
    IPP_OP_GET_PRINTER_ATTRIBUTES,
    IPP_OP_HOLD_JOB,
    IPP_OP_RELEASE_JOB,
    };

    #define BUFF_SIZE (sizeof(ops)/sizeof(ops[0]))
    int *buff[BUFF_SIZE];
    for (int i=0; i<BUFF_SIZE; i++) {
       buff[i] = &ops[i];
    }

    ippAddAttr(req_attr, "operations-supported", (void **)buff, BUFF_SIZE, IPP_TAG_PRINTER, IPP_TAG_ENUM);
    return 0;
}

int ipp_get_printer_state(ipp_attribute **printer_attr, ipp_pstate_t printerstate)
{
    ippAddBoolean(printer_attr, "printer-is-accepting-jobs", 1, IPP_TAG_PRINTER);

    ippAddData(printer_attr, "printer-state-change-date-time", NULL, IPP_TAG_PRINTER);
    ippAddInteger(printer_attr, "printer-state-change-time", 0, IPP_TAG_PRINTER, IPP_TAG_INTEGER);

    switch (printerstate) {
       case IPP_PSTATE_STOPPED:
         ippAddInteger(printer_attr, "printer-state", IPP_PSTATE_STOPPED, IPP_TAG_PRINTER, IPP_TAG_ENUM);
         ippAddString(printer_attr, "printer-state-message", "Printer is stoped.", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
         break;

       case IPP_PSTATE_PROCESSING:
         ippAddInteger(printer_attr, "printer-state", IPP_PSTATE_PROCESSING, IPP_TAG_PRINTER, IPP_TAG_ENUM);
         ippAddString(printer_attr, "printer-state-message", "Printer is processing.", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
         break;

       case IPP_PSTATE_IDLE:
       default:
         ippAddInteger(printer_attr, "printer-state", IPP_PSTATE_IDLE, IPP_TAG_PRINTER, IPP_TAG_ENUM);
         ippAddString(printer_attr, "printer-state-message", "Printer ready to print.", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
         break;
    }

    ippAddString(printer_attr, "printer-state-reasons", "none", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    return 0;
}

int ipp_get_printer_pdl(ipp_attribute **printer_attr)
{
    #define PDL_SIZE 4
    char *pdl[PDL_SIZE] = {
        "application/octet-stream",
        "image/pwg-raster",
        "application/PCLm",
        "image/urf"
    };

    ippAddResolution(printer_attr, "printer-resolution-supported", 300, 300, 0x03, IPP_TAG_PRINTER);
    ippAddResolution(printer_attr, "printer-resolution-default", 300, 300, 0x03, IPP_TAG_PRINTER);

    ippAddAttr(printer_attr, "document-format-supported", (void **)pdl, PDL_SIZE, IPP_TAG_PRINTER, IPP_TAG_MIMETYPE);

    ippAddString(printer_attr, "document-format-default", "image/urf", IPP_TAG_PRINTER, IPP_TAG_MIMETYPE);

    //ippAddString(printer_attr, "urf-supported", "RS300", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    ippAddResolution(printer_attr, "pwg-raster-document-resolution-supported", 300, 300, 0x03, IPP_TAG_PRINTER);
    ippAddResolution(printer_attr, "pclm-source-resolution-supported", 300, 300, 0x03, IPP_TAG_PRINTER);

    return 0;
}


void ipp_validate_job(ipp_attribute **printer_attr_req, char *job_name)
{
	ippAddString(printer_attr_req, "attributes-charset", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);
	ippAddString(printer_attr_req, "attributes-natural-language", "zh-cn", IPP_TAG_OPERATION, IPP_TAG_LANGUAGE);
	ippAddString(printer_attr_req, "printer-uri", "ipp://10.66.9.120:631/ipp/print", IPP_TAG_OPERATION, IPP_TAG_URI);
	ippAddString(printer_attr_req, "requesting-user-name", "root", IPP_TAG_OPERATION, IPP_TAG_NAME);
	ippAddString(printer_attr_req, "job-name", job_name, IPP_TAG_OPERATION, IPP_TAG_NAME);
	ippAddString(printer_attr_req, "document-format", "image/urf", IPP_TAG_OPERATION, IPP_TAG_MIMETYPE);

	ippAddString(printer_attr_req, "job-originating-host-name", "localhost", IPP_TAG_JOB, IPP_TAG_NAME);
	ippAddString(printer_attr_req, "job-originating-user-name", "root", IPP_TAG_JOB, IPP_TAG_NAME);
	ippAddInteger(printer_attr_req, "job-priority", 50, IPP_TAG_JOB, IPP_TAG_INTEGER);
	ippAddString(printer_attr_req, "job-uuid", "urn:uuid:bf742805-f872-3f1b-4e12-2abc59d5d010", IPP_TAG_JOB, IPP_TAG_URI);
	ippAddString(printer_attr_req, "output-format", "apple-raster", IPP_TAG_JOB, IPP_TAG_NAME);
	ippAddString(printer_attr_req, "Resolution", "300dpi", IPP_TAG_JOB, IPP_TAG_NAME);
}

void ipp_create_job(ipp_attribute **printer_attr_req, char *job_name)
{
	ippAddString(printer_attr_req, "attributes-charset", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);
	ippAddString(printer_attr_req, "attributes-natural-language", "zh-cn", IPP_TAG_OPERATION, IPP_TAG_LANGUAGE);
	ippAddString(printer_attr_req, "printer-uri", "ipp://10.66.9.120:631/ipp/print", IPP_TAG_OPERATION, IPP_TAG_URI);
	ippAddString(printer_attr_req, "requesting-user-name", "root", IPP_TAG_OPERATION, IPP_TAG_NAME);
	ippAddString(printer_attr_req, "job-name", job_name, IPP_TAG_OPERATION, IPP_TAG_NAME);
	// ippAddString(printer_attr_req, "document-format", "image/urf", IPP_TAG_OPERATION, IPP_TAG_MIMETYPE);

	// ippAddString(printer_attr_req, "job-originating-host-name", "localhost", IPP_TAG_JOB, IPP_TAG_NAME);
	// ippAddString(printer_attr_req, "job-originating-user-name", "root", IPP_TAG_JOB, IPP_TAG_NAME);
	// ippAddInteger(printer_attr_req, "job-priority", 50, IPP_TAG_JOB, IPP_TAG_INTEGER);
	// ippAddString(printer_attr_req, "job-uuid", "urn:uuid:bf742805-f872-3f1b-4e12-2abc59d5d010", IPP_TAG_JOB, IPP_TAG_URI);
	// ippAddString(printer_attr_req, "output-format", "apple-raster", IPP_TAG_JOB, IPP_TAG_NAME);
	// ippAddString(printer_attr_req, "Resolution", "300dpi", IPP_TAG_JOB, IPP_TAG_NAME);
}

int ipp_get_printer_attributes_req(ipp_attribute **printer_attr_req)
{
    ippAddString(printer_attr_req, "attributes-charset", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);
    ippAddString(printer_attr_req, "attributes-natural-language", "zh-cn", IPP_TAG_OPERATION, IPP_TAG_LANGUAGE);
    ippAddString(printer_attr_req, "printer-uri", "ipp://10.66.9.120:631/ipp/print", IPP_TAG_OPERATION, IPP_TAG_URI);
	ippAddString(printer_attr_req, "requesting-user-name", "root", IPP_TAG_OPERATION, IPP_TAG_NAME);
	ippAddString(printer_attr_req, "requested-attributes", "all", IPP_TAG_OPERATION, IPP_TAG_KEYWORD);
	return 0;
}

void ipp_get_job_attribut(ipp_attribute **printer_attr_req)
{
	ippAddString(printer_attr_req, "attributes-charset", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);
	ippAddString(printer_attr_req, "attributes-natural-language", "zh-cn", IPP_TAG_OPERATION, IPP_TAG_LANGUAGE);
	ippAddString(printer_attr_req, "printer-uri", "ipp://10.66.9.120:631/ipp/print", IPP_TAG_OPERATION, IPP_TAG_URI);
	ippAddInteger(printer_attr_req, "job-id", 1, IPP_TAG_OPERATION, IPP_TAG_INTEGER);
	ippAddString(printer_attr_req, "requesting-user-name", "root", IPP_TAG_OPERATION, IPP_TAG_NAME);
	ippAddString(printer_attr_req, "requested-attributes", "all", IPP_TAG_OPERATION, IPP_TAG_KEYWORD);
}

void ipp_cancel_job(ipp_attribute **printer_attr_req)
{
	ippAddString(printer_attr_req, "attributes-charset", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);
	ippAddString(printer_attr_req, "attributes-natural-language", "zh-cn", IPP_TAG_OPERATION, IPP_TAG_LANGUAGE);
	ippAddString(printer_attr_req, "printer-uri", "ipp://10.66.9.120:631/ipp/print", IPP_TAG_OPERATION, IPP_TAG_URI);
	ippAddInteger(printer_attr_req, "job-id", 1, IPP_TAG_OPERATION, IPP_TAG_INTEGER);
	ippAddString(printer_attr_req, "requesting-user-name", "root", IPP_TAG_OPERATION, IPP_TAG_NAME);
}



#if 0
int ipp_get_printer_attributes(ipp_attribute **printer_attr, ipp_pstate_t printerstate)
{
    ippAddString(printer_attr, "attributes-charset", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);
    ippAddString(printer_attr, "attributes-natural-language", "en", IPP_TAG_OPERATION, IPP_TAG_LANGUAGE);

    ippAddString(printer_attr, "charset-supported", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);
    ippAddString(printer_attr, "charset-configured", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);

    ippAddString(printer_attr, "printer-make-and-model", "PP A4 Series", IPP_TAG_PRINTER, IPP_TAG_TEXT);
    ippAddString(printer_attr, "output-bin-default", "face-down", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    ippAddString(printer_attr, "output-bin-supported", "face-down", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    ippAddBoolean(printer_attr, "color-supported", 0, IPP_TAG_PRINTER);
    ippAddString(printer_attr, "printer-strings-uri", "ipp://esp32-mdns.local:631/ipp/print", IPP_TAG_PRINTER, IPP_TAG_URI);

    /* Put all available PDls into a simple case-insensitevely searchable
     sorted string list */
    ipp_get_printer_pdl(printer_attr);

    /* Page*/
    ippAddInteger(printer_attr, "media-bottom-margin-supported", 440, IPP_TAG_PRINTER, IPP_TAG_INTEGER);
    ippAddInteger(printer_attr, "media-left-margin-supported", 440, IPP_TAG_PRINTER, IPP_TAG_INTEGER);
    ippAddInteger(printer_attr, "media-right-margin-supported", 440, IPP_TAG_PRINTER, IPP_TAG_INTEGER);
    ippAddInteger(printer_attr, "media-top-margin-supported", 440, IPP_TAG_PRINTER, IPP_TAG_INTEGER);

    ippAddString(printer_attr, "media-default", "iso_a4_210x297mm", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    ippAddString(printer_attr, "media-supported", "iso_a4_210x297mm", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    ippAddString(printer_attr, "media-ready", "iso_a4_210x297mm", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);

    ippAddString(printer_attr, "media-type", "auto", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    ippAddString(printer_attr, "media-type-supported", "auto", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);

    ippAddString(printer_attr, "sides-supported", "one-sided", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    ippAddString(printer_attr, "sides-default", "one-sided", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);


    ippAddInteger(printer_attr, "job-priority-default", 50, IPP_TAG_PRINTER, IPP_TAG_INTEGER);
    ippAddString(printer_attr, "job-hold-until-default", "no-hold", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    ippAddString(printer_attr, "job-sheets-default", "none", IPP_TAG_PRINTER, IPP_TAG_CHARSET);

    ippAddInteger(printer_attr, "multiple-operation-time-out", 30, IPP_TAG_PRINTER, IPP_TAG_INTEGER);
    ippAddBoolean(printer_attr, "multiple-document-jobs-supported", 0, IPP_TAG_PRINTER);

    ippAddString(printer_attr, "multiple-document-handling-default", 
                               "separate-documents-uncollated-copies", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    ippAddString(printer_attr, "multiple-document-handling-supported", 
                   "separate-documents-uncollated-copies", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);

    ippAddInteger(printer_attr, "copies-default", 1, IPP_TAG_PRINTER, IPP_TAG_INTEGER);

    ippAddInteger(printer_attr, "finishings-supported", 3,  IPP_TAG_PRINTER,IPP_TAG_ENUM);
    ippAddInteger(printer_attr, "finishings-default", 3, IPP_TAG_PRINTER, IPP_TAG_ENUM);


    ippAddInteger(printer_attr, "number-up-default", 1, IPP_TAG_PRINTER, IPP_TAG_INTEGER);


    /* quality-default: Draft(3), Normal(4), High(5) */
    ippAddInteger(printer_attr, "print-quality-default", 4, IPP_TAG_PRINTER, IPP_TAG_ENUM);

    ippAddString(printer_attr, "media-size-supported", "{x-dimension=21000 y-dimension=29700}", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    ippAddString(printer_attr, "media-size-default", "{x-dimension=21000 y-dimension=29700}", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);

    ippAddInteger(printer_attr, "job-priority-supported", 100, IPP_TAG_PRINTER, IPP_TAG_INTEGER);

    ippAddString(printer_attr, "job-hold-until-supported", "no-hold", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    ippAddString(printer_attr, "job-sheets-supported", "none", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);


    ippAddString(printer_attr, "cups-version", NULL, IPP_TAG_UNSUPPORTED_GROUP, IPP_TAG_UNSUPPORTED_VALUE);
    ippAddString(printer_attr, "job-password-encryption-supported", NULL,
                                                  IPP_TAG_UNSUPPORTED_GROUP, IPP_TAG_UNSUPPORTED_VALUE);
    ippAddString(printer_attr, "marker-message", NULL, IPP_TAG_UNSUPPORTED_GROUP, IPP_TAG_UNSUPPORTED_VALUE);
    ippAddString(printer_attr, "printer-mandatory-job-attributes",
                                                  NULL, IPP_TAG_UNSUPPORTED_GROUP, IPP_TAG_UNSUPPORTED_VALUE);

    ippAddString(printer_attr, "compression-supported", "none", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);

    ippAddRange(printer_attr, "copies-supported", 1, 255, IPP_TAG_PRINTER);


    ippAddString(printer_attr, "marker-colors", "#000000", IPP_TAG_PRINTER, IPP_TAG_NAME);
    ippAddInteger(printer_attr, "marker-high-levels", 100, IPP_TAG_PRINTER, IPP_TAG_INTEGER);
    ippAddInteger(printer_attr, "marker-levels", 50, IPP_TAG_PRINTER, IPP_TAG_INTEGER);
    ippAddInteger(printer_attr, "marker-low-levels", 10, IPP_TAG_PRINTER, IPP_TAG_INTEGER);

    ippAddString(printer_attr, "marker-names", "MiaoBao", IPP_TAG_PRINTER, IPP_TAG_NAME);
    ippAddString(printer_attr, "marker-types", "toner", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);

    ippAddString(printer_attr, "generated-natural-language-supported", "en-us", IPP_TAG_PRINTER, IPP_TAG_LANGUAGE);

    ippAddString(printer_attr, "identify-actions-default", "flash", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    ippAddString(printer_attr, "identify-actions-supported", "flash", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);

    ippAddString(printer_attr, "ipp-features-supported", "document-object,airprint-1.8", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);

    ippAddString(printer_attr, "ipp-versions-supported", "1.0,1.1,2.0", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);

    ippAddInteger(printer_attr, "ippget-event-life", 300, IPP_TAG_PRINTER, IPP_TAG_INTEGER);

    ippAddRange(printer_attr, "job-k-octets-supported", 1, 65535, IPP_TAG_PRINTER);

  

    ippAddString(printer_attr, "natural-language-configured", "en", IPP_TAG_PRINTER, IPP_TAG_LANGUAGE);

    ippAddString(printer_attr, "printer-location", "paperang", IPP_TAG_PRINTER, IPP_TAG_TEXT);
    ippAddString(printer_attr, "printer-uuid", "16a65700-007c-1000-bb49-040e3c71acba", IPP_TAG_PRINTER, IPP_TAG_URI);
    ippAddString(printer_attr, "printer-info", "PP A4 Series", IPP_TAG_PRINTER, IPP_TAG_TEXT);
    ippAddString(printer_attr, "printer-device-id", "MFG:PP;CMD:PCLM,PWGRaster;MDL:PP A4 Series;CLS:PRINTER;CID:PPA4;MODE:A4;", IPP_TAG_PRINTER, IPP_TAG_TEXT);

    ippAddInteger(printer_attr, "copies-default", 1, IPP_TAG_PRINTER, IPP_TAG_INTEGER);

    ippAddString(printer_attr, "uri-security-supported", "none", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);

    ippAddString(printer_attr, "print-quality-default", "normal", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);

    ippAddString(printer_attr, "printer-name", "PP A4 Series", IPP_TAG_PRINTER, IPP_TAG_NAME);
    ipp_get_printer_state(printer_attr, printerstate);

    ippAddString(printer_attr, "uri-authentication-supported", "none", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);
    ippAddString(printer_attr, "printer-uri-supported", "ipp://esp32-mdns.local:631/ipp/print", IPP_TAG_PRINTER, IPP_TAG_KEYWORD);

    ippAddInteger(printer_attr, "printer-up-time", 10000, IPP_TAG_PRINTER, IPP_TAG_INTEGER);

    add_printer_operations_supported(printer_attr);

    ippAddInteger(printer_attr, "printer-config-change-time", 0, IPP_TAG_PRINTER, IPP_TAG_INTEGER);
    ippAddData(printer_attr, "printer-config-change-date-time", NULL, IPP_TAG_PRINTER);

    return 0;
}
#endif
