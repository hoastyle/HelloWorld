#include <stdio.h>
#include "common.h"

void main()
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
}
