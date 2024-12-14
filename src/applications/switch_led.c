#include <rtthread.h>
#include "appdef.h"
#define GPIO_SWs    0x80001400
#define GPIO_LEDs   0x80001404
#define GPIO_INOUT  0x80001408

#define READ_GPIO(dir) (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, value) { (*(volatile unsigned *)dir) = (value); }

static rt_thread_t tid = RT_NULL;
int switchLED ( void )
{
    int En_Value=0xFFFF, switches_value;

    WRITE_GPIO(GPIO_INOUT, En_Value);

    while (1) { 
        switches_value = READ_GPIO(GPIO_SWs);
        switches_value = switches_value >> 16;
        WRITE_GPIO(GPIO_LEDs, switches_value);
        rt_thread_mdelay(100);
    }

    return(0);
}
static rt_thread_t tid_exit = RT_NULL;
void exitApp_LED(){
    while(1){
        if(READ_SW()>>14==1){
            rt_kprintf("准备退出LED_SWITCH\n");
            rt_thread_delete(tid);
            rt_kprintf("成功退出LED_SWITCH\n");
            // startApp();
            // resume_appStart();
            continue_next();
            return;
        }
        rt_thread_delay(100);
    }
}
int switch_led() {
    tid = rt_thread_create("thread_switchLED",
                           switchLED, RT_NULL,
                           THREAD_STACK_SIZE,
                           THREAD_PRIORITY,
                           THREAD_TIMESLICE);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    tid_exit = rt_thread_create("extApp_switch_led",
                            exitApp_LED, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);

    
    /* 如果获得线程控制块，启动这个线程 */
    if (tid_exit != RT_NULL)
        rt_thread_startup(tid_exit);
    return 0;
    
}

void continue_next(void) {
    while (1) { 
        unsigned int value = READ_SW();
        if (((value >> 15) & 1) == 1 && ((value >> 14) & 1) == 0) {
            return;
        }
    }
}

/* 导出到 MSH 命令列表中 */
MSH_CMD_EXPORT(switch_led, Switch LED according to switches);