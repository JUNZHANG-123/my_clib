#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ipp.h"
#include "ipp_server.h"
#include "../internalhub/internal_printinfo.h"


int ipp_get_job_attributes(ipp_attribute **job_attr, ipp_jstate_t jobstate)
{
	uint32_t job_id = ipp_get_job_id();
	ipp_server_info_t *ipp_server_info = ipp_get_server_info();
	char job_url[64] = {0};

	sprintf(job_url, "ipp://%s.local:631/ipp/print/Job-%d", ipp_server_info->host_name, job_id);
	
    ippAddString(job_attr, "attributes-charset", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);
    ippAddString(job_attr, "attributes-natural-language", "en", IPP_TAG_OPERATION, IPP_TAG_LANGUAGE);

    ippAddString(job_attr, "charset-supported", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);
    ippAddString(job_attr, "charset-configured", "utf-8", IPP_TAG_OPERATION, IPP_TAG_CHARSET);
	
    ippAddInteger(job_attr, "job-id", job_id, IPP_TAG_JOB, IPP_TAG_INTEGER);
    ippAddString(job_attr, "job-uri", job_url, IPP_TAG_JOB, IPP_TAG_URI);

	internal_jobstate internal_job_sta = (internal_jobstate)jobstate;
	if (internal_job_sta == JOB_STATE_DOWNLOAD_FILE_ERR ||
		internal_job_sta == JOB_STATE_NOTFOUND ||
		internal_job_sta == JOB_STATE_ERROR ) {
		jobstate = IPP_JSTATE_ABORTED;
	} else if (internal_job_sta == JOB_STATE_CREATING) {
		jobstate = IPP_JSTATE_HELD;
	}	

    ippAddInteger(job_attr, "job-state", jobstate, IPP_TAG_JOB, IPP_TAG_ENUM);
    switch (jobstate) {
		case IPP_JSTATE_PENDING:
			ippAddString(job_attr, "job-state-message", "Job pending.", IPP_TAG_JOB, IPP_TAG_TEXT);
			ippAddString(job_attr, "job-state-reasons", "none", IPP_TAG_JOB, IPP_TAG_KEYWORD);
			break;
	
		case IPP_JSTATE_HELD:
			if (0) {
				ippAddString(job_attr, "job-state-message", "Job incoming.", IPP_TAG_JOB, IPP_TAG_TEXT);
				ippAddString(job_attr, "job-state-reasons", "job-incoming", IPP_TAG_JOB, IPP_TAG_KEYWORD);
			} else if (1) {
				ippAddString(job_attr, "job-state-message", "Job held.", IPP_TAG_JOB, IPP_TAG_TEXT);
				ippAddString(job_attr, "job-state-reasons", "job-hold-until-specified", IPP_TAG_JOB, IPP_TAG_KEYWORD);
			} else {
				ippAddString(job_attr, "job-state-message", "Job created.", IPP_TAG_JOB, IPP_TAG_TEXT);
				ippAddString(job_attr, "job-state-reasons", "job-data-insufficient", IPP_TAG_JOB, IPP_TAG_KEYWORD);
			}
			
			break;
	
        case IPP_JSTATE_PROCESSING:
			if (0) {
				ippAddString(job_attr, "job-state-message", "Job canceling.", IPP_TAG_JOB, IPP_TAG_TEXT);
				ippAddString(job_attr, "job-state-reasons", "processing-to-stop-point", IPP_TAG_JOB, IPP_TAG_KEYWORD);
			} else {
				ippAddString(job_attr, "job-state-message", "Job printing.", IPP_TAG_JOB, IPP_TAG_TEXT);
				ippAddString(job_attr, "job-state-reasons", "job-printing", IPP_TAG_JOB, IPP_TAG_KEYWORD);
			}

            break;

        case IPP_JSTATE_STOPPED:
			ippAddString(job_attr, "job-state-message", "Job stopped.", IPP_TAG_JOB, IPP_TAG_TEXT);
			ippAddString(job_attr, "job-state-reasons", "job-stopped", IPP_TAG_JOB, IPP_TAG_KEYWORD);
			break;

		case IPP_JSTATE_CANCELED:
			ippAddString(job_attr, "job-state-message", "Job canceled.", IPP_TAG_JOB, IPP_TAG_TEXT);
			ippAddString(job_attr, "job-state-reasons", "job-canceled-by-user", IPP_TAG_JOB, IPP_TAG_KEYWORD);
			break;

		case IPP_JSTATE_ABORTED:
			ippAddString(job_attr, "job-state-message", "Job aborted.", IPP_TAG_JOB, IPP_TAG_TEXT);
			ippAddString(job_attr, "job-state-reasons", "aborted-by-system", IPP_TAG_JOB, IPP_TAG_KEYWORD);
			break;

		case IPP_JSTATE_COMPLETED:
			ippAddString(job_attr, "job-state-message", "Job completed.", IPP_TAG_JOB, IPP_TAG_TEXT);
			ippAddInteger(job_attr, "job-impressions-completed", 1, IPP_TAG_JOB, IPP_TAG_INTEGER);
			ippAddInteger(job_attr, "job-media-sheets-completed", 1, IPP_TAG_JOB, IPP_TAG_INTEGER);
			ippAddString(job_attr, "job-state-reasons", "job-completed-successfully", IPP_TAG_JOB, IPP_TAG_KEYWORD);
			break;

		default:
			ippAddString(job_attr, "job-state-message", "none", IPP_TAG_JOB, IPP_TAG_TEXT);
			ippAddString(job_attr, "job-state-reasons", "none", IPP_TAG_JOB, IPP_TAG_KEYWORD);
			break;
    }

    return 0;
}


