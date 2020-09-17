#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
typedef struct Stack {
	LinkedList *list;
} Stack;

void create_stack(Stack *stack) {
	stack->list=malloc(sizeof(LinkedList *));
	free(stack->list->head);
	create_list(stack->list);
}

void push(Stack *stack, int data) {
	add_at_first(stack->list, data);
}

int peek(Stack *stack) {
	return get(stack->list, 0);
}

int pop(Stack *stack) {
	int data=peek(stack);
	_remove_(stack->list, 0);
	return data;
}

int main() {
	Stack *stack;
	create_stack(stack);
	return 0;
}