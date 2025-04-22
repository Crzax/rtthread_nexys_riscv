#include <rtthread.h>
#include "appdef.h"
#include "utils.h"

#define GPIO_LEDs   0x80001404
#define GPIO_INOUT  0x80001408

#define READ_GPIO(dir) (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, value) { (*(volatile unsigned *)dir) = (value); }

static rt_thread_t tid = RT_NULL;

// 跑马灯线程函数
void led_marquee_thread(void *parameter)
{
    uint16_t mask = 0x0001; // 初始点亮第一个LED
    int switches_value;
    // 设置GPIO为输出模式（假设0xFFFF表示全输出）
    WRITE_GPIO(GPIO_INOUT, 0xFFFF);

    while (1)
    { 
        // 写入当前mask到LED
        WRITE_GPIO(GPIO_LEDs, mask);

        // 使用系统tick实现100ms间隔（替代延时函数）
        uint32_t start_tick = rt_tick_get();
        switches_value = READ_GPIO(GPIO_SWs);
        switches_value = switches_value >> 16;
        if (((switches_value >> 15) & 1) == 1 && ((switches_value >> 14) & 1) == 0) {
            WRITE_GPIO(GPIO_LEDs, 0x0000); // 关闭LED
            rt_kprintf("LED Marquee stopped.\n");
            return;
        }
        while (rt_tick_get() - start_tick < RT_TICK_PER_SECOND / 10)
        {
            // 忙等待时让出CPU（关键优化！）
            rt_schedule();
        }

        // 移动mask（左移后循环）
        mask <<= 1;
        if (mask == 0) mask = 0x0001; // 防止溢出后变为0
    }
}

// 退出线程
static rt_thread_t tid_exit = RT_NULL;
void exitApp_LED1(void *parameter){
    continue_next ();
}

int led_marquee() {
    // 创建跑马灯线程
    tid = rt_thread_create("led_marquee",
                           led_marquee_thread, RT_NULL,
                           THREAD_STACK_SIZE,
                           THREAD_PRIORITY,
                           THREAD_TIMESLICE);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    // 退出线程
    tid_exit = rt_thread_create("extApp_switch_led",
                            exitApp_LED1, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);

    if (tid_exit != RT_NULL)
        rt_thread_startup(tid_exit);

    return 0;
}

MSH_CMD_EXPORT(led_marquee, Run 16-LED Marquee Effect);
