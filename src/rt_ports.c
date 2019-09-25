
#include <rtthread.h>

void *rt_calloc(size_t numitems, size_t size)
{
    size_t sizel = numitems * size;
    void *ptr = pvPortMalloc(sizel);
    memset(ptr, 0, sizel);
    return ptr;
}

void *rt_realloc(void *ptr, size_t size)
{
    void *p_tmp = pvPortMalloc(size);
    if (p_tmp)
    {
        memset(p_tmp, 0, size);
    }
    vPortFree(ptr);

    return p_tmp;
}

char *rt_strdup(const char *src)
{
    void *p_tmp = pvPortMalloc(strlen(src)+1);
    if (p_tmp)
    {
        strcpy(p_tmp, src);
    }
    return p_tmp;
}

