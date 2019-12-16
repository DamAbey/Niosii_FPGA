/*
 * "Small Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It requires a STDOUT  device in your system's hardware.
 *
 * The purpose of this example is to demonstrate the smallest possible Hello
 * World application, using the Nios II HAL library.  The memory footprint
 * of this hosted application is ~332 bytes by default using the standard
 * reference design.  For a more fully featured Hello World application
 * example, see the example titled "Hello World".
 *
 * The memory footprint of this example has been reduced by making the
 * following changes to the normal "Hello World" example.
 * Check in the Nios II Software Developers Manual for a more complete
 * description.
 *
 * In the SW Application project (small_hello_world):
 *
 *  - In the C/C++ Build page
 *
 *    - Set the Optimization Level to -Os
 *
 * In System Library project (small_hello_world_syslib):
 *  - In the C/C++ Build page
 *
 *    - Set the Optimization Level to -Os
 *
 *    - Define the preprocessor option ALT_NO_INSTRUCTION_EMULATION
 *      This removes software exception handling, which means that you cannot
 *      run code compiled for Nios II cpu with a hardware multiplier on a core
 *      without a the multiply unit. Check the Nios II Software Developers
 *      Manual for more details.
 *
 *  - In the System Library page:
 *    - Set Periodic system timer and Timestamp timer to none
 *      This prevents the automatic inclusion of the timer driver.
 *
 *    - Set Max file descriptors to 4
 *      This reduces the size of the file handle pool.
 *
 *    - Check Main function does not exit
 *    - Uncheck Clean exit (flush buffers)
 *      This removes the unneeded call to exit when main returns, since it
 *      won't.
 *
 *    - Check Don't use C++
 *      This builds without the C++ support code.
 *
 *    - Check Small C library
 *      This uses a reduced functionality C library, which lacks
 *      support for buffering, file IO, floating point and getch(), etc.
 *      Check the Nios II Software Developers Manual for a complete list.
 *
 *    - Check Reduced device drivers
 *      This uses reduced functionality drivers if they're available. For the
 *      standard design this means you get polled UART and JTAG UART drivers,
 *      no support for the LCD driver and you lose the ability to program
 *      CFI compliant flash devices.
 *
 *    - Check Access device drivers directly
 *      This bypasses the device file system to access device drivers directly.
 *      This eliminates the space required for the device file system services.
 *      It also provides a HAL version of libc services that access the drivers
 *      directly, further reducing space. Only a limited number of libc
 *      functions are available in this configuration.
 *
 *    - Use ALT versions of stdio routines:
 *
 *           Function                  Description
 *        ===============  =====================================
 *        alt_printf       Only supports %s, %x, and %c ( < 1 Kbyte)
 *        alt_putstr       Smaller overhead than puts with direct drivers
 *                         Note this function doesn't add a newline.
 *        alt_putchar      Smaller overhead than putchar with direct drivers
 *        alt_getchar      Smaller overhead than getchar with direct drivers
 *
 */

//#include "sys/alt_stdio.h"
#include "stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_uart_regs.h"
#include <time.h>
#include <unistd.h>
int main()
{
    //alt_putstr("Hi, Hello from Nios II!\n");
	printf("Hi Damith");
    int count = 0;
    int micro_out=0;
    int micro_in=0;
    int i=0;
    while(1)
    {
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE, count);
        IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 'A');

    	//count= IORD_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE);
        usleep(100000);


        	/* COMMAND SET
        	 * 0x05- Write Yaer
        	 * 0x09- Write Month
        	 * 0x0D- Write Date
        	 * 0x00- while data change
        	 * 0x03-Data read from fabric
        	 */
        	IOWR_ALTERA_AVALON_PIO_DIRECTION(PIO_DATA_BASE, 0xFFFF);// 1: set direction of all lines to output
        	usleep(10);

        	i=2000;
        	IOWR_ALTERA_AVALON_PIO_DATA(PIO_COMMAND_BASE, (0x00));// this command is sent to prevent reading while data change
        	IOWR_ALTERA_AVALON_PIO_DATA(PIO_DATA_BASE, i);// set data to be written to FPGA
        	usleep(10);
        	IOWR_ALTERA_AVALON_PIO_DATA(PIO_COMMAND_BASE, (0x05));// command to write year
        	usleep(10);

        	i=10;
        	IOWR_ALTERA_AVALON_PIO_DATA(PIO_COMMAND_BASE, (0x00));// this command is sent to prevent reading while data change
        	IOWR_ALTERA_AVALON_PIO_DATA(PIO_DATA_BASE, i);// set data to be written to FPGA
        	usleep(10);
        	IOWR_ALTERA_AVALON_PIO_DATA(PIO_COMMAND_BASE, (0x09));// command to write month
        	usleep(10);

        	i=1;
        	IOWR_ALTERA_AVALON_PIO_DATA(PIO_COMMAND_BASE, (0x00));// this command is sent to prevent reading while data change
        	IOWR_ALTERA_AVALON_PIO_DATA(PIO_DATA_BASE, i);// set data to be written to FPGA
        	usleep(10);
        	IOWR_ALTERA_AVALON_PIO_DATA(PIO_COMMAND_BASE, (0x0D));// command to write data
        	usleep(10);


        	IOWR_ALTERA_AVALON_PIO_DIRECTION(PIO_DATA_BASE, 0x0000);// 0: set direction of all lines to input
        	usleep(10);
        	IOWR_ALTERA_AVALON_PIO_DATA(PIO_COMMAND_BASE, 0x03);// command to read data from FPGA
        	usleep(10);
        	micro_in=IORD_ALTERA_AVALON_PIO_DATA(PIO_DATA_BASE);
        	printf("The day is: ");

        	switch (micro_in)
        	{
        	case 0: printf("Sunday \n");break;
        	case 1: printf("Monday \n");break;
        	case 2: printf("Tuesday \n");break;
        	case 3: printf("Wednesday \n");break;
        	case 4: printf("Thursday \n");break;
        	case 5: printf("Friday \n");break;
        	case 6: printf("Saturday \n");break;
        	default:printf("Invalid data \n");break;
        	}

        	/*
        	 * 0-Sunday
        	 * 1-Monday
        	 * 2-Tuesday
        	 * 3-Wednesday
        	 * 4-Thursday
        	 * 5-Friday
        	 * 6-Saturday
        	 */


    }
    return 0;
}
