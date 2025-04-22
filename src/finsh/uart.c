#define uart_data (*(volatile unsigned int *)0x80002000)
#define uart_lsr (*(volatile unsigned int *)0x80002014)
 
#define uart_lsr_r_mask 0x01
#define uart_lsr_w_mask 0x20

char uart_getchar(void)
{
    char c;

    while((uart_lsr_r_mask & uart_lsr) == 0);
    c = uart_data;

    return c;
}
 
/**
 * Redefine "rt\u hw\u console\u getchar" function to realize finsh function
 */
char rt_hw_console_getchar(void)
{
	int ch = -1;

	ch = uart_getchar();
	
	return ch;
}