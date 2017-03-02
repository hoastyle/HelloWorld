void show_bytes(unsigned char * start, int len);

void show_int(int x)
{
	show_bytes((unsigned char *)&x, sizeof(int));
}

void show_bytes(unsigned char * start, int len)
{
	int i;
	for(i = 0; i < len; i++) {
		printf("%.2x\n", *(start + i));
	}
}
