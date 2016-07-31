/* common header file */
#include <stdio.h>
#include <errno.h>
#include "error.h"

#define TYPE int
#define MAXSIZE 10

/* For sequence definition, defined in seq.c*/
typedef struct {
	TYPE *seq;  //sequence pointer
	int length; //actual length
	int size;   //sequence size
} seqlist;

int seq_init(seqlist *);
int seq_set(seqlist *, int, TYPE);
int seq_clear(seqlist *, int);
int seq_free(seqlist *);

/* For list definition, defined in list.c */
typedef struct node {
	TYPE value;
	struct node* next;
	struct node* prev;
} list, *pList;

int list_init_head(list *);
int list_insert(list *, list, list);
int list_delete(list *, list);
int list_destroy(list *);

/* stack */
typedef struct {
	TYPE *base;
	TYPE *top;
	int size;
} stk, *pStk;

int init_stack(stk *);
int push_stack(stk *, TYPE);
int pop_stack(stk *, TYPE *);
int print_stack(stk *);
int empty_stack(stk *);
int length_stack(stk *, int *);
int destroy_stack(stk *);

/* queue */
typedef struct q_node {
	TYPE data;
	struct q_node *next;
} qNode, *pQNode;

typedef struct {
	qNode *front;
	qNode *rear;
} qList, pQList;

int init_queue(qList *);
int en_queue(qList *, TYPE);
int de_queue(qList *, TYPE *);
int print_queue(qList *);
int destroy_queue(qList *);

/* cycle queue */
typedef struct {
	TYPE *base;
	int front;
	int rear;
} cycle, *pCycle;

int init_cycle(cycle *);
int en_cycle(cycle *, TYPE);
int de_cycle(cycle *, TYPE *);
int print_cycle(cycle *);
int destroy_cycle(cycle *);
