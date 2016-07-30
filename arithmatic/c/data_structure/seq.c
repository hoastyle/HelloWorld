/* Sequence list */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "error.h"
#include "common.h"

//思考，如果发生错误，应该在主函数中处理还是在function中就进行处理
/* Sequence operation */
/* Initialization */
int seq_init(seqlist *list)
{
	if (!list) {
		error("list pointer is NULl\n");
		return -1;
	}

	list->seq = (TYPE *)malloc(MAXSIZE * sizeof(TYPE));
	if (!list->seq) {
		error("seq list alloc failed\n");
		return -1;
	}
	list->length = 0;
	list->size = MAXSIZE;
	return 0;
}

/* Set value */
int seq_set(seqlist *list, int set_loc, TYPE value)
{
	if (!list) {
		error("list pointer is NULl\n");
		return -1;
	}

	if (!list->seq) {
		error("seq is NULl\n");
		return -1;
	}

	//考虑set_loc为负数的情况，允许为负数的情况，不允许为负数的情况
	if (abs(set_loc) >= list->size) {
		error("set location is beyond the limitation\n");
		return -1;
	} else {
		if(set_loc >= 0)
			*(list->seq + set_loc) = value;
		else
			*(list->seq + list->size - abs(set_loc)) = value;
		list->length++;
	}
	return 0;
}

int seq_clear(seqlist *list, int clear_loc)
{
	if (!list) {
		error("list pointer is NULl\n");
		return -1;
	}

	if (!list->seq) {
		error("seq is NULl\n");
		return -1;
	}

	//考虑set_loc为负数的情况，允许为负数的情况，不允许为负数的情况
	if (abs(clear_loc) >= list->size) {
		error("clear location is beyond the limitation\n");
		return -1;
	} else {
		if(clear_loc >= 0)
			*(list->seq + clear_loc) = 0;
		else
			*(list->seq + list->size - abs(clear_loc)) = 0;
		list->length--;
	}
	return 0;
}

/* Insert */
//int seq_insert(seqlist *list, int ins_loc, TYPE value)
//{
//	if (!list) {
//		error("seq list pointer is NULl\n");
//		return -1;
//	}
//
//	if ( ins_loc >= 0 && ins_loc < (list->size - 1)) {
//		list->seq = (TYPE *)malloc(list->size + 1);
//		list->size += 1;
//		list->length += 1;
//		for (i = list->size; i > ins_loc; i--)
//			*(list->seq + i - 1) = *(list->seq + i -2);
//		*(list->seq + ins_loc + 1) = value;
//	} elseif ( ins_loc < 0 && 2 < abs(ins_loc) < list->size) {
//	} else {
//		error("insert location is beyond the limitation\n");
//		return -1;
//	}
//
//	return 0;
//}
//
///* Delete */
//int seq_delete()
//{
//
//}

/* Free */
int seq_free(seqlist *list)
{
	if (!list) {
		error("list pointer is NULl\n");
		return -1;
	}

	if (!list->seq) {
		error("seq is NULl\n");
		return -1;
	}

	free(list->seq);
	list->length = 0;
	list->size = 0;

	return 0;
}
