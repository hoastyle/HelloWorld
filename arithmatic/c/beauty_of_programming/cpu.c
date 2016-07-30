#include <stdio.h>

int main()
{
	int i;
	for(;;)
	{
		for(i = 0; i < 9600000; i++)
			;
		sleep(10);
	}
	return 0;
}
