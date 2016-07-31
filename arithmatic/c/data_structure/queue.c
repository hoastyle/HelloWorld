/* queue */
/* length of normal queue is variable, front point to head and rear point to rear, represent by a list */
#include "common.h"
#include <stdlib.h>

static pQNode medium = NULL, next = NULL;
//使用queue表示一个队列
//头结点不用来存储数据
//开始时front和rear同时指向头结点，之后rear指向最后一个节点
int init_queue(qList *queue)
{
	if (!queue) {
		error("Failed to init queue, invalid parameter\n");
		return -EINVAL;
	}

	queue->front = queue->rear = (qNode *)malloc(sizeof(qNode));
	if (!queue->front) {
		error("Failed to init queue, no mem\n");
		return -ENOMEM;
	}

	queue->front->next = NULL;

	return 0;
}

int en_queue(qList *queue, TYPE value)
{
	if (!queue) {
		error("Failed to enqueue, invalid parameter\n");
		return -EINVAL;
	}

	pQNode node = (pQNode)malloc(sizeof(qNode));
	if (!node) {
		error("Failed to alloc node, no mem\n");
		return -ENOMEM;
	}

	node->data = value;
	node->next = NULL;

	queue->rear->next = node;
	queue->rear = node;
	return 0;
}

int de_queue(qList *queue, TYPE *value)
{
	if (!queue) {
		error("Failed to enqueue, invalid parameter\n");
		return -EINVAL;
	}

	if (queue->front == queue->rear) {
		printf("queue is empty.\n");
		return 0;
	}

	medium = queue->front->next;
	next = medium->next;
	queue->front->next = next;
	*value = medium->data;
	free(medium);
	return 0;
}

int destroy_queue(qList *queue)
{
	if (!queue) {
		error("Failed to destroy queue, invalid parameter\n");
		return -EINVAL;
	}

	medium = queue->front->next;
	while (medium) {
		free(medium);
	}

	free(queue->front);
	return 0;
}

int print_queue(qList *queue)
{
	int i = 0;
	medium = queue->front->next;
	while (medium) {
		printf("queue item %d is %d\n", i, medium->data);
		medium = medium->next;
	}

	return 0;
}

/* 
 * cycle queue
 * - length of cycle queue is consistent, and both front and rear is variable, represent by a array
 * - how works?
 */

/*
 * name: init_cycle
 * - empty when front equal to rear
 * - size of cycle queue is (MAXSIZE - 1)
 */
int init_cycle(cycle *cq)
{
	if (!cq) {
		error("Failed to init cycle queue, invalid parameter\n");
		return -EINVAL;
	}

	cq->base = (TYPE *)malloc(sizeof(TYPE) * MAXSIZE);
	if (!cq->base) {
		error("Failed to malloc memory\n");
		return -ENOMEM;
	}
	cq->front = cq->rear = 0;

	return 0;
}

/* return directly when cycle queue is full */
int en_cycle(cycle *cq, TYPE value)
{
	if (!cq) {
		error("Invalid parameter\n");
		return -EINVAL;
	}

	if ((cq->rear + 1) % MAXSIZE == cq->front) {
		printf("Cycle queue is full\n");
		return 0;
	}

	*(cq->base + cq->rear) = value;
	cq->rear = (cq->rear + 1) % MAXSIZE;
	return 0;
}

/* return directly when cycle queue is empty */
int de_cycle(cycle *cq, TYPE *value)
{
	if (!cq) {
		error("Invalid parameter\n");
		return -EINVAL;
	}

	//check empty
	if (cq->rear == cq->front) {
		printf("Cycle queue is empty\n");
		return 0;
	}

	*value = *(cq->base + cq->front);
	cq->front = (cq->front + 1) % MAXSIZE;
	return 0;
}

int print_cycle(cycle *cq)
{
	int temp;
	temp = cq->front;
	while (temp != cq->rear) {
		printf("item %d is %d\n", temp, *(cq->base + temp));
		temp = (temp + 1) % MAXSIZE;
	}

	return 0;
}

int destroy_cycle(cycle *cq)
{
	if (!cq->base) {
		error("base is NULL\n");
		return -EINVAL;
	}
	free(cq->base);

	cq->front = cq->rear = 0;
	return 0;
}
