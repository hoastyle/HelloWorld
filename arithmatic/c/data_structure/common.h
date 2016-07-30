/* For sequence definition, defined in seq.c*/
#define TYPE int
#define MAXSIZE 10

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
