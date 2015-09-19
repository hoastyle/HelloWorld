#include <stdio.h>
#include <stdarg.h>

void debug(const char *format, ...)
{
	va_list arg;
	
	va_start(arg, format);
	//output to stdout
	vprintf(format, arg);
	va_end(arg);
}

#define debug1(fmt, arg...) printf(fmt, arg)
#define debug2(fmt, arg...) printf(fmt, ##arg)
#define debug3(fmt, ...) printf(fmt, __VA_ARGS__)
#define debug4(fmt, ...) printf(fmt, ##__VA_ARGS__)

/* The debug macro with ## have a better robustness */
int main()
{
	char *var = "world";
	int var1 = 1, var2 = 2;
	debug("hello %s %d %d\n", var, var1, var2);
	debug1("hello %s\n", var);
	debug2("hello %s\n", var);
	debug3("hello %s\n", var);
	debug4("hello %s\n", var);

	debug1("hello");
	debug2("hello");
	debug3("hello");
	debug4("hello");
	return 0;
}
