/* stack */
#include "common.h"
#include <stdlib.h>

/* 
 * 首先定义栈的类型 
 * - 向上生长
 * - top指向最后一个元素，而不是最后的后一个元素
 */
int init_stack(stk *stack)
{
	stack->base = (TYPE *)malloc(sizeof(TYPE) * MAXSIZE);
	if (!stack->base) {
		error("Init failed, no mem\n");
		return -ENOMEM;
	}

	stack->size = MAXSIZE;
	stack->top = stack->base;
	return 0;
}

int push_stack(stk *stack, TYPE value)
{
	if (!stack->base) {
		error("Base is NULL, invalid parameter\n");
		return -EINVAL;
	}

	if (stack->top < (stack->base + stack->size)) {
		*stack->top = value;
		stack->top = stack->top + 1;
	} else if (stack->top == (stack->base + stack->size)) {
		printf("stack is full\n");
	}

	return 0;
}

int pop_stack(stk *stack, TYPE *value)
{
	if (!stack->base) {
		error("Base is NULL, invalid parameter\n");
		return -EINVAL;
	}

	if (stack->top == stack->base) {
		printf("stack is empty");
	} else {
		*value = *--stack->top;
	}

	return 0;
}

int print_stack(stk *stack)
{
	int i;

	if (!stack->base) {
		error("Base is NULL, invalid parameter\n");
		return -EINVAL;
	}

	printf("stack content is:\n");
	for (i = 0; i < (stack->top - stack->base); i++)
		printf("stack %d is %d\n", i, *(stack->base + i));

	return 0;
}

int empty_stack(stk *stack)
{
	if (!stack->base) {
		error("Base is NULL, invalid parameter\n");
		return -EINVAL;
	}

	stack->top = stack->base;
	return 0;
}

int length_stack(stk *stack, int *length)
{
	if (!stack->base) {
		error("Base is NULL, invalid parameter\n");
		return -EINVAL;
	}

	*length = stack->top - stack->base;
	return 0;
}

int destroy_stack(stk *stack)
{
	if (!stack->base) {
		error("Base is NULL, invalid parameter\n");
		return -EINVAL;
	}

	stack->top = stack->base;
	free(stack->base);
	return 0;
}
