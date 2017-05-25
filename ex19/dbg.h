#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n",\
                __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr,\
                "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__,\
                clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr,\
                "[WARN] (%s:%d: errno: %s) " M "\n",\
                __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n",\
                __FILE__, __LINE__, ##__VA_ARGS__)


/**
* check if condition A is true and if not log the error
***/
#define check(A, M, ...) if(!(A)) {\
        log_err(M, ##__VA_ARGS__); errno=0; goto error; }

// sentinel should be put in places which should never be reached or shouldn't happen
// to log them
#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__);\
        errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__);\
        errno=0; goto error; }

#endif
