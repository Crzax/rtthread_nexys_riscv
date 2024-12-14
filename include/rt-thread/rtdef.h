/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2007-01-10     Bernard      the first version
 * 2008-07-12     Bernard      remove all rt_int8, rt_uint32_t etc typedef
 * 2010-10-26     yi.qiu       add module support
 * 2010-11-10     Bernard      add cleanup callback function in thread exit.
 * 2011-05-09     Bernard      use builtin va_arg in GCC 4.x
 * 2012-11-16     Bernard      change RT_NULL from ((void*)0) to 0.
 * 2012-12-29     Bernard      change the RT_USING_MEMPOOL location and add
 *                             RT_USING_MEMHEAP condition.
 * 2012-12-30     Bernard      add more control command for graphic.
 * 2013-01-09     Bernard      change version number.
 * 2015-02-01     Bernard      change version number to v2.1.0
 * 2017-08-31     Bernard      change version number to v3.0.0
 * 2017-11-30     Bernard      change version number to v3.0.1
 * 2017-12-27     Bernard      change version number to v3.0.2
 * 2018-02-24     Bernard      change version number to v3.0.3
 * 2018-04-25     Bernard      change version number to v3.0.4
 * 2018-05-31     Bernard      change version number to v3.1.0
 * 2018-09-04     Bernard      change version number to v3.1.1
 * 2018-09-14     Bernard      apply Apache License v2.0 to RT-Thread Kernel
 * 2018-10-13     Bernard      change version number to v4.0.0
 * 2018-10-02     Bernard      add 64bit arch support
 * 2018-11-22     Jesven       add smp member to struct rt_thread
 *                             add struct rt_cpu
 *                             add smp relevant macros
 * 2019-01-27     Bernard      change version number to v4.0.1
 * 2019-05-17     Bernard      change version number to v4.0.2
 * 2019-12-20     Bernard      change version number to v4.0.3
 * 2020-08-10     Meco Man     add macro for struct rt_device_ops
 * 2020-10-23     Meco Man     define maximum value of ipc type
 * 2021-03-19     Meco Man     add security devices
 * 2021-05-10     armink       change version number to v4.0.4
 * 2021-11-19     Meco Man     change version number to v4.1.0
 * 2021-12-21     Meco Man     re-implement RT_UNUSED
 * 2022-01-01     Gabriel      improve hooking method
 * 2022-01-07     Gabriel      move some __on_rt_xxxxx_hook to dedicated c source files
 * 2022-01-12     Meco Man     remove RT_THREAD_BLOCK
 * 2022-04-20     Meco Man     change version number to v4.1.1
 * 2022-04-21     THEWON       add macro RT_VERSION_CHECK
 * 2022-06-29     Meco Man     add RT_USING_LIBC and standard libc headers
 * 2022-08-16     Meco Man     change version number to v5.0.0
 * 2022-09-12     Meco Man     define rt_ssize_t
 * 2022-12-20     Meco Man     add const name for rt_object
 * 2023-04-01     Chushicheng  change version number to v5.0.1
 * 2023-05-20     Bernard      add stdc atomic detection.
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 * 2023-10-10     Chushicheng  change version number to v5.1.0
 * 2023-10-11     zmshahaha    move specific devices related and driver to components/drivers
 * 2023-11-21     Meco Man     add RT_USING_NANO macro
 * 2023-11-17     xqyjlj       add process group and session support
 * 2023-12-01     Shell        Support of dynamic device
 * 2023-12-18     xqyjlj       add rt_always_inline
 * 2023-12-22     Shell        Support hook list
 * 2024-01-18     Shell        Seperate basical types to a rttypes.h
 *                             Seperate the compiler portings to rtcompiler.h
 */

#ifndef __RT_DEF_H__
#define __RT_DEF_H__

/* include rtconfig header to import configuration */
#include <rtconfig.h>
#include <rtsched.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup BasicDef
 */

/**@{*/

/* RT-Thread version information */
#define RT_VERSION_MAJOR                5               /**< Major version number (X.x.x) */
#define RT_VERSION_MINOR                1               /**< Minor version number (x.X.x) */
#define RT_VERSION_PATCH                0               /**< Patch version number (x.x.X) */

/* RT-Thread version */
#define RTTHREAD_VERSION                ((RT_VERSION * 10000) + \
                                         (RT_SUBVERSION * 100) + RT_REVISION)

/* RT-Thread basic data type definitions */
#ifndef RT_USING_ARCH_DATA_TYPE
typedef signed   char                   rt_int8_t;      /**<  8bit integer type */
typedef signed   short                  rt_int16_t;     /**< 16bit integer type */
typedef signed   int                    rt_int32_t;     /**< 32bit integer type */
typedef unsigned char                   rt_uint8_t;     /**<  8bit unsigned integer type */
typedef unsigned short                  rt_uint16_t;    /**< 16bit unsigned integer type */
typedef unsigned int                    rt_uint32_t;    /**< 32bit unsigned integer type */

#ifdef ARCH_CPU_64BIT
typedef signed long                     rt_int64_t;     /**< 64bit integer type */
typedef unsigned long                   rt_uint64_t;    /**< 64bit unsigned integer type */
typedef unsigned long                   rt_size_t;      /**< Type for size number */
#else
typedef signed long long                rt_int64_t;     /**< 64bit integer type */
typedef unsigned long long              rt_uint64_t;    /**< 64bit unsigned integer type */
typedef unsigned int                    rt_size_t;      /**< Type for size number */
#endif /* ARCH_CPU_64BIT */
#endif /* RT_USING_ARCH_DATA_TYPE */

typedef int                             rt_bool_t;      /**< boolean type */
typedef long                            rt_base_t;      /**< Nbit CPU related date type */
typedef unsigned long                   rt_ubase_t;     /**< Nbit unsigned CPU related data type */

typedef rt_base_t                       rt_err_t;       /**< Type for error number */
typedef rt_uint32_t                     rt_time_t;      /**< Type for time stamp */
typedef rt_uint32_t                     rt_tick_t;      /**< Type for tick count */
typedef rt_base_t                       rt_flag_t;      /**< Type for flags */
typedef rt_ubase_t                      rt_dev_t;       /**< Type for device */
typedef rt_base_t                       rt_off_t;       /**< Type for offset */

/* boolean type definitions */
#define RT_TRUE                         1               /**< boolean true  */
#define RT_FALSE                        0               /**< boolean fails */

/**@}*/

/* maximum value of base type */
#define RT_UINT8_MAX                    0xff            /**< Maximum number of UINT8 */
#define RT_UINT16_MAX                   0xffff          /**< Maximum number of UINT16 */
#define RT_UINT32_MAX                   0xffffffff      /**< Maximum number of UINT32 */
#define RT_TICK_MAX                     RT_UINT32_MAX   /**< Maximum number of tick */

/* maximum value of ipc type */
#define RT_SEM_VALUE_MAX                RT_UINT16_MAX   /**< Maximum number of semaphore .value */
#define RT_MUTEX_VALUE_MAX              RT_UINT16_MAX   /**< Maximum number of mutex .value */
#define RT_MUTEX_HOLD_MAX               RT_UINT8_MAX    /**< Maximum number of mutex .hold */
#define RT_MB_ENTRY_MAX                 RT_UINT16_MAX   /**< Maximum number of mailbox .entry */
#define RT_MQ_ENTRY_MAX                 RT_UINT16_MAX   /**< Maximum number of message queue .entry */

#define RT_UNUSED(x)                   ((void)x)

