#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
 
#define POSTURL    "http://192.168.175.1:8888/pic"
#define FILENAME   "../dummy_pen/img0000.jpg"
#if 0	//将请求保存到文件

#define POSTFIELDS "email=myemail@163.com&password=mypassword&autologin=1&submit=登 录&type="

 
size_t write_data(void* buffer,size_t size,size_t nmemb,void *stream)
{
	FILE *fptr = (FILE*)stream;
	fwrite(buffer,size,nmemb,fptr);
	return size*nmemb;
}
 
int main(int argc,char *argv[])
{
	CURL *curl;
	CURLcode res;
	FILE* fptr;
	struct curl_slist *http_header = NULL;
 
	if ((fptr = fopen(FILENAME,"w")) == NULL)
	{
		fprintf(stderr,"fopen file error:%s\n",FILENAME);
		return -1;
	}
 
	curl = curl_easy_init();
	if (!curl)
	{
		fprintf(stderr,"curl init failed\n");
		return -1;
	}
 
	curl_easy_setopt(curl,CURLOPT_URL,POSTURL); //url地址
	//curl_easy_setopt(curl,CURLOPT_POSTFIELDS,POSTFIELDS); //post参数
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data); //对返回的数据进行操作的函数地址
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,fptr); //这是write_data的第四个参数值
	curl_easy_setopt(curl,CURLOPT_POST,1); //设置问非0表示本次操作为post
	curl_easy_setopt(curl,CURLOPT_VERBOSE,1); //打印调试信息
	curl_easy_setopt(curl,CURLOPT_HEADER,1); //将响应头信息和相应体一起传给write_data
	curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1); //设置为非0,响应头信息location
	//curl_easy_setopt(curl,CURLOPT_COOKIEFILE,"/Users/zhu/CProjects/curlposttest.cookie");
 
	res = curl_easy_perform(curl);
 
	if (res != CURLE_OK)
	{
		switch(res)
		{
			case CURLE_UNSUPPORTED_PROTOCOL:
				fprintf(stderr,"不支持的协议,由URL的头部指定\n");
			case CURLE_COULDNT_CONNECT:
				fprintf(stderr,"不能连接到remote主机或者代理\n");
			case CURLE_HTTP_RETURNED_ERROR:
				fprintf(stderr,"http返回错误\n");
			case CURLE_READ_ERROR:
				fprintf(stderr,"读本地文件错误\n");
			default:
				fprintf(stderr,"返回值:%d\n",res);
		}
		return -1;
	}
 
	curl_easy_cleanup(curl);
}
#endif


 
size_t process_data(void* buffer, size_t size, size_t nmemb, void* user_p){
    FILE *fp = (FILE*)user_p;
    size_t return_size = fwrite(buffer, size, nmemb, fp);
    printf("process_data:%s\n", (char*)buffer);
}
 
int get(void){
    
    CURLcode return_code;
    return_code = curl_global_init(CURL_GLOBAL_ALL);
    if(return_code != CURLE_OK){
        printf("curl_global_init failed!");
        return -1;
    }
 
    //get easyhandle
    CURL* easy_handler = curl_easy_init();
    if(easy_handler == NULL){
        printf("curl_easy_init failed!");
        curl_global_cleanup();
        return -1;
    }
 
    FILE* fp = fopen(FILENAME,"ab+");
    //set easy opt
    curl_easy_setopt(easy_handler, CURLOPT_URL, POSTURL);
    curl_easy_setopt(easy_handler, CURLOPT_WRITEFUNCTION, &process_data);
    curl_easy_setopt(easy_handler, CURLOPT_WRITEDATA,fp);
 
    //exe
    curl_easy_perform(easy_handler);
 
    fclose(fp);
    curl_easy_cleanup(easy_handler);
    curl_global_cleanup();
    return 0;
}
 
size_t read_data(void* buffer,size_t size,size_t nmemb,void* user_p){
    FILE* fp = (FILE *)user_p;
    return fread(buffer,size,nmemb,fp);
}
 
