/* List */
//not complete
#include "common.h"

static pList medium = NULL;
static pList next = NULL;
static pList prev = NULL;

/* 
 * 头部，prev 为 NULL
 * 尾部，next 为 NULL
 * 开始，prev == next == NULL
 */
int list_init_head(list *head)
{
	if (!head) {
		error("list head is NULL\n");
		return -1;
	}

	head->value = 0;
	head->next = NULL;
	head->prev = NULL;

	return 0;
}

int list_init_node(list *node, TYPE value)
{
	node = (list *)malloc(sizeof(list));
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
}

/* 
 * 在指定的node后面插入node
 * - 1. 找到指定node
 * - 2. 将指定node->next指向new, new->next指向原来的下一个，原来的下一个的prev指向new
 */
int list_insert(list *head, list node, list ins)
{
	//check list
	if (!head) {
		error("INVALID head");
		return -EINVAL;
	}

	medium = head->next;
	if (!medium && (&node == head)) {
		head->next = &ins;
		ins.next = NULL;
		ins.prev = head;
	}

	//search node
	while(medium) {
		if (medium == &node) {
			next = node.next;
			node.next = &ins;
			ins.next = next;
			ins.prev = &node;
			if (next)
				next->prev = &ins;
			break;
		}
		medium = medium->next;
		if (!medium) {
			error("Did not find the target node\n");
			return -EINVAL;
		}
	}

	return 0;
}

int list_delete(list *head, list node)
{
	//check list
	if (!head || !(head->next)) {
		error("INVALID head");
		return -EINVAL;
	}

	medium = head->next;
	while (medium) {
		if (medium == &node) {
			next = node.next;
			prev = node.prev;
			prev->next = next;
			if (next)
				next->prev = prev;
			break;
		}
		medium = medium->next;
		if (!medium)
			error("Did not find the target node\n");
			return -EINVAL;
	}

	return 0;
}

int list_destroy(list *head)
{
}