/* Compiler Related Definitions */
#if defined(__ARMCC_VERSION)           /* ARM Compiler */
    #include <stdarg.h>
    #define RT_SECTION(x)               __attribute__((section(x)))
    #define RT_USED                     __attribute__((used))
    #define ALIGN(n)                    __attribute__((aligned(n)))
    #define RT_WEAK                     __attribute__((weak))
    #define rt_inline                   static __inline
    /* module compiling */
    #ifdef RT_USING_MODULE
        #define RTT_API                 __declspec(dllimport)
    #else
        #define RTT_API                 __declspec(dllexport)
    #endif /* RT_USING_MODULE */
#elif defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
    #include <stdarg.h>
    #define RT_SECTION(x)               @ x
    #define RT_USED                     __root
    #define PRAGMA(x)                   _Pragma(#x)
    #define ALIGN(n)                    PRAGMA(data_alignment=n)
    #define RT_WEAK                     __weak
    #define rt_inline                   static inline
    #define RTT_API
#elif defined (__GNUC__)                /* GNU GCC Compiler */
    #ifdef RT_USING_NEWLIB
        #include <stdarg.h>
    #else
        /* the version of GNU GCC must be greater than 4.x */
        typedef __builtin_va_list       __gnuc_va_list;
        typedef __gnuc_va_list          va_list;
        #define va_start(v,l)           __builtin_va_start(v,l)
        #define va_end(v)               __builtin_va_end(v)
        #define va_arg(v,l)             __builtin_va_arg(v,l)
    #endif /* RT_USING_NEWLIB */
    #define RT_SECTION(x)               __attribute__((section(x)))
    #define RT_USED                     __attribute__((used))
    #define ALIGN(n)                    __attribute__((aligned(n)))
    #define RT_WEAK                     __attribute__((weak))
    #define rt_inline                   static __inline
    #define RTT_API
#elif defined (__ADSPBLACKFIN__)        /* for VisualDSP++ Compiler */
    #include <stdarg.h>
    #define RT_SECTION(x)               __attribute__((section(x)))
    #define RT_USED                     __attribute__((used))
    #define ALIGN(n)                    __attribute__((aligned(n)))
    #define RT_WEAK                     __attribute__((weak))
    #define rt_inline                   static inline
    #define RTT_API
#elif defined (_MSC_VER)
    #include <stdarg.h>
    #define RT_SECTION(x)
    #define RT_USED
    #define ALIGN(n)                    __declspec(align(n))
    #define RT_WEAK
    #define rt_inline                   static __inline
    #define RTT_API
#elif defined (__TI_COMPILER_VERSION__)
    #include <stdarg.h>
    /* The way that TI compiler set section is different from other(at least
     * GCC and MDK) compilers. See ARM Optimizing C/C++ Compiler 5.9.3 for more
     * details. */
    #define RT_SECTION(x)
    #define RT_USED
    #define PRAGMA(x)                   _Pragma(#x)
    #define ALIGN(n)
    #define RT_WEAK
    #define rt_inline                   static inline
    #define RTT_API
#elif defined (__TASKING__)
    #include <stdarg.h>
    #define RT_SECTION(x)               __attribute__((section(x)))
    #define RT_USED                     __attribute__((used, protect))
    #define PRAGMA(x)                   _Pragma(#x)
    #define ALIGN(n)                    __attribute__((__align(n)))
    #define RT_WEAK                     __attribute__((weak))
    #define rt_inline                   static inline
    #define RTT_API
#else
    #error not supported tool chain
#endif