int post(CURL *easy_handler){
	CURLcode code;
    FILE *fp = fopen(FILENAME,"rb");
    if(NULL == fp){
        printf("fopen failed!\n");
        curl_global_cleanup();
        return -1;
    }
    
    fseek(fp,0,2);
    int file_size = ftell(fp);
    rewind(fp);
	
	printf("file_size=%d\n", file_size);
 
    curl_easy_setopt(easy_handler, CURLOPT_URL, POSTURL);
    curl_easy_setopt(easy_handler, CURLOPT_UPLOAD, 1);
    curl_easy_setopt(easy_handler, CURLOPT_READFUNCTION, &read_data);
    curl_easy_setopt(easy_handler, CURLOPT_READDATA, fp);
    curl_easy_setopt(easy_handler, CURLOPT_INFILESIZE_LARGE, file_size);

	#if 1
	/* enable TCP keep-alive for this transfer */
    curl_easy_setopt(easy_handler, CURLOPT_TCP_KEEPALIVE, 1L);
    /* keep-alive idle time to 120 seconds */
    curl_easy_setopt(easy_handler, CURLOPT_TCP_KEEPIDLE, 30000L);
    /* interval time between keep-alive probes: 60 seconds */
    curl_easy_setopt(easy_handler, CURLOPT_TCP_KEEPINTVL, 200L);
    curl_easy_setopt(easy_handler, CURLOPT_TIMEOUT, 30);
	
    /**
    * 当多个线程都使用超时处理的时候，同时主线程中有sleep或是wait等操作。
    * 如果不设置这个选项，libcurl将会发信号打断这个wait从而导致程序退出。
    */
    curl_easy_setopt(easy_handler, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(easy_handler, CURLOPT_CONNECTTIMEOUT, 20);
	#endif
	
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Expect:");
	curl_easy_setopt(easy_handler, CURLOPT_HTTPHEADER, headers);

    //
    code = curl_easy_perform(easy_handler);
    if(code == CURLE_OK){
        printf("upload success\n");
    }
 
    fclose(fp);
    //curl_easy_cleanup(easy_handler);
    //curl_global_cleanup();
    return 0;
}
 
int post_arguments(void){
    CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
    CURL* easy_handler = curl_easy_init();
    
    curl_easy_setopt(easy_handler, CURLOPT_URL, POSTURL);
    curl_easy_setopt(easy_handler, CURLOPT_POSTFIELDS, "ID=1&AI_ID=2&gift_url=123");
    code = curl_easy_perform(easy_handler);
    if(code == CURLE_OK){
        printf("post arguments success\n");
    }
    curl_easy_cleanup(easy_handler);
    curl_global_cleanup();
    return 0;
}
 
int post_multi_part(void){
    
    CURLcode code;
    code = curl_global_init(CURL_GLOBAL_ALL);
    if(code != CURLE_OK){
        printf("curl global init failed!");
        curl_global_cleanup();
        return -1;
    }
    CURL* easy_handler = curl_easy_init();
    if(easy_handler == NULL){
        printf("curl easy init failed!");
        curl_global_cleanup();
        return -1;
    }
    curl_easy_setopt(easy_handler, CURLOPT_URL, POSTURL);
    //curl_easy_setopt(easy_handler,CURLOPT_POSTFIELDS,"ID=1&AI_ID=2&gift_url=123");
    struct curl_httppost* post = NULL;
    struct curl_httppost* last = NULL;
 
    //string ID = "123";
    //string AI_ID = "1234567";
    //string gift_url = "sdfsdfdsfdsf";
	
	char ID[10] = "123";
	char AI_ID[100] = "1234567";
	char gift_url[100] = "sdfsdfdsfdsf";
	
    //curl_formadd(&post,&last,CURLFORM_COPYNAME, "AI_ID", CURLFORM_COPYCONTENTS, AI_ID, CURLFORM_END);
    //curl_formadd(&post,&last,CURLFORM_COPYNAME, "ID", CURLFORM_COPYCONTENTS, ID, CURLFORM_END);
    //curl_formadd(&post,&last,CURLFORM_COPYNAME, "gift_url", CURLFORM_COPYCONTENTS, gift_url, CURLFORM_END);
    curl_formadd(&post,&last,CURLFORM_COPYNAME, "newImg", CURLFORM_FILE, "img0000.jpg", CURLFORM_END);
    curl_formadd(&post,&last,CURLFORM_COPYNAME, "newImg", CURLFORM_FILE, "img0000.jpg", CURLFORM_END);
    curl_formadd(&post,&last,CURLFORM_COPYNAME, "newImg", CURLFORM_FILE, "img0000.jpg", CURLFORM_END);
   
 
    char buffer[1024];
    snprintf(buffer,sizeof(buffer),"%d",123);
    printf("buffer=%s\n", buffer);
 
   /*
    char file1[] = "./picture_1.png";
    char file2[] = "./picture_2.png";
    struct curl_forms arr[3];
    arr[0].option = CURLFORM_FILE;
    arr[0].value = file1;
    arr[1].option = CURLFORM_FILE;
    arr[1].value = file2;
    arr[2].option = CURLFORM_END;
    curl_formadd(&post,&last,CURLFORM_COPYNAME,"newImg",CURLFORM_ARRAY,arr,CURLFORM_END);
*/
    curl_easy_setopt(easy_handler,CURLOPT_HTTPPOST,post);
    code = curl_easy_perform(easy_handler);
    if(code != CURLE_OK){
        printf("curl easy perform failed!");
        curl_easy_cleanup(easy_handler);
        curl_global_cleanup();
        return -1;
    }
    curl_formfree(post);
    curl_easy_cleanup(easy_handler);
    curl_global_cleanup();
    return 0;
}
 
 
int main(void){

    CURLcode code;
    code = curl_global_init(CURL_GLOBAL_ALL);
    if (code != CURLE_OK){
        printf("curl global init failed!\n");
        return -1;
    }
	
    //get easy handler
    CURL *easy_handler = curl_easy_init();
    if(easy_handler == NULL){
        printf("curl easy init failed!\n");
        curl_global_cleanup();
        return -1;
    }

#if 1
	struct timeval t1, t2;
	gettimeofday(&t1, NULL);
	for (int i = 0; i< 120; i++) {
		post(easy_handler);
		printf("i=%d\n", i);
	}
	gettimeofday(&t2, NULL);
	unsigned long diff = (t2.tv_sec-t1.tv_sec) * 1000000 + t2.tv_usec-t1.tv_usec;
	printf("diff=%ld\n", diff);
#endif

    //post_arguments();
    //post_multi_part();
    return 0;
}
 
