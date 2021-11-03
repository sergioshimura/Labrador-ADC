
/*
@File name: adc_test.c
@Author Igor Ruschi Andrade E Lima <igor.lima@lsitec.org.br>
@LSITEC
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "labrador_adc.h"
#include "caninos_time.h"

/*
this get the root minimum square of n values give
@fd: adc file descriptor
n: the n get numbers to do rms
return rms value of adc 0-1024(10bits adc 0V - 3V)
*/
int adc_get_rms_value(int fd, int n){
	int i = 0;
	int ret;
    	int aux_i;
    	double aux_d;
	while(i < n){
        	aux_i = adc_read(fd);
		aux_d +=  pow(aux_i, 2);
		i++;
	}
	aux_d = aux_d / i;
	aux_d = sqrt(aux_d);
    	aux_i = (int)(aux_d);
	return aux_i;
}

int main(){
	//set default location for adc0
	char adc_file_path[25] = "/sys/kernel/auxadc/adc0";
	//create the file descriptor for adc
	int adc_fd;
	//create a variable to store the adc data
	int data;
	//open adc file descriptor
	adc_fd = adc_open(adc_file_path);
    	if(adc_fd < 0){
        	printf("[ERROR]: Fail to open ADC FILE ret = %d\n", adc_fd);
        	return -1;
    	}
	while(1){
		//use some filter to remove noise from adc, in this case a rms filter, with n of 5
		data = adc_get_rms_value(adc_fd, 5);
		printf("ADC_DATA = %d\n", data);
		//give 10ms of delay to not overload the system
		delay(10);
	}
	adc_close(adc_fd);
    	exit(1);
    	return 0;
}
