
/* for rt-thread code porting */

#ifndef __RTDBG_H__
#define __RTDBG_H__
#include <utils_log.h>

/* debug */
#define RT_ASSERT(x)    do { \
    if (!(x)) { \
        printf("%d:ASSERT_ERR(" #x ")\n", __LINE__); \
    } \
} while(0)

#define LOG_E       log_error
#define LOG_D       log_debug
#define LOG_RAW     printf

#endif

