/* a.c */

int c;
extern int shared;

int main()
{
	int b;
	int a = 100;
	swap(&a, &shared);
	return 0;
}
