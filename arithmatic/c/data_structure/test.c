#include "common.h"
#include <stdlib.h>

/* seqlist */
int seqlist_test()
{
	seqlist list;
	seq_init(&list);

	int i;
	for (i = 0; i < 10; i++)
		seq_set(&list, i, i);

	for (i = 0; i < 10; i++)
		printf("seq[%d] is %d\n", i, *(list.seq + i));

	for (i = -1; abs(i) < 11; i--)
		seq_set(&list, i, 1);

	for (i = 0; i < 10; i++)
		printf("seq[%d] is %d\n", i, *(list.seq + i));

	for (i = 0; i < 10; i++)
		seq_clear(&list, i);

	for (i = 0; i < 10; i++)
		printf("seq[%d] is %d\n", i, *(list.seq + i));

	seq_free(&list);

	for (i = 0; i < 10; i++)
		seq_set(&list, i, i);

	return 0;
}

int list_test()
{
	int ret;
	int i;
	pList head;
	pList medium;

	ret = list_init_head(head);
	if (ret < 0)
		exit(-1);

	for(i = 0; i < 10; i++) {
		pList new = (pList)malloc(sizeof(list));
		new->value = i;
		new->next = new->prev = NULL;
		medium = head;
		list_insert(head, *medium, *new);
		medium = medium->next;
	}

	medium = head->next;
	while(medium) {
		printf("%d\n", medium->value);
		medium = medium->next;
	}

	return 0;
}

/* stack */ 
int stack_test()
{
	int i, value, length;
	stk stack;

	init_stack(&stack);

	for(i = 0; i < 10; i++)
		push_stack(&stack, i);

	print_stack(&stack);
	length_stack(&stack, &length);
	printf("length is %d\n", length);

	empty_stack(&stack);
	length_stack(&stack, &length);
	printf("length is %d\n", length);

	for(i = 0; i < 10; i++)
		push_stack(&stack, i);

	for(i = 0; i < 10; i++) {
		pop_stack(&stack, &value);
		printf("%d\n", value);
	}

	length_stack(&stack, &length);
	printf("length is %d\n", length);

	return 0;
}

int queue_test()
{
	int i;
	int value;
	qList queue;
	init_queue(&queue);
	for (i = 0; i < 10; i++) {
		en_queue(&queue, i);
	}

	print_queue(&queue);

	for (i = 0; i < 10; i++) {
		de_queue(&queue, &value);
		printf("pop value is %d\n", value);
	}

	print_queue(&queue);
	destroy_queue(&queue);
	return 0;
}

int cycle_test()
{
	int i, value, ret;
	cycle cq;
	init_cycle(&cq);

	for (i = 0; i < 9; i++) {
		ret = en_cycle(&cq, i);
		if (ret != 0)
			exit(-1);
	}

	print_cycle(&cq);

	for (i = 0; i < 3; i++) {
		ret = de_cycle(&cq, &value);
		printf("de cycle value is %d\n", value);
	}

	for (i = 11; i < 15; i++) {
		ret = en_cycle(&cq, i);
		if (ret != 0)
			exit(-1);
	}

	print_cycle(&cq);
}

void main()
{
/*
	int ret;
	ret = queue_test();
	if (ret == 0)
		printf("test passed\n");

	exit(0);
*/
	cycle_test();
	exit(0);
}
