
#include <rtthread.h>

//#define REALLOC_DEBUG
#ifdef REALLOC_DEBUG
#include <stdio.h>
#include <cli.h>
#include <yd_log_print.h>
#endif

extern size_t xYdGetBlockSize(void *pv);

void *rt_calloc(size_t numitems, size_t size)
{
    size_t sizel = numitems * size;
    void *ptr = pvPortMallocDMA(sizel);
    memset(ptr, 0, sizel);
    return ptr;
}

void *rt_realloc(void *ptr, size_t size)
{
    size_t size_old = 0;
    void *p_tmp = NULL;

    size_old = xYdGetBlockSize(ptr);
#ifdef REALLOC_DEBUG
    printf("%s %d: size_old=0x%x\r\n", __FUNCTION__, __LINE__, size_old);
#endif

    /* if block size is enough, no need to alloc new block. */
    if (size_old >= size)
    {
        return ptr;
    }

    p_tmp = pvPortMallocDMA(size);

    if (p_tmp)
    {
        /* copy data from old ptr */
#ifdef REALLOC_DEBUG
        printf("%s %d: p_tmp=%p size=0x%x\r\n", __FUNCTION__, __LINE__, p_tmp, xYdGetBlockSize(p_tmp));
#endif

        memcpy(p_tmp, ptr, size_old);

    }

    vPortFreeDMA(ptr);

    return p_tmp;
}

char *rt_strdup(const char *src)
{
    void *p_tmp = pvPortMallocDMA(strlen(src)+1);
    if (p_tmp)
    {
        strcpy(p_tmp, src);
    }
    return p_tmp;
}


#ifdef REALLOC_DEBUG
#define print_free_mem() do {\
    printf("%s %d:", __FUNCTION__, __LINE__);\
    printf("free memory dma_memory:%d, dtcm_memory:%d, total:(%d) \r\n", xPortGetFreeHeapSizeDMA(), xPortGetFreeHeapSizeNoDMA(), xPortGetFreeHeapSize());\
}while(0)

static void test_cmd_realloc(char *buf, int len, int argc, char **argv)
{
    char *p = NULL;

    print_free_mem();

    p = rt_malloc(10);

    print_free_mem();

    if (p == NULL)
    {
        printf("malloc failed\r\n");
        return;
    }

    printf("p=%p\r\n", p);
    memset(p, 3, 10);

    p = rt_realloc(p, 20);

    print_free_mem();

    if (p == NULL)
    {
        printf("realloc failed\r\n");
        return;
    }

    printf("p=%p\r\n", p);
    yd_dump_data(YD_LOG_LEVEL_DEBUG, p, 20);

    p = rt_realloc(p, 80);

    print_free_mem();

    if (p == NULL)
    {
        printf("realloc 2 failed\r\n");
        return;
    }

    printf("p=%p\r\n", p);
    yd_dump_data(YD_LOG_LEVEL_DEBUG, p, 80);

    rt_free(p);

    print_free_mem();

    return;
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "realloc_test", "Test realloc function.", test_cmd_realloc},
};

int helper_yd_test_realloc_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}
#endif

