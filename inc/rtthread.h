
/* for rt-thread code porting */

#ifndef __RTTHREAD_H__
#define __RTTHREAD_H__

#define OS_USING_FREERTOS
#ifdef OS_USING_FREERTOS
#include <FreeRTOS.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

/* base types */
#define RT_NULL     NULL

#define rt_bool_t   bool
#define RT_TRUE     true
#define RT_FALSE    false

#define rt_int32_t  int

/* error code */
#define RT_ENOMEM   12
#define RT_ERROR    1
#define RT_EOK      0

/* string / print */
#define rt_strlen   strlen
#define rt_strncpy  strncpy
#define rt_strstr   strstr
#define rt_vsnprintf    vsnprintf
#define rt_snprintf snprintf
#define rt_strcmp   strcmp

#define rt_kprintf  printf

/* memory */
#define rt_memset   memset
#define rt_malloc   pvPortMallocDMA
#define rt_free     vPortFreeDMA

/* misc */
#define rt_tick_from_millisecond(x) (x)

void *rt_calloc(size_t numitems, size_t size);
void *rt_realloc(void *ptr, size_t size);
char *rt_strdup(const char *src);

#endif

#endif

