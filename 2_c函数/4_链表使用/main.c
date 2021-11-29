#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct avahi_browse_info{
	char print_name[256];
	bool color_flg;
	char pdl[256];
	char avahi_name[256];
	struct avahi_browse_info *next;
}avahi_browse_info_t;

static avahi_browse_info_t *header_browse_info = NULL;
static void avahi_browse_add_info(avahi_browse_info_t *avahi_info)
{
	if (header_browse_info == NULL){
		//第一个节点先加入header，next节点指向null
		header_browse_info = (avahi_browse_info_t*)malloc(sizeof(avahi_browse_info_t));
		strcpy(header_browse_info->print_name, avahi_info->print_name);
		strcpy(header_browse_info->pdl, avahi_info->pdl);
		strcpy(header_browse_info->avahi_name, avahi_info->avahi_name);
		header_browse_info->color_flg = avahi_info->color_flg;
		header_browse_info->next = NULL;
	} else {
		//第二个节点开始
		avahi_browse_info_t *p = header_browse_info, *q = NULL;

		//先找到当前最后一个节点（不是空节点）
		while(p->next != NULL)
			p = p->next;

		q = p;//先把当前最后一个节点赋值给q
		p = p->next;//将p指向p->next(此时为空节点)
		p = (avahi_browse_info_t*)malloc(sizeof(avahi_browse_info_t));//给p分配空间，并赋值
		strcpy(p->print_name, avahi_info->print_name);
		strcpy(p->pdl, avahi_info->pdl);
		strcpy(p->avahi_name, avahi_info->avahi_name);
		p->color_flg = avahi_info->color_flg;	
		p->next = NULL;
		
		q->next = p;//将p 接入链表最后一个节点
	}
	printf("%s added now!\n", avahi_info->print_name);
}

/*
*input parameter: 
*	avahi_name:  Used to find nodes
*	print_name:	 Used to return the printer name
*/
static void avahi_browse_remove_info(const char *avahi_name, char *print_name)
{
	avahi_browse_info_t *p = header_browse_info;
	avahi_browse_info_t *q = header_browse_info;

	//header processing
	//头部处理，如果头出队，则头指针要指向下一个节点
	if (p == NULL){
		return;
	} else {
		if (strcmp(p->avahi_name, avahi_name) ==0 ){
			strcpy(print_name,p->print_name);
			header_browse_info = p->next;
			free(p);
			return;
		}		
	}
	
	p = p->next;
	while(p != NULL){
		if (strcmp(p->avahi_name, avahi_name) ==0 ){
			strcpy(print_name,p->print_name);
			q->next = p->next;
			free(p);
			return;
		}else{
			//用q来标记p，当p出队后，q->next直接指向p->next
			q = p;
			p = p->next;
		}
	}
	printf("%s remove now!", print_name);
}

avahi_browse_info_t *avahi_browse_get_info(char *print_name)
{
	avahi_browse_info_t *p = header_browse_info;

	while(p != NULL){
		printf("avahi_browse_get_info: p->print_name=%s color=%d pdl=%s print_name=%s\n", p->print_name, 
			p->color_flg, p->pdl,print_name);
		//查找到对应节点后返回改节点地址
		if (strcmp(p->print_name, print_name) ==0 ){
			printf("--1--\n");
			return p;
		} else {
			p = p->next;
		}
	}
	return NULL;
}

void avahi_browse_printlist()
{
	avahi_browse_info_t *p = header_browse_info;

	while(p != NULL){
		printf("avahi_browse_printlist: p->print_name=%s color=%d\n", 
						p->print_name, p->color_flg);

		p = p->next;
	}	
}


int main(int argc, char **argv)
{
	avahi_browse_info_t a;

	strcpy(a.print_name, "aaa");
	a.color_flg = true;
	strcpy(a.pdl, "a_pdl");
	strcpy(a.avahi_name, "a_avahi");
	avahi_browse_add_info(&a);

	avahi_browse_info_t b;
	strcpy(b.print_name, "bbb");
	b.color_flg = true;
	strcpy(b.pdl, "b_pdl");
	strcpy(b.avahi_name, "b_avahi");
	avahi_browse_add_info(&b);

	avahi_browse_info_t *tmp = NULL;
	tmp = avahi_browse_get_info("bbb");
	printf("avahi_name=%s \n", tmp->avahi_name);
	printf("pdl=%s \n", tmp->pdl);
	printf("tmp=%p \n", tmp);
	return 0;
}


