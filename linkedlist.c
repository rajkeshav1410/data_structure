#include <stdlib.h>
#include <stdio.h>
typedef enum {false, true} boolean;

struct Node {
	int data;
	struct Node *next, *pre;
};

typedef struct LinkedList {
	struct Node *head;
	int length;
} LinkedList;

void create_list(LinkedList *list) {
	list->head=NULL;
	list->length=0;
}

void initialize_node(struct Node **node, int data, struct Node *next) {
	*node=(struct Node *)malloc(sizeof(struct Node));
	if(*node==NULL)
		return;
	(*node)->data=data;
	(*node)->next=next;
}

boolean is_list_empty(LinkedList *list) {
	return list->head==NULL;
}

void add(LinkedList *list, int data) {
	list->length++;
	struct Node *curr, *tmp=list->head;
	initialize_node(&curr, data, NULL);
	if(is_list_empty(list)) {
		list->head=curr;
		return;
	}
	while(tmp->next)
		tmp=tmp->next;
	tmp->next=curr;
}

void add_at_first(LinkedList *list, int data) {
	list->length++;
	struct Node *curr;
	if(is_list_empty(list)) {
		initialize_node(&curr, data, NULL);
		list->head=curr;
		return;
	}
	initialize_node(&curr, data, list->head);
	list->head=curr;
}

void _add_(LinkedList *list, int data, int index) {
	list->length++;
	if(index<=0) {
		add_at_first(list, data);
		return;
	}
	if(index>=list->length)  {
		add(list, data);
		return;
	}
	struct Node *curr, *tmp=list->head;
	while(--index)
		tmp=tmp->next;
	initialize_node(&curr, data, tmp->next);
	tmp->next=curr;
}

int _remove_(LinkedList *list, int index) {
	if(index<0||index>list->length-1)
		return -1;
	list->length--;
	struct Node *tmp, *ptr=list->head;
	if(index==0) {
		tmp=list->head;
		list->head=tmp->next;
		free(tmp);
		return 0;
	}
	while(--index)
		ptr=ptr->next;
	tmp=ptr->next;
	ptr->next=tmp->next;
	free(tmp);
	return index;
}

int get(LinkedList *list, int index) {
	if(index<0)
		index=0;
	else if(index>(list->length)-1)
		index=(list->length)-1;
	struct Node *tmp=list->head;
	while(index--)
		tmp=tmp->next;
	return tmp->data;
}

int search(LinkedList *list, int data) {
	int index=0;
	struct Node *tmp=list->head;
	while(tmp) {
		if(tmp->data==data)
			return index;
		tmp=tmp->next;
		index++;
	}
	return -1;
}

void dispose(LinkedList *list) {
	struct Node *ptr=list->head,
				*tmp=ptr;
	while(tmp) {
		tmp=ptr->next;
		free(ptr);
		ptr=tmp;
	}
}

int main() {
	struct LinkedList *list_1;
	create_list(list_1);
	add_at_first(list_1, 1);
	add_at_first(list_1, 3);
	add(list_1, 5);
	_add_(list_1, 7, 2);
	printf("%d\n", list_1->length);
	printf("%d %d %d\n", get(list_1, 1), get(list_1, 2), get(list_1, 3));
	_remove_(list_1, 3);
	printf("%d %d %d\n", get(list_1, 1), get(list_1, 2), get(list_1, 3));
	printf("%d\n", search(list_1, 3));
	printf("\033[31;1mHello\033[0m, \033[32;1;2mworld!\033[0m");
	return 0;
}