#ifndef _dbg_h_
#define _dbg_h_

#include <stdio.h>
#include <errno.h>
#include <string.h>

/* error handling function is written by yourself*/
#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, "[ERROR] %s:%d error: %s" M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN] %s:%d error: %s" M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] %s:%d error: %s" M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) {log_err(M, ##__VA_ARGS__); errno = 0; goto error;}

/* sentinel is placed in any part of a function that shouldn't run, and if it does prints an error message then jumps to the error: label. You put this in if-statements and switch-statements to catch conditions that shouldn't happen, like the default:. */
#define sentinel(M, ...) {log_err(M, ##__VA_ARGS__); errno = 0; goto error;}

/* makes sure a pointer is valid, and if it isn't reports it as an error with "Out of memory." */
#define check_mem(A) check((A), "Out of memory.")

/*  */
#define check_debug(A, M, ...) if(!(A)) {debug(M, ##__VA_ARGS__); errno = 0; goto error;}

#endif