/* initialization export */
#ifdef RT_USING_COMPONENTS_INIT
typedef int (*init_fn_t)(void);
#ifdef _MSC_VER
#pragma section("rti_fn$f",read)
    #if RT_DEBUG_INIT
        struct rt_init_desc
        {
            const char* level;
            const init_fn_t fn;
            const char* fn_name;
        };
        #define INIT_EXPORT(fn, level)                                  \
                                const char __rti_level_##fn[] = ".rti_fn." level;       \
                                const char __rti_##fn##_name[] = #fn;                   \
                                __declspec(allocate("rti_fn$f"))                        \
                                RT_USED const struct rt_init_desc __rt_init_msc_##fn =  \
                                {__rti_level_##fn, fn, __rti_##fn##_name};
    #else
        struct rt_init_desc
        {
            const char* level;
            const init_fn_t fn;
        };
        #define INIT_EXPORT(fn, level)                                  \
                                const char __rti_level_##fn[] = ".rti_fn." level;       \
                                __declspec(allocate("rti_fn$f"))                        \
                                RT_USED const struct rt_init_desc __rt_init_msc_##fn =  \
                                {__rti_level_##fn, fn };
    #endif
#else
    #if RT_DEBUG_INIT
        struct rt_init_desc
        {
            const char* fn_name;
            const init_fn_t fn;
        };
        #define INIT_EXPORT(fn, level)                                                       \
            const char __rti_##fn##_name[] = #fn;                                            \
            RT_USED const struct rt_init_desc __rt_init_desc_##fn RT_SECTION(".rti_fn." level) = \
            { __rti_##fn##_name, fn};
    #else
        #define INIT_EXPORT(fn, level)                                                       \
            RT_USED const init_fn_t __rt_init_##fn RT_SECTION(".rti_fn." level) = fn
    #endif
#endif
#else
#define INIT_EXPORT(fn, level)
#endif

/* board init routines will be called in board_init() function */
#define INIT_BOARD_EXPORT(fn)           INIT_EXPORT(fn, "1")

/* pre/device/component/env/app init routines will be called in init_thread */
/* components pre-initialization (pure software initialization) */
#define INIT_PREV_EXPORT(fn)            INIT_EXPORT(fn, "2")
/* device initialization */
#define INIT_DEVICE_EXPORT(fn)          INIT_EXPORT(fn, "3")
/* components initialization (dfs, lwip, ...) */
#define INIT_COMPONENT_EXPORT(fn)       INIT_EXPORT(fn, "4")
/* environment initialization (mount disk, ...) */
#define INIT_ENV_EXPORT(fn)             INIT_EXPORT(fn, "5")
/* application initialization (rtgui application etc ...) */
#define INIT_APP_EXPORT(fn)             INIT_EXPORT(fn, "6")

#if !defined(RT_USING_FINSH)
/* define these to empty, even if not include finsh.h file */
#define FINSH_FUNCTION_EXPORT(name, desc)
#define FINSH_FUNCTION_EXPORT_ALIAS(name, alias, desc)

#define MSH_CMD_EXPORT(command, desc)
#define MSH_CMD_EXPORT_ALIAS(command, alias, desc)
#elif !defined(FINSH_USING_SYMTAB)
#define FINSH_FUNCTION_EXPORT_CMD(name, cmd, desc)
#endif

/* event length */
#define RT_EVENT_LENGTH                 32

/* memory management option */
#define RT_MM_PAGE_SIZE                 4096
#define RT_MM_PAGE_MASK                 (RT_MM_PAGE_SIZE - 1)
#define RT_MM_PAGE_BITS                 12

/* kernel malloc definitions */
#ifndef RT_KERNEL_MALLOC
#define RT_KERNEL_MALLOC(sz)            rt_malloc(sz)
#endif

#ifndef RT_KERNEL_FREE
#define RT_KERNEL_FREE(ptr)             rt_free(ptr)
#endif

#ifndef RT_KERNEL_REALLOC
#define RT_KERNEL_REALLOC(ptr, size)    rt_realloc(ptr, size)
#endif

/**
 * @addtogroup Error
 */

/**@{*/

/* RT-Thread error code definitions */
#if defined(RT_USING_LIBC) && !defined(RT_USING_NANO)
/* POSIX error code compatible */
#define RT_EOK                          0               /**< There is no error */
#define RT_ERROR                        255             /**< A generic/unknown error happens */
#define RT_ETIMEOUT                     ETIMEDOUT       /**< Timed out */
#define RT_EFULL                        ENOSPC          /**< The resource is full */
#define RT_EEMPTY                       ENODATA         /**< The resource is empty */
#define RT_ENOMEM                       ENOMEM          /**< No memory */
#define RT_ENOSYS                       ENOSYS          /**< Function not implemented */
#define RT_EBUSY                        EBUSY           /**< Busy */
#define RT_EIO                          EIO             /**< IO error */
#define RT_EINTR                        EINTR           /**< Interrupted system call */
#define RT_EINVAL                       EINVAL          /**< Invalid argument */
#define RT_ENOENT                       ENOENT          /**< No entry */
#define RT_ENOSPC                       ENOSPC          /**< No space left */
#define RT_EPERM                        EPERM           /**< Operation not permitted */
#define RT_EFAULT                       EFAULT          /**< Bad address */
#define RT_ENOBUFS                      ENOBUFS         /**< No buffer space is available */
#define RT_ESCHEDISR                    253             /**< scheduler failure in isr context */
#define RT_ESCHEDLOCKED                 252             /**< scheduler failure in critical region */
#define RT_ETRAP                        254             /**< Trap event */
#else
#define RT_EOK                          0               /**< There is no error */
#define RT_ERROR                        1               /**< A generic/unknown error happens */
#define RT_ETIMEOUT                     2               /**< Timed out */
#define RT_EFULL                        3               /**< The resource is full */
#define RT_EEMPTY                       4               /**< The resource is empty */
#define RT_ENOMEM                       5               /**< No memory */
#define RT_ENOSYS                       6               /**< Function not implemented */
#define RT_EBUSY                        7               /**< Busy */
#define RT_EIO                          8               /**< IO error */
#define RT_EINTR                        9               /**< Interrupted system call */
#define RT_EINVAL                       10              /**< Invalid argument */
#define RT_ENOENT                       11              /**< No entry */
#define RT_ENOSPC                       12              /**< No space left */
#define RT_EPERM                        13              /**< Operation not permitted */
#define RT_ETRAP                        14              /**< Trap event */
#define RT_EFAULT                       15              /**< Bad address */
#define RT_ENOBUFS                      16              /**< No buffer space is available */
#define RT_ESCHEDISR                    17              /**< scheduler failure in isr context */
#define RT_ESCHEDLOCKED                 18              /**< scheduler failure in critical region */
#endif /* defined(RT_USING_LIBC) && !defined(RT_USING_NANO) */

/**@}*/

/**
 * @ingroup BasicDef
 *
 * @def RT_ALIGN(size, align)
 * Return the most contiguous size aligned at specified width. RT_ALIGN(13, 4)
 * would return 16.
 */
#define RT_ALIGN(size, align)           (((size) + (align) - 1) & ~((align) - 1))

/**
 * @ingroup BasicDef
 *
 * @def RT_ALIGN_DOWN(size, align)
 * Return the down number of aligned at specified width. RT_ALIGN_DOWN(13, 4)
 * would return 12.
 */
#define RT_ALIGN_DOWN(size, align)      ((size) & ~((align) - 1))

/**
 * @ingroup BasicDef
 *
 * @def RT_NULL
 * Similar as the \c NULL in C library.
 */
#define RT_NULL                         (0)

/**
 * Double List structure
 */
struct rt_list_node
{
    struct rt_list_node *next;                          /**< point to next node. */
    struct rt_list_node *prev;                          /**< point to prev node. */
};
typedef struct rt_list_node rt_list_t;                  /**< Type for lists. */

/**
 * Single List structure
 */
struct rt_slist_node
{
    struct rt_slist_node *next;                         /**< point to next node. */
};
typedef struct rt_slist_node rt_slist_t;                /**< Type for single list. */

/**
 * @addtogroup KernelObject
 */

/**@{*/

/*
 * kernel object macros
 */
#define RT_OBJECT_FLAG_MODULE           0x80            /**< is module object. */

/**
 * Base structure of Kernel object
 */
struct rt_object
{
    char       name[RT_NAME_MAX];                       /**< name of kernel object */
    rt_uint8_t type;                                    /**< type of kernel object */
    rt_uint8_t flag;                                    /**< flag of kernel object */

#ifdef RT_USING_MODULE
    void      *module_id;                               /**< id of application module */
#endif
    rt_list_t  list;                                    /**< list node of kernel object */
};
typedef struct rt_object *rt_object_t;                  /**< Type for kernel objects. */

/**
 *  The object type can be one of the follows with specific
 *  macros enabled:
 *  - Thread
 *  - Semaphore
 *  - Mutex
 *  - Event
 *  - MailBox
 *  - MessageQueue
 *  - MemHeap
 *  - MemPool
 *  - Device
 *  - Timer
 *  - Module
 *  - Unknown
 *  - Static
 */
enum rt_object_class_type
{
    RT_Object_Class_Null          = 0x00,      /**< The object is not used. */
    RT_Object_Class_Thread        = 0x01,      /**< The object is a thread. */
    RT_Object_Class_Semaphore     = 0x02,      /**< The object is a semaphore. */
    RT_Object_Class_Mutex         = 0x03,      /**< The object is a mutex. */
    RT_Object_Class_Event         = 0x04,      /**< The object is a event. */
    RT_Object_Class_MailBox       = 0x05,      /**< The object is a mail box. */
    RT_Object_Class_MessageQueue  = 0x06,      /**< The object is a message queue. */
    RT_Object_Class_MemHeap       = 0x07,      /**< The object is a memory heap. */
    RT_Object_Class_MemPool       = 0x08,      /**< The object is a memory pool. */
    RT_Object_Class_Device        = 0x09,      /**< The object is a device. */
    RT_Object_Class_Timer         = 0x0a,      /**< The object is a timer. */
    RT_Object_Class_Module        = 0x0b,      /**< The object is a module. */
    RT_Object_Class_Memory        = 0x0c,      /**< The object is a memory. */
    RT_Object_Class_Channel       = 0x0d,      /**< The object is a channel */
    RT_Object_Class_ProcessGroup  = 0x0e,      /**< The object is a process group */
    RT_Object_Class_Session       = 0x0f,      /**< The object is a session */
    RT_Object_Class_Custom        = 0x10,      /**< The object is a custom object */
    RT_Object_Class_Unknown       = 0x11,      /**< The object is unknown. */
    RT_Object_Class_Static        = 0x80       /**< The object is a static object. */
};

/**
 * The information of the kernel object
 */
struct rt_object_information
{
    enum rt_object_class_type type;                     /**< object class type */
    rt_list_t                 object_list;              /**< object list */
    rt_size_t                 object_size;              /**< object size */
};

/**
 * The hook function call macro
 */
#ifndef RT_USING_HOOK
    #define __ON_HOOK_ARGS(__hook, argv)
    #define RT_OBJECT_HOOK_CALL(func, argv)
#else
    #define RT_OBJECT_HOOK_CALL(func, argv)         __on_##func argv
    #ifdef RT_HOOK_USING_FUNC_PTR
        #define __ON_HOOK_ARGS(__hook, argv)        do {if ((__hook) != RT_NULL) __hook argv; } while (0)
    #else
        #define __ON_HOOK_ARGS(__hook, argv)
    #endif
#endif

#ifndef __on_rt_interrupt_switch_hook
    #define __on_rt_interrupt_switch_hook()         __ON_HOOK_ARGS(rt_interrupt_switch_hook, ())
#endif
#ifndef __on_rt_malloc_hook
    #define __on_rt_malloc_hook(addr, size)         __ON_HOOK_ARGS(rt_malloc_hook, (addr, size))
#endif
#ifndef __on_rt_free_hook
    #define __on_rt_free_hook(rmem)                 __ON_HOOK_ARGS(rt_free_hook, (rmem))
#endif

#ifdef RT_USING_HOOKLIST

/**
 * @brief Add declaration for hook list types.
 *
 * @note Usage:
 * This is typically used in your header. In foo.h using this like:
 *
 * ```foo.h
 *     typedef void (*bar_hook_proto_t)(arguments...);
 *     RT_OBJECT_HOOKLIST_DECLARE(bar_hook_proto_t, bar_myhook);
 * ```
 */
#define RT_OBJECT_HOOKLIST_DECLARE(handler_type, name) \
    typedef struct name##_hooklistnode                 \
    {                                                  \
        handler_type handler;                          \
        rt_list_t list_node;                           \
    } *name##_hooklistnode_t;                          \
    extern volatile rt_ubase_t name##_nested;          \
    void name##_sethook(name##_hooklistnode_t node);   \
    void name##_rmhook(name##_hooklistnode_t node)

/**
 * @brief Add declaration for hook list node.
 *
 * @note Usage
 * You can add a hook like this.
 *
 * ```addhook.c
 * void myhook(arguments...) { do_something(); }
 * RT_OBJECT_HOOKLIST_DEFINE_NODE(bar_myhook, myhook_node, myhook);
 *
 * void addhook(void)
 * {
 *      bar_myhook_sethook(myhook);
 * }
 * ```
 *
 * BTW, you can also find examples codes under
 * `examples/utest/testcases/kernel/hooklist_tc.c`.
 */
#define RT_OBJECT_HOOKLIST_DEFINE_NODE(hookname, nodename, hooker_handler) \
    struct hookname##_hooklistnode nodename = {                            \
        .handler = hooker_handler,                                         \
        .list_node = RT_LIST_OBJECT_INIT(nodename.list_node),              \
    };

/**
 * @note Usage
 * Add this macro to the source file where your hook point is inserted.
 */
#define RT_OBJECT_HOOKLIST_DEFINE(name)                                      \
    static rt_list_t name##_hooklist = RT_LIST_OBJECT_INIT(name##_hooklist); \
    static struct rt_spinlock name##lock = RT_SPINLOCK_INIT;                 \
    volatile rt_ubase_t name##_nested = 0;                                   \
    void name##_sethook(name##_hooklistnode_t node)                          \
    {                                                                        \
        rt_ubase_t level = rt_spin_lock_irqsave(&name##lock);                \
        while (name##_nested)                                                \
        {                                                                    \
            rt_spin_unlock_irqrestore(&name##lock, level);                   \
            level = rt_spin_lock_irqsave(&name##lock);                       \
        }                                                                    \
        rt_list_insert_before(&name##_hooklist, &node->list_node);           \
        rt_spin_unlock_irqrestore(&name##lock, level);                       \
    }                                                                        \
    void name##_rmhook(name##_hooklistnode_t node)                           \
    {                                                                        \
        rt_ubase_t level = rt_spin_lock_irqsave(&name##lock);                \
        while (name##_nested)                                                \
        {                                                                    \
            rt_spin_unlock_irqrestore(&name##lock, level);                   \
            level = rt_spin_lock_irqsave(&name##lock);                       \
        }                                                                    \
        rt_list_remove(&node->list_node);                                    \
        rt_spin_unlock_irqrestore(&name##lock, level);                       \
    }

/**
 * @brief Add hook list point in the routines. Multiple hookers in the list will
 *        be called one by one starting from head node.
 *
 * @note Usage:
 * void foo() {
 *     do_something();
 *
 *     RT_OBJECT_HOOKLIST_CALL(foo);
 *
 *     do_other_things();
 * }
 */
#define _RT_OBJECT_HOOKLIST_CALL(nodetype, nested, list, lock, argv)  \
    do                                                                \
    {                                                                 \
        nodetype iter, next;                                          \
        rt_ubase_t level = rt_spin_lock_irqsave(&lock);               \
        nested += 1;                                                  \
        rt_spin_unlock_irqrestore(&lock, level);                      \
        if (!rt_list_isempty(&list))                                  \
        {                                                             \
            rt_list_for_each_entry_safe(iter, next, &list, list_node) \
            {                                                         \
                iter->handler argv;                                   \
            }                                                         \
        }                                                             \
        level = rt_spin_lock_irqsave(&lock);                          \
        nested -= 1;                                                  \
        rt_spin_unlock_irqrestore(&lock, level);                      \
    } while (0)
#define RT_OBJECT_HOOKLIST_CALL(name, argv)                        \
    _RT_OBJECT_HOOKLIST_CALL(name##_hooklistnode_t, name##_nested, \
                             name##_hooklist, name##lock, argv)

#else

#define RT_OBJECT_HOOKLIST_DECLARE(handler_type, name)
#define RT_OBJECT_HOOKLIST_DEFINE_NODE(hookname, nodename, hooker_handler)
#define RT_OBJECT_HOOKLIST_DEFINE(name)
#define RT_OBJECT_HOOKLIST_CALL(name, argv)
#endif /* RT_USING_HOOKLIST */

/**@}*/

/**
 * @addtogroup Clock
 */

/**@{*/

/**
 * clock & timer macros
 */
#define RT_TIMER_FLAG_DEACTIVATED       0x0             /**< timer is deactive */
#define RT_TIMER_FLAG_ACTIVATED         0x1             /**< timer is active */
#define RT_TIMER_FLAG_PROCESSING        0x2             /**< timer's timeout fuction is processing */
#define RT_TIMER_FLAG_ONE_SHOT          0x0             /**< one shot timer */
#define RT_TIMER_FLAG_PERIODIC          0x4             /**< periodic timer */

#define RT_TIMER_FLAG_HARD_TIMER        0x0             /**< hard timer,the timer's callback function will be called in tick isr. */
#define RT_TIMER_FLAG_SOFT_TIMER        0x8             /**< soft timer,the timer's callback function will be called in timer thread. */
#define RT_TIMER_FLAG_THREAD_TIMER \
    (0x10 | RT_TIMER_FLAG_HARD_TIMER)                    /**< thread timer that cooperates with scheduler directly */

#define RT_TIMER_CTRL_SET_TIME          0x0             /**< set timer control command */
#define RT_TIMER_CTRL_GET_TIME          0x1             /**< get timer control command */
#define RT_TIMER_CTRL_SET_ONESHOT       0x2             /**< change timer to one shot */
#define RT_TIMER_CTRL_SET_PERIODIC      0x3             /**< change timer to periodic */
#define RT_TIMER_CTRL_GET_STATE         0x4             /**< get timer run state active or deactive*/
#define RT_TIMER_CTRL_GET_REMAIN_TIME   0x5             /**< get the remaining hang time */
#define RT_TIMER_CTRL_GET_FUNC          0x6             /**< get timer timeout func  */
#define RT_TIMER_CTRL_SET_FUNC          0x7             /**< set timer timeout func  */
#define RT_TIMER_CTRL_GET_PARM          0x8             /**< get timer parameter  */
#define RT_TIMER_CTRL_SET_PARM          0x9             /**< get timer parameter  */

#ifndef RT_TIMER_SKIP_LIST_LEVEL
#define RT_TIMER_SKIP_LIST_LEVEL          1
#endif

/* 1 or 3 */
#ifndef RT_TIMER_SKIP_LIST_MASK
#define RT_TIMER_SKIP_LIST_MASK         0x3             /**< Timer skips the list mask */
#endif

/**
 * timer structure
 */
struct rt_timer
{
    struct rt_object parent;                            /**< inherit from rt_object */

    rt_list_t        row[RT_TIMER_SKIP_LIST_LEVEL];

    void (*timeout_func)(void *parameter);              /**< timeout function */
    void            *parameter;                         /**< timeout function's parameter */

    rt_tick_t        init_tick;                         /**< timer timeout tick */
    rt_tick_t        timeout_tick;                      /**< timeout tick */
};
typedef struct rt_timer *rt_timer_t;

/**@}*/

/**
 * @addtogroup Signal
 */
#ifdef RT_USING_SIGNALS
#include <sys/signal.h>
typedef unsigned long rt_sigset_t;
typedef void (*rt_sighandler_t)(int signo);
typedef siginfo_t rt_siginfo_t;

#define RT_SIG_MAX          32
#endif
/**@}*/

/**
 * @addtogroup Thread
 */

/**@{*/

/*
 * Thread
 */

/*
 * thread state definitions
 */
#define RT_THREAD_INIT                       0x00                /**< Initialized status */
#define RT_THREAD_CLOSE                      0x01                /**< Closed status */
#define RT_THREAD_READY                      0x02                /**< Ready status */
#define RT_THREAD_RUNNING                    0x03                /**< Running status */

/*
 * for rt_thread_suspend_with_flag()
 */
enum
{
    RT_INTERRUPTIBLE = 0,
    RT_KILLABLE,
    RT_UNINTERRUPTIBLE,
};

#define RT_THREAD_SUSPEND_MASK               0x04
#define RT_SIGNAL_COMMON_WAKEUP_MASK         0x02
#define RT_SIGNAL_KILL_WAKEUP_MASK           0x01

#define RT_THREAD_SUSPEND_INTERRUPTIBLE      (RT_THREAD_SUSPEND_MASK)                                                             /**< Suspend interruptable 0x4 */
#define RT_THREAD_SUSPEND                    RT_THREAD_SUSPEND_INTERRUPTIBLE
#define RT_THREAD_SUSPEND_KILLABLE           (RT_THREAD_SUSPEND_MASK | RT_SIGNAL_COMMON_WAKEUP_MASK)                              /**< Suspend with killable 0x6 */
#define RT_THREAD_SUSPEND_UNINTERRUPTIBLE    (RT_THREAD_SUSPEND_MASK | RT_SIGNAL_COMMON_WAKEUP_MASK | RT_SIGNAL_KILL_WAKEUP_MASK) /**< Suspend with uninterruptable 0x7 */
#define RT_THREAD_STAT_MASK                  0x07

#define RT_THREAD_STAT_YIELD            0x08                /**< indicate whether remaining_tick has been reloaded since last schedule */
#define RT_THREAD_STAT_YIELD_MASK       RT_THREAD_STAT_YIELD

#define RT_THREAD_STAT_SIGNAL           0x10                /**< task hold signals */
#define RT_THREAD_STAT_SIGNAL_READY     (RT_THREAD_STAT_SIGNAL | RT_THREAD_READY)
#define RT_THREAD_STAT_SIGNAL_WAIT      0x20                /**< task is waiting for signals */
#define RT_THREAD_STAT_SIGNAL_PENDING   0x40                /**< signals is held and it has not been procressed */
#define RT_THREAD_STAT_SIGNAL_MASK      0xf0

/**
 * thread control command definitions
 */
#define RT_THREAD_CTRL_STARTUP          0x00                /**< Startup thread. */
#define RT_THREAD_CTRL_CLOSE            0x01                /**< Close thread. */
#define RT_THREAD_CTRL_CHANGE_PRIORITY  0x02                /**< Change thread priority. */
#define RT_THREAD_CTRL_INFO             0x03                /**< Get thread information. */
#define RT_THREAD_CTRL_BIND_CPU         0x04                /**< Set thread bind cpu. */

#ifdef RT_USING_SMP

#define RT_CPU_DETACHED                 RT_CPUS_NR          /**< The thread not running on cpu. */
#define RT_CPU_MASK                     ((1 << RT_CPUS_NR) - 1) /**< All CPUs mask bit. */

#ifndef RT_SCHEDULE_IPI
#define RT_SCHEDULE_IPI                 0
#endif

#ifndef RT_STOP_IPI
#define RT_STOP_IPI                     1
#endif

/**
 * CPUs definitions
 *
 */
struct rt_cpu
{
    struct rt_thread *current_thread;

    rt_uint16_t irq_nest;
    rt_uint8_t  irq_switch_flag;

    rt_uint8_t current_priority;
    rt_list_t priority_table[RT_THREAD_PRIORITY_MAX];
#if RT_THREAD_PRIORITY_MAX > 32
    rt_uint32_t priority_group;
    rt_uint8_t ready_table[32];
#else
    rt_uint32_t priority_group;
#endif

    rt_tick_t tick;
};

#endif

typedef void (*rt_thread_cleanup_t)(struct rt_thread *tid);

/**
 * Thread structure
 */
#define RT_USING_OLD
struct rt_thread
{
#ifdef RT_USING_OLD
 /* rt object */
    char        name[RT_NAME_MAX];                      /**< the name of thread */
    rt_uint8_t  type;                                   /**< type of object */
    rt_uint8_t  flags;                                  /**< thread's flags */
#ifdef RT_USING_MODULE
    void       *module_id;                              /**< id of application module */
#endif
#endif
    struct rt_object            parent;

#ifdef RT_USING_OLD
    rt_list_t   list;                                   /**< the object list */
#endif
    /* stack point and entry */
    void                        *sp;                    /**< stack point */
    void                        *entry;                 /**< entry */
    void                        *parameter;             /**< parameter */
    void                        *stack_addr;            /**< stack address */
    rt_uint32_t                 stack_size;             /**< stack size */

    /* error code */
    rt_err_t                    error;                  /**< error code */

#ifdef RT_USING_SMP
    rt_atomic_t                 cpus_lock_nest;         /**< cpus lock count */
#endif

    RT_SCHED_THREAD_CTX
    struct rt_timer             thread_timer;           /**< built-in thread timer */
    rt_thread_cleanup_t         cleanup;                /**< cleanup function when thread exit */

#ifdef RT_USING_MUTEX
    /* object for IPC */
    rt_list_t                   taken_object_list;
    rt_object_t                 pending_object;
#endif /* RT_USING_MUTEX */

#ifdef RT_USING_EVENT
    /* thread event */
    rt_uint32_t                 event_set;
    rt_uint8_t                  event_info;
#endif /* RT_USING_EVENT */

#ifdef RT_USING_SIGNALS
    rt_sigset_t                 sig_pending;            /**< the pending signals */
    rt_sigset_t                 sig_mask;               /**< the mask bits of signal */

#ifndef RT_USING_SMP
    void                        *sig_ret;               /**< the return stack pointer from signal */
#endif /* RT_USING_SMP */
    rt_sighandler_t             *sig_vectors;           /**< vectors of signal handler */
    void                        *si_list;               /**< the signal infor list */
#endif /* RT_USING_SIGNALS */

#ifdef RT_USING_CPU_USAGE
    rt_uint64_t                 duration_tick;          /**< cpu usage tick */
#endif /* RT_USING_CPU_USAGE */

#ifdef RT_USING_PTHREADS
    void                        *pthread_data;          /**< the handle of pthread data, adapt 32/64bit */
#endif /* RT_USING_PTHREADS */

    /* light weight process if present */
#ifdef RT_USING_SMART
    void                        *msg_ret;               /**< the return msg */

    void                        *lwp;                   /**< the lwp reference */
    /* for user create */
    void                        *user_entry;
    void                        *user_stack;
    rt_uint32_t                 user_stack_size;
    rt_uint32_t                 *kernel_sp;             /**< kernel stack point */
    rt_list_t                   sibling;                /**< next thread of same process */

    struct lwp_thread_signal    signal;                 /**< lwp signal for user-space thread */
    struct rt_user_context      user_ctx;               /**< user space context */
    struct rt_wakeup            wakeup_handle;          /**< wakeup handle for IPC */
    rt_atomic_t                 exit_request;           /**< pending exit request of thread */
    int                         tid;                    /**< thread ID used by process */
    int                         tid_ref_count;          /**< reference of tid */
    void                        *susp_recycler;         /**< suspended recycler on this thread */
    void                        *robust_list;           /**< pi lock, very carefully, it's a userspace list!*/

    rt_uint64_t                 user_time;
    rt_uint64_t                 system_time;

#ifndef ARCH_MM_MMU
    lwp_sighandler_t            signal_handler[32];
#else
    int                         step_exec;
    int                         debug_attach_req;
    int                         debug_ret_user;
    int                         debug_suspend;
    struct rt_hw_exp_stack      *regs;
    void                        *thread_idr;            /** lwp thread indicator */
    int                         *clear_child_tid;
#endif /* ARCH_MM_MMU */
#endif /* RT_USING_SMART */

#ifdef RT_USING_MEM_PROTECTION
    void *mem_regions;
#ifdef RT_USING_HW_STACK_GUARD
    void *stack_buf;
#endif /* RT_USING_HW_STACK_GUARD */
#endif /* RT_USING_MEM_PROTECTION */

    struct rt_spinlock          spinlock;
    rt_ubase_t                  user_data;              /**< private user data beyond this thread */
};
typedef struct rt_thread *rt_thread_t;

/**@}*/

/**
 * @addtogroup IPC
 */

/**@{*/

/**
 * IPC flags and control command definitions
 */
#define RT_IPC_FLAG_FIFO                0x00            /**< FIFOed IPC. @ref IPC. */
#define RT_IPC_FLAG_PRIO                0x01            /**< PRIOed IPC. @ref IPC. */

#define RT_IPC_CMD_UNKNOWN              0x00            /**< unknown IPC command */
#define RT_IPC_CMD_RESET                0x01            /**< reset IPC object */
#define RT_IPC_CMD_GET_STATE            0x02            /**< get the state of IPC object */
#define RT_IPC_CMD_SET_VLIMIT           0x03            /**< set max limit value of IPC value */

#define RT_WAITING_FOREVER              -1              /**< Block forever until get resource. */
#define RT_WAITING_NO                   0               /**< Non-block. */

/**
 * Base structure of IPC object
 */
struct rt_ipc_object
{
    struct rt_object parent;                            /**< inherit from rt_object */

    rt_list_t        suspend_thread;                    /**< threads pended on this resource */
};

#ifdef RT_USING_SEMAPHORE
/**
 * Semaphore structure
 */
struct rt_semaphore
{
    struct rt_ipc_object parent;                        /**< inherit from ipc_object */

    rt_uint16_t          value;                         /**< value of semaphore. */
#define RT_USING_OLD    
#ifdef RT_USING_OLD
    rt_uint16_t          reserved;                      /**< reserved field */
#endif    
    rt_uint16_t          max_value;
    struct rt_spinlock   spinlock;
};
typedef struct rt_semaphore *rt_sem_t;
#endif

#ifdef RT_USING_MUTEX
/**
 * Mutual exclusion (mutex) structure
 */
struct rt_mutex
{
    struct rt_ipc_object parent;                        /**< inherit from ipc_object */

    rt_uint8_t           ceiling_priority;              /**< the priority ceiling of mutexe */
    rt_uint8_t           priority;                      /**< the maximal priority for pending thread */
    rt_uint8_t           hold;                          /**< numbers of thread hold the mutex */
    rt_uint8_t           reserved;                      /**< reserved field */
#define RT_USING_OLD
#ifdef RT_USING_OLD    
    rt_uint16_t          value;                         /**< value of mutex */

    rt_uint8_t           original_priority;             /**< priority of last thread hold the mutex */
#endif
    struct rt_thread    *owner;                         /**< current owner of mutex */
    rt_list_t            taken_list;                    /**< the object list taken by thread */
    struct rt_spinlock   spinlock;
};
typedef struct rt_mutex *rt_mutex_t;
#endif

#ifdef RT_USING_EVENT
/**
 * flag definitions in event
 */
#define RT_EVENT_FLAG_AND               0x01            /**< logic and */
#define RT_EVENT_FLAG_OR                0x02            /**< logic or */
#define RT_EVENT_FLAG_CLEAR             0x04            /**< clear flag */

/*
 * event structure
 */
struct rt_event
{
    struct rt_ipc_object parent;                        /**< inherit from ipc_object */

    rt_uint32_t          set;                           /**< event set */
};
typedef struct rt_event *rt_event_t;
#endif

#ifdef RT_USING_MAILBOX
/**
 * mailbox structure
 */
struct rt_mailbox
{
    struct rt_ipc_object parent;                        /**< inherit from ipc_object */

    rt_ubase_t          *msg_pool;                      /**< start address of message buffer */

    rt_uint16_t          size;                          /**< size of message pool */

    rt_uint16_t          entry;                         /**< index of messages in msg_pool */
    rt_uint16_t          in_offset;                     /**< input offset of the message buffer */
    rt_uint16_t          out_offset;                    /**< output offset of the message buffer */

    rt_list_t            suspend_sender_thread;         /**< sender thread suspended on this mailbox */
};
typedef struct rt_mailbox *rt_mailbox_t;
#endif

#ifdef RT_USING_MESSAGEQUEUE
#define RT_USING_OLD
#ifdef RT_USING_OLD
/**
 * message queue structure
 */
struct rt_messagequeue
{
    struct rt_ipc_object parent;                        /**< inherit from ipc_object */

    void                *msg_pool;                      /**< start address of message queue */

    rt_uint16_t          msg_size;                      /**< message size of each message */
    rt_uint16_t          max_msgs;                      /**< max number of messages */

    rt_uint16_t          entry;                         /**< index of messages in the queue */

    void                *msg_queue_head;                /**< list head */
    void                *msg_queue_tail;                /**< list tail */
    void                *msg_queue_free;                /**< pointer indicated the free node of queue */

    rt_list_t            suspend_sender_thread;         /**< sender thread suspended on this message queue */
};
typedef struct rt_messagequeue *rt_mq_t;
#endif  /* RT_USING_OLD */

struct rt_mq_message
{
    struct rt_mq_message *next;
    rt_ssize_t length;
#ifdef RT_USING_MESSAGEQUEUE_PRIORITY
    rt_int32_t prio;
#endif /* RT_USING_MESSAGEQUEUE_PRIORITY */
};

#define RT_MQ_BUF_SIZE(msg_size, max_msgs) \
((RT_ALIGN((msg_size), RT_ALIGN_SIZE) + sizeof(struct rt_mq_message)) * (max_msgs))

/*
 * message queue interface
 */
rt_err_t rt_mq_init(rt_mq_t     mq,
                    const char *name,
                    void       *msgpool,
                    rt_size_t   msg_size,
                    rt_size_t   pool_size,
                    rt_uint8_t  flag);
rt_err_t rt_mq_detach(rt_mq_t mq);
#ifdef RT_USING_HEAP
rt_mq_t rt_mq_create(const char *name,
                     rt_size_t   msg_size,
                     rt_size_t   max_msgs,
                     rt_uint8_t  flag);
rt_err_t rt_mq_delete(rt_mq_t mq);
#endif /* RT_USING_HEAP */

rt_err_t rt_mq_send(rt_mq_t mq, const void *buffer, rt_size_t size);
rt_err_t rt_mq_send_interruptible(rt_mq_t mq, const void *buffer, rt_size_t size);
rt_err_t rt_mq_send_killable(rt_mq_t mq, const void *buffer, rt_size_t size);
rt_err_t rt_mq_send_wait(rt_mq_t     mq,
                         const void *buffer,
                         rt_size_t   size,
                         rt_int32_t  timeout);
rt_err_t rt_mq_send_wait_interruptible(rt_mq_t     mq,
                         const void *buffer,
                         rt_size_t   size,
                         rt_int32_t  timeout);
rt_err_t rt_mq_send_wait_killable(rt_mq_t     mq,
                         const void *buffer,
                         rt_size_t   size,
                         rt_int32_t  timeout);
rt_err_t rt_mq_urgent(rt_mq_t mq, const void *buffer, rt_size_t size);
rt_ssize_t rt_mq_recv(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
                    rt_int32_t timeout);
rt_ssize_t rt_mq_recv_interruptible(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
                    rt_int32_t timeout);
rt_ssize_t rt_mq_recv_killable(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
                    rt_int32_t timeout);
rt_err_t rt_mq_control(rt_mq_t mq, int cmd, void *arg);

#ifdef RT_USING_MESSAGEQUEUE_PRIORITY
rt_err_t rt_mq_send_wait_prio(rt_mq_t mq,
                              const void *buffer,
                              rt_size_t size,
                              rt_int32_t prio,
                              rt_int32_t timeout,
                              int suspend_flag);
rt_ssize_t rt_mq_recv_prio(rt_mq_t mq,
                           void *buffer,
                           rt_size_t size,
                           rt_int32_t *prio,
                           rt_int32_t timeout,
                           int suspend_flag);
#endif /* RT_USING_MESSAGEQUEUE_PRIORITY */
#endif

/**@}*/

/**
 * @addtogroup MM
 */

/**@{*/

#ifdef RT_USING_HEAP
/*
 * memory structure
 */
struct rt_memory
{
    struct rt_object        parent;                 /**< inherit from rt_object */
    const char *            algorithm;              /**< Memory management algorithm name */
    rt_ubase_t              address;                /**< memory start address */
    rt_size_t               total;                  /**< memory size */
    rt_size_t               used;                   /**< size used */
    rt_size_t               max;                    /**< maximum usage */
};
typedef struct rt_memory *rt_mem_t;
#endif

/*
 * memory management
 * heap & partition
 */

#ifdef RT_USING_SMALL_MEM
typedef rt_mem_t rt_smem_t;
#endif

#ifdef RT_USING_SLAB
typedef rt_mem_t rt_slab_t;
#endif

#ifdef RT_USING_MEMHEAP
/**
 * memory item on the heap
 */
struct rt_memheap_item
{
    rt_uint32_t             magic;                      /**< magic number for memheap */
    struct rt_memheap      *pool_ptr;                   /**< point of pool */

    struct rt_memheap_item *next;                       /**< next memheap item */
    struct rt_memheap_item *prev;                       /**< prev memheap item */

    struct rt_memheap_item *next_free;                  /**< next free memheap item */
    struct rt_memheap_item *prev_free;                  /**< prev free memheap item */
#ifdef RT_USING_MEMTRACE
    rt_uint8_t              owner_thread_name[4];       /**< owner thread name */
#endif
};

/**
 * Base structure of memory heap object
 */
struct rt_memheap
{
    struct rt_object        parent;                     /**< inherit from rt_object */

    void                   *start_addr;                 /**< pool start address and size */

    rt_size_t               pool_size;                  /**< pool size */
    rt_size_t               available_size;             /**< available size */
    rt_size_t               max_used_size;              /**< maximum allocated size */

    struct rt_memheap_item *block_list;                 /**< used block list */

    struct rt_memheap_item *free_list;                  /**< free block list */
    struct rt_memheap_item  free_header;                /**< free block list header */

    struct rt_semaphore     lock;                       /**< semaphore lock */
    rt_bool_t               locked;                     /**< External lock mark */
};
#endif

#ifdef RT_USING_MEMPOOL
/**
 * Base structure of Memory pool object
 */
struct rt_mempool
{
    struct rt_object parent;                            /**< inherit from rt_object */

    void            *start_address;                     /**< memory pool start */
    rt_size_t        size;                              /**< size of memory pool */

    rt_size_t        block_size;                        /**< size of memory blocks */
    rt_uint8_t      *block_list;                        /**< memory blocks list */

    rt_size_t        block_total_count;                 /**< numbers of memory block */
    rt_size_t        block_free_count;                  /**< numbers of free memory block */

    rt_list_t        suspend_thread;                    /**< threads pended on this resource */
};
typedef struct rt_mempool *rt_mp_t;
#endif

/**@}*/

#ifdef RT_USING_DEVICE
/**
 * @addtogroup Device
 */

/**@{*/

/**
 * device (I/O) class type
 */
enum rt_device_class_type
{
    RT_Device_Class_Char = 0,                           /**< character device */
    RT_Device_Class_Block,                              /**< block device */
    RT_Device_Class_NetIf,                              /**< net interface */
    RT_Device_Class_MTD,                                /**< memory device */
    RT_Device_Class_CAN,                                /**< CAN device */
    RT_Device_Class_RTC,                                /**< RTC device */
    RT_Device_Class_Sound,                              /**< Sound device */
    RT_Device_Class_Graphic,                            /**< Graphic device */
    RT_Device_Class_I2CBUS,                             /**< I2C bus device */
    RT_Device_Class_USBDevice,                          /**< USB slave device */
    RT_Device_Class_USBHost,                            /**< USB host bus */
    RT_Device_Class_USBOTG,                             /**< USB OTG bus */
    RT_Device_Class_SPIBUS,                             /**< SPI bus device */
    RT_Device_Class_SPIDevice,                          /**< SPI device */
    RT_Device_Class_SDIO,                               /**< SDIO bus device */
    RT_Device_Class_PM,                                 /**< PM pseudo device */
    RT_Device_Class_Pipe,                               /**< Pipe device */
    RT_Device_Class_Portal,                             /**< Portal device */
    RT_Device_Class_Timer,                              /**< Timer device */
    RT_Device_Class_Miscellaneous,                      /**< Miscellaneous device */
    RT_Device_Class_Sensor,                             /**< Sensor device */
    RT_Device_Class_Touch,                              /**< Touch device */
    RT_Device_Class_PHY,                                /**< PHY device */
    RT_Device_Class_Security,                           /**< Security device */
    RT_Device_Class_Unknown                             /**< unknown device */
};

/**
 * device flags definitions
 */
#define RT_DEVICE_FLAG_DEACTIVATE       0x000           /**< device is not not initialized */

#define RT_DEVICE_FLAG_RDONLY           0x001           /**< read only */
#define RT_DEVICE_FLAG_WRONLY           0x002           /**< write only */
#define RT_DEVICE_FLAG_RDWR             0x003           /**< read and write */

#define RT_DEVICE_FLAG_REMOVABLE        0x004           /**< removable device */
#define RT_DEVICE_FLAG_STANDALONE       0x008           /**< standalone device */
#define RT_DEVICE_FLAG_ACTIVATED        0x010           /**< device is activated */
#define RT_DEVICE_FLAG_SUSPENDED        0x020           /**< device is suspended */
#define RT_DEVICE_FLAG_STREAM           0x040           /**< stream mode */

#define RT_DEVICE_FLAG_INT_RX           0x100           /**< INT mode on Rx */
#define RT_DEVICE_FLAG_DMA_RX           0x200           /**< DMA mode on Rx */
#define RT_DEVICE_FLAG_INT_TX           0x400           /**< INT mode on Tx */
#define RT_DEVICE_FLAG_DMA_TX           0x800           /**< DMA mode on Tx */

#define RT_DEVICE_OFLAG_CLOSE           0x000           /**< device is closed */
#define RT_DEVICE_OFLAG_RDONLY          0x001           /**< read only access */
#define RT_DEVICE_OFLAG_WRONLY          0x002           /**< write only access */
#define RT_DEVICE_OFLAG_RDWR            0x003           /**< read and write */
#define RT_DEVICE_OFLAG_OPEN            0x008           /**< device is opened */
#define RT_DEVICE_OFLAG_MASK            0xf0f           /**< mask of open flag */

/**
 * general device commands
 */
#define RT_DEVICE_CTRL_RESUME           0x01            /**< resume device */
#define RT_DEVICE_CTRL_SUSPEND          0x02            /**< suspend device */
#define RT_DEVICE_CTRL_CONFIG           0x03            /**< configure device */
#define RT_DEVICE_CTRL_CLOSE            0x04            /**< close device */

#define RT_DEVICE_CTRL_SET_INT          0x10            /**< set interrupt */
#define RT_DEVICE_CTRL_CLR_INT          0x11            /**< clear interrupt */
#define RT_DEVICE_CTRL_GET_INT          0x12            /**< get interrupt status */

/**
 * special device commands
 */
#define RT_DEVICE_CTRL_CHAR_STREAM      0x20            /**< stream mode on char device */
#define RT_DEVICE_CTRL_BLK_GETGEOME     0x20            /**< get geometry information   */
#define RT_DEVICE_CTRL_BLK_SYNC         0x21            /**< flush data to block device */
#define RT_DEVICE_CTRL_BLK_ERASE        0x22            /**< erase block on block device */
#define RT_DEVICE_CTRL_BLK_AUTOREFRESH  0x23            /**< block device : enter/exit auto refresh mode */
#define RT_DEVICE_CTRL_NETIF_GETMAC     0x20            /**< get mac address */
#define RT_DEVICE_CTRL_MTD_FORMAT       0x20            /**< format a MTD device */

typedef struct rt_device *rt_device_t;

#ifdef RT_USING_DEVICE_OPS
/**
 * operations set for device object
 */
struct rt_device_ops
{
    /* common device interface */
    rt_err_t  (*init)   (rt_device_t dev);
    rt_err_t  (*open)   (rt_device_t dev, rt_uint16_t oflag);
    rt_err_t  (*close)  (rt_device_t dev);
    rt_size_t (*read)   (rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
    rt_size_t (*write)  (rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
    rt_err_t  (*control)(rt_device_t dev, int cmd, void *args);
};
#endif

/**
 * WaitQueue structure
 */
struct rt_wqueue
{
    rt_uint32_t flag;
    rt_list_t waiting_list;
};
typedef struct rt_wqueue rt_wqueue_t;

/**
 * Device structure
 */
struct rt_device
{
    struct rt_object          parent;                   /**< inherit from rt_object */

    enum rt_device_class_type type;                     /**< device type */
    rt_uint16_t               flag;                     /**< device flag */
    rt_uint16_t               open_flag;                /**< device open flag */

    rt_uint8_t                ref_count;                /**< reference count */
    rt_uint8_t                device_id;                /**< 0 - 255 */

    /* device call back */
    rt_err_t (*rx_indicate)(rt_device_t dev, rt_size_t size);
    rt_err_t (*tx_complete)(rt_device_t dev, void *buffer);

#ifdef RT_USING_DEVICE_OPS
    const struct rt_device_ops *ops;
#else
    /* common device interface */
    rt_err_t  (*init)   (rt_device_t dev);
    rt_err_t  (*open)   (rt_device_t dev, rt_uint16_t oflag);
    rt_err_t  (*close)  (rt_device_t dev);
    rt_size_t (*read)   (rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
    rt_size_t (*write)  (rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
    rt_err_t  (*control)(rt_device_t dev, int cmd, void *args);
#endif

#ifdef RT_USING_POSIX_DEVIO
    const struct dfs_file_ops *fops;
    struct rt_wqueue wait_queue;
#endif

    void                     *user_data;                /**< device private data */
};

/**
 * block device geometry structure
 */
struct rt_device_blk_geometry
{
    rt_uint32_t sector_count;                           /**< count of sectors */
    rt_uint32_t bytes_per_sector;                       /**< number of bytes per sector */
    rt_uint32_t block_size;                             /**< number of bytes to erase one block */
};

/**
 * sector arrange struct on block device
 */
struct rt_device_blk_sectors
{
    rt_uint32_t sector_begin;                           /**< begin sector */
    rt_uint32_t sector_end;                             /**< end sector   */
};

/**
 * cursor control command
 */
#define RT_DEVICE_CTRL_CURSOR_SET_POSITION  0x10
#define RT_DEVICE_CTRL_CURSOR_SET_TYPE      0x11

/**
 * graphic device control command
 */
#define RTGRAPHIC_CTRL_RECT_UPDATE      0
#define RTGRAPHIC_CTRL_POWERON          1
#define RTGRAPHIC_CTRL_POWEROFF         2
#define RTGRAPHIC_CTRL_GET_INFO         3
#define RTGRAPHIC_CTRL_SET_MODE         4
#define RTGRAPHIC_CTRL_GET_EXT          5
#define RTGRAPHIC_CTRL_SET_BRIGHTNESS   6
#define RTGRAPHIC_CTRL_GET_BRIGHTNESS   7
#define RTGRAPHIC_CTRL_GET_MODE         8
#define RTGRAPHIC_CTRL_GET_STATUS       9
#define RTGRAPHIC_CTRL_PAN_DISPLAY      10
#define RTGRAPHIC_CTRL_WAIT_VSYNC       11

/* graphic device */
enum
{
    RTGRAPHIC_PIXEL_FORMAT_MONO = 0,
    RTGRAPHIC_PIXEL_FORMAT_GRAY4,
    RTGRAPHIC_PIXEL_FORMAT_GRAY16,
    RTGRAPHIC_PIXEL_FORMAT_RGB332,
    RTGRAPHIC_PIXEL_FORMAT_RGB444,
    RTGRAPHIC_PIXEL_FORMAT_RGB565,
    RTGRAPHIC_PIXEL_FORMAT_RGB565P,
    RTGRAPHIC_PIXEL_FORMAT_BGR565 = RTGRAPHIC_PIXEL_FORMAT_RGB565P,
    RTGRAPHIC_PIXEL_FORMAT_RGB666,
    RTGRAPHIC_PIXEL_FORMAT_RGB888,
    RTGRAPHIC_PIXEL_FORMAT_ARGB888,
    RTGRAPHIC_PIXEL_FORMAT_ABGR888,
    RTGRAPHIC_PIXEL_FORMAT_RESERVED,
};

/**
 * build a pixel position according to (x, y) coordinates.
 */
#define RTGRAPHIC_PIXEL_POSITION(x, y)  ((x << 16) | y)

/**
 * graphic device information structure
 */
struct rt_device_graphic_info
{
    rt_uint8_t  pixel_format;                           /**< graphic format */
    rt_uint8_t  bits_per_pixel;                         /**< bits per pixel */
    rt_uint16_t pitch;                                  /**< bytes per line */

    rt_uint16_t width;                                  /**< width of graphic device */
    rt_uint16_t height;                                 /**< height of graphic device */

    rt_uint8_t *framebuffer;                            /**< frame buffer */
    rt_uint32_t smem_len;                               /**< allocated frame buffer size */
};

/**
 * rectangle information structure
 */
struct rt_device_rect_info
{
    rt_uint16_t x;                                      /**< x coordinate */
    rt_uint16_t y;                                      /**< y coordinate */
    rt_uint16_t width;                                  /**< width */
    rt_uint16_t height;                                 /**< height */
};

/**
 * graphic operations
 */
struct rt_device_graphic_ops
{
    void (*set_pixel) (const char *pixel, int x, int y);
    void (*get_pixel) (char *pixel, int x, int y);

    void (*draw_hline)(const char *pixel, int x1, int x2, int y);
    void (*draw_vline)(const char *pixel, int x, int y1, int y2);

    void (*blit_line) (const char *pixel, int x, int y, rt_size_t size);
};
#define rt_graphix_ops(device)          ((struct rt_device_graphic_ops *)(device->user_data))

/**@}*/
#endif

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/* RT-Thread definitions for C++ */
namespace rtthread {

enum TICK_WAIT {
    WAIT_NONE = 0,
    WAIT_FOREVER = -1,
};

}

#endif /* end of __cplusplus */

#endif
