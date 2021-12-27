#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "ipp.h"

static ipp_attribute *printer_attr_req = NULL;
static ipp_attribute *job_attr = NULL;

#define IPP_SERVER_BUF_SIZE_MAX 4096

int main(int argc, char** argv)
{
  uint32_t version = 2 << 8;
  uint32_t op_status = 0;
  uint32_t request_id = 1;
  char buffer[IPP_SERVER_BUF_SIZE_MAX];
  int buf_len = 0;

  // 打印机属性值
#if 0
  ipp_get_printer_attributes_req(&printer_attr_req);
  op_status = IPP_OP_GET_PRINTER_ATTRIBUTES;
  buf_len = ippAttrToReqBuff(printer_attr_req, version, op_status, request_id, buffer, IPP_SERVER_BUF_SIZE_MAX);
#endif

  // 验证打印机任务是否可以创建
#if 0
  ipp_get_job_attribut(&job_attr);
  op_status = IPP_OP_VALIDATE_JOB;
  buf_len = ippAttrToReqBuff(job_attr, version, op_status, request_id, buffer, IPP_SERVER_BUF_SIZE_MAX);
#endif

  // 创建打印任务
#if 0
  ipp_create_job(&job_attr, "test.pdf");
  op_status = IPP_OP_CREATE_JOB;
  buf_len = ippAttrToReqBuff(job_attr, version, op_status, request_id, buffer, IPP_SERVER_BUF_SIZE_MAX);
#endif

  // 获取打印任务状态
#if 0
  ipp_get_job_attribut(&job_attr);
  op_status = IPP_OP_GET_JOB_ATTRIBUTES;
  buf_len = ippAttrToReqBuff(job_attr, version, op_status, request_id, buffer, IPP_SERVER_BUF_SIZE_MAX);
#endif

  //ipp_get_printer_attributes_req(&printer_attr_req);
  op_status = IPP_OP_SEND_DOCUMENT;
  buf_len = ippAttrToReqBuff(printer_attr_req, version, op_status, request_id, buffer, IPP_SERVER_BUF_SIZE_MAX);


  write(1, buffer, buf_len);
  for (int i=0; i<buf_len; i++)
  {
    fprintf(stderr, "0x%02x, ", buffer[i]);
    if (i % 8 == 0)
    {
      fprintf(stderr, "\n");
    }
  }

  fprintf(stderr, "\n");

  return 0;
}
