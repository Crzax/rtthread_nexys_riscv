#include "board.h"
#define THREAD_PRIORITY         10
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

#ifdef __cplusplus
int dynmem_sample(void);
int interrupt_sample(void);
int createLEDController(void);
int mempool_sample(void);
int mailbox_sample(void);
int mutex_sample(void);
int msgq_sample(void);
int semaphore_sample(void);
int signal_sample(void);
int thread_sample(void);
int timer_sample(void);
int timeslice_sample(void);
#endif