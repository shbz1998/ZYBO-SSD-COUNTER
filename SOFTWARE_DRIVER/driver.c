//NAME: SHAHBAZ HASSAN KHAN MALIK
//SEVEN SEGMENT COUNTER

#include "xuartps.h"
#include <stdio.h>
#include <stdlib.h>
#include "xil_printf.h"
#include "xbasic_types.h"
#include "xparameters.h"
#include "xuartps.h"
#include "xuartps_hw.h"
#include "sleep.h"
#include "xgpio.h"

#define SSD (*((u32 *)(XPAR_MY_SSD_0_S00_AXI_BASEADDR))) //this is our LED

//binary format: [display_mode],G,F,E,D,C,B,A
//display_mode=1, left hand display

unsigned char a[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67}; //right hand display
unsigned char b[]={0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xE7}; //left hand display

int main(){

XGpio push;
u32 input;

int status;
int i=0;
int j=0;

XGpio_Initialize(&push, XPAR_AXI_GPIO_0_DEVICE_ID);
XGpio_SetDataDirection(&push, 1, 0xFFFFFFFF);

xil_printf("WELCOME \n\r");

while(1){
input = XGpio_DiscreteRead(&push, 1);
xil_printf("%u\r\n", input);
	if(input == 1){
		while(1){
		SSD=a[i];
		usleep(17500); //16000 //17500 //30000
		SSD=b[j];
		usleep(50); //25, //50, //2500 //25
		for(int i=0; i<9999999; i++); //extra delay 9999999 5000000
		i=i+1;
		if(i==10){
			i=0;
			j=j+1;
		}
		if(j==10){
			j=0;
		}
		input = XGpio_DiscreteRead(&push, 1);
		if(input == 2){
			i=0;
			j=0;
		}
		else if(input == 4){
			while(1){
			SSD=a[i];
			usleep(50);
			SSD=b[j];
			usleep(50);
			input = XGpio_DiscreteRead(&push, 1);
			if(input == 1){
				break;
			}
			}
		}

	}
	}
}


	return 0;
}
