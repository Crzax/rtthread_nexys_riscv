#include "utils.h"
#include <rtthread.h>
#include <board.h>
void continue_next(void) 
{
    rt_kprintf("请置状态为sw[15,14]=10来退出\n");
    while (1) 
    { 
        unsigned int value = READ_SW();
        if (((value >> 15) & 1) == 1 && ((value >> 14) & 1) == 0) 
            return;
    }
}