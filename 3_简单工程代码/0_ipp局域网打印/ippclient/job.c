#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ipp.h"

int ipp_get_job_attributes(ipp_attribute **job_attr, ipp_jstate_t jobstate)
{
    ippAddString(job_attr, "attributes-charset", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);
    ippAddString(job_attr, "attributes-natural-language", "en", IPP_TAG_OPERATION, IPP_TAG_LANGUAGE);

    ippAddString(job_attr, "charset-supported", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);
    ippAddString(job_attr, "charset-configured", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);

    ippAddString(job_attr, "printer-uri", "ipp://esp32-mdns.local:631/ipp/print", IPP_TAG_OPERATION, IPP_TAG_URI);

    ippAddInteger(job_attr, "job-id", 1, IPP_TAG_JOB, IPP_TAG_INTEGER);
    ippAddString(job_attr, "job-uri", "ipp://esp32-mdns.local:631/ipp/print/Job-1", IPP_TAG_JOB, IPP_TAG_URI);

    ippAddInteger(job_attr, "job-state", jobstate, IPP_TAG_JOB, IPP_TAG_ENUM);
    switch (jobstate) {
        case IPP_JSTATE_COMPLETED:
            ippAddInteger(job_attr, "job-impressions-completed", 1, IPP_TAG_JOB, IPP_TAG_INTEGER);
            ippAddInteger(job_attr, "job-media-sheets-completed", 1, IPP_TAG_JOB, IPP_TAG_INTEGER);
            ippAddString(job_attr, "job-state-reasons", "job-completed-successfully", IPP_TAG_JOB, IPP_TAG_KEYWORD);
            break;

       case IPP_JSTATE_CANCELED:
           ippAddString(job_attr, "job-state-message", "stop print by user", IPP_TAG_JOB, IPP_TAG_TEXT);
           ippAddString(job_attr, "job-state-reasons", "processing-to-stop-point", IPP_TAG_JOB, IPP_TAG_KEYWORD);
           break;

       default:
           ippAddString(job_attr, "job-state-message", "none", IPP_TAG_JOB, IPP_TAG_TEXT);
          ippAddString(job_attr, "job-state-reasons", "none", IPP_TAG_JOB, IPP_TAG_KEYWORD);
          break;
    }

    return 0;
}