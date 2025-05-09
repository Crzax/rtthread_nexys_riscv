/*
* SPDX-License-Identifier: Apache-2.0
* Copyright 2019 Western Digital Corporation or its affiliates.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http:*www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
/**
* @author Ofer Shinaar
* @date   24.02.2020
* @brief  header file for printf
*/

#ifndef __BSP_PRINTF_H__
#define __BSP_PRINTF_H__

#include "psp_types.h"
#include <stdarg.h>
u32_t  printfNexys(const char * cFormat, ... );
void   uartInit(void);
void   printfSetUartStatus(u08_t ucStatus);
int    uart_printf(const char* ctrl1, va_list argp);
u08_t  printfGetUartStatus(void);

#endif //__BSP_PRINTF_H__
