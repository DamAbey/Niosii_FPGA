

#include "stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_uart_regs.h"
#include <time.h>
#include <unistd.h>

int Command[]={1,2,4,8,16,32,64,128,256,512};
int Conv_calc();
int Image_Data [10][10]={
		{0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,0,0,0,0,0},
		{0,0,0,0,0,1,1,1,1,1},
		{0,0,0,0,0,1,1,1,1,1},
		{0,0,0,0,0,1,1,1,1,1},
		{0,0,0,0,0,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0}
};


int main()
{

    int conv=0;
    int Data[9];
    int j=0;
    int k=0;
    int n=0;
    int Conv[8][8];
    //int Data[0,0,0,0,5,0,0,0,0];
    while(1)
    {	printf("Image Convolution \n");


    	for(j=0;j<8;j++)
    	{	k=0;
    		for(k=0;k<8;k++)
    		{
    			Data[0]=Image_Data[j][k];
    			Data[1]=Image_Data[j][k+1];
    			Data[2]=Image_Data[j][k+2];
    			Data[3]=Image_Data[j+1][k];
    			Data[4]=Image_Data[j+1][k+1];
    			Data[5]=Image_Data[j+1][k+2];
    			Data[6]=Image_Data[j+2][k];
    			Data[7]=Image_Data[j+2][k+1];
    			Data[8]=Image_Data[j+2][k+2];

    			Conv[j][k]=Conv_calc(Data);
    			printf("%d,", Conv[j][k]);

    		}
    		printf("\n");
    	}
    	printf("------------------------------ \n");

    }
    return 0;
}

int Conv_calc (int data[9])
   {
	int i;
    int micro_in=0;


	IOWR_ALTERA_AVALON_PIO_DIRECTION(PIO_DATA_BASE, 0xFFFF);// 1: set direction of all lines to output
	usleep(10);

	for (i=1;i<10;i++)
	{
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_COMMAND_BASE, (0x00));// this command is sent to prevent reading while data change
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_DATA_BASE, data[i-1]);// set data to be written to FPGA
	usleep(10);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_COMMAND_BASE, Command[i-1]);// command to write year
	usleep(10);
	}


	IOWR_ALTERA_AVALON_PIO_DIRECTION(PIO_DATA_BASE, 0x0000);// 0: set direction of all lines to input
	usleep(10);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_COMMAND_BASE, 0x0200);// command to read data from FPGA
	usleep(10);
	micro_in=IORD_ALTERA_AVALON_PIO_DATA(PIO_DATA_BASE);

	if (micro_in>=32768)
	{
		micro_in=micro_in-65536;
	}
	return micro_in;
    }
