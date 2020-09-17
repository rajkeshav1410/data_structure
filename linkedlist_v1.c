#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
#define N_ARGS(...) (sizeof((int[]){0, ##__VA_ARGS__})/sizeof(int)-1)
#define add_element(list, data, ...) (__add_element(list, data, N_ARGS(__VA_ARGS__), ##__VA_ARGS__))

typedef struct _Node {
	void *data;
	struct _Node *next;
	int index;
} Node;

typedef struct _LinkedList {
	struct _Node *head, *prev;
	int len;
} LinkedList;

void create_list(LinkedList *);
void __add_element(LinkedList *, void *, int,  ...);
void *get(LinkedList *, int);
void *to_array(LinkedList *);
int size(LinkedList *);
void reindex(LinkedList *);
void free_list(LinkedList *);

int main() {
	LinkedList *list1, *list2;
	create_list(list1);
	create_list(list2);
	add_element(list1, (int *)1);
	add_element(list1, "Raj");
	add_element(list2, "and");
	printf("0 : %d\n1 : %s\n0 : %s\n", get(list1, 0), get(list1, 1), get(list2, 0));
	printf("%s, %s, %s\n", __FILE__, __DATE__, __TIME__);
	free(list1->head);
	list1->head=NULL;
	return 0;
}

void create_list(LinkedList *list) {
	list->head=NULL;
	list->len=0;
}

void __add_element(LinkedList *list, void *data, int nargs, ...) {
	va_list args;
	Node *node, *curr;
	node=(Node *)malloc(sizeof(Node));
	node->data=data;
	if(nargs==1) {
		va_start(args, nargs);
		int index=va_arg(args, int);
		if(index<0||index>list->len)
			return;
		else {
			if(index==0) {
				node->next=list->head;
				list->head=node;
			}
			else if(index!=list->len) {
				curr=list->head;
				while(curr->next->index!=index)
					curr=curr->next;
				node->next=curr->next;
				curr->next=node;
			}
			reindex(list);
			return;
		}
	}
	node->next=NULL;
	node->index=list->len;
	(list->len)++;
	if(list->head==NULL)
		list->head=node;
	else
		list->prev->next=node;
	list->prev=node;
	node=NULL;
	va_end(args);
}

void *get(LinkedList *list, int index) {
	if(index<0||index>=list->len)
		return NULL;
	Node *curr=list->head;
	while(curr->index!=index)
		curr=curr->next;
	return curr->data;
}

void reindex(LinkedList *list) {
	int index=0;
	Node *curr=list->head;
	while(curr->next!=NULL) {
		curr->index=index++;
		curr=curr->next;
	}
	curr->index=index++;
	list->len=index;
}

void free_list(LinkedList *list) {
	Node *curr=list->head;
	do {
		
	} while(curr->next!=NULL);
}