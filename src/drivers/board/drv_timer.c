/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-22     Jesven       first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#include "board.h"
#include "bsp_timer.h"
#include "bsp_external_interrupts.h"
#include "interrupt.h"
#include "components.h"
#include "rtdef.h"
#include "drv_timer.h"
#include "psp_interrupts_eh1.h"
#include "psp_api.h"

#define TIMER_HW_BASE                   D_TIMER_DURATION_SETUP_ADDRESS  // 使用新的定时器基地址

#include "psp_api.h"

void rt_hw_timer_isr(void)
{
    pspDisableInterruptNumberMachineLevel(D_PSP_INTERRUPTS_MACHINE_TIMER);

    rt_tick_increase();

    pspEnableInterruptNumberMachineLevel(D_PSP_INTERRUPTS_MACHINE_TIMER);
}

int rt_hw_timer_init(void)
{
    pspInterruptsSetVectorTableAddress(&psp_vect_table);
    pspRegisterInterruptHandler((pspInterruptHandler_t)rt_hw_timer_isr, E_MACHINE_TIMER_CAUSE);

    // pspEnableInterruptNumberMachineLevel(D_PSP_INTERRUPTS_MACHINE_TIMER); // 启用定时器中断

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_timer_init);


void timer_clear_pending(int timer)
{
#ifdef RT_USING_OLD
    // 假设每个定时器有不同的清除中断地址
    if (timer == 0)
    {
        TIMER_INTCLR(TIMER01_HW_BASE) = 0x01;
    } 
    else
    {
        TIMER_INTCLR(TIMER23_HW_BASE) = 0x01;
    }
#else
    M_PSP_WRITE_CSR(D_PSP_MITBND0_NUM, 0x01);
    M_PSP_WRITE_CSR(D_PSP_MITBND1_NUM, 0x01);
}
#endif