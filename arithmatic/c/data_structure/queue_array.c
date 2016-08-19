#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "error.h"

#define QUEUE_SIZE 10
#define MAXSIZE ((QUEUE_SIZE) + 1)

typedef struct {
	int *queue;
	int front;
	int rear;
} queue, *pQueue;

int i;

int init_queue(queue *queue)
{
	if (!queue) {
		error("Failed to init queue, invalid parameter\n");
		return -EINVAL;
	}

	queue->queue = (int *)malloc(sizeof(int)*MAXSIZE);
	if (!queue->queue) {
		error("Failed to init queue, no mem\n");
	}

	queue->front = queue->rear = 0;

	return 0;
}

int en_queue(queue *queue, int value)
{
	if ((queue->front + 1) % MAXSIZE == queue->rear) {
		error("Full\n");
		return -1;
	}

	*(queue->queue + queue->front) = value;
	queue->front = (queue->front + 1) % MAXSIZE;

	return 0;
}

int de_queue(queue *queue, int *value)
{
	if (queue->front == queue->rear) {
		error("Empty\n");
		return -1;
	}

	*value = *(queue->queue + queue->rear);
	queue->rear = (queue->rear + 1) % MAXSIZE;

	return 0;
}

int print_queue(queue *queue)
{
	if (queue->front > queue->rear) {
		for (i = queue->rear; i < queue->front; i++)
			printf("queue %d is %d\n", i - queue->rear, *(queue->queue + i));
	} else if (queue->front < queue->rear) {
		for (i = queue->rear; i < MAXSIZE; i++)
			printf("queue %d is %d\n", i - queue->rear, *(queue->queue + i));
		for (i = 0; i < queue->front; i++)
			printf("queue %d is %d\n", MAXSIZE - queue->rear + 1 + i, *(queue->queue + i));
	} else
		printf("queue is empty\n");

	return 0;
}

void main()
{
	queue queue;
	int ret;
	int value;

	ret = init_queue(&queue);
	for (i = 0; i < 12; i++) {
		ret = en_queue(&queue, i);
		if (ret == -1)
			printf("error\n");
	}

	print_queue(&queue);

	for (i = 0; i < 4; i++) {
		ret = de_queue(&queue, &value);
		if (!ret)
			printf("get %d\n", value);
		else
			printf("error\n");
	}

	print_queue(&queue);
	return;
}
