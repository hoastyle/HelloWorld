#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define DEBUG 1
#ifdef DEBUG
void debug(const char *format, ...)
{
	va_list arg;
	
	va_start(arg, format);
	//output to stdout
	vprintf(format, arg);
	va_end(arg);
}
#else
void debug(const char*format, ...)
{}
#endif

void die(const char *format, ...)
{
	va_list arg;

	va_start(arg, format);
	vprintf(format, arg);
	va_end(arg);

	exit(1);
}
	
//#define debug1(fmt, arg...) printf(fmt, arg)
#define debug2(fmt, arg...) printf(fmt, ##arg)
//#define debug3(fmt, ...) printf(fmt, __VA_ARGS__)
#define debug4(fmt, ...) printf(fmt, ##__VA_ARGS__)

///* The debug macro with ## have a better robustness */
//int main()
//{
//	char *var = "world";
//	int var1 = 1, var2 = 2;
//	debug("hello %s %d %d\n", var, var1, var2);
//	debug("hello\n");
////	debug1("hello %s\n", var);
//	debug2("hello %s\n", var);
////	debug3("hello %s\n", var);
//	debug4("hello %s\n", var);
//
////	debug1("hello");
//	debug2("hello\n");
////	debug3("hello");
//	debug4("hello\n");
//	return 0;
//}
