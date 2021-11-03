CC	= gcc #use this one if in Labrador
#CC	= arm-linux-gnueabihf-gcc #use this one if you are in Linux x86 or Linux x64
CFLAGS  = -g
RM      = rm -f

default: all

all: GPIO

GPIO:  labrador_adc.o caninos_time.o adc_test.o
	$(CC) $(CFLAGS) -o adcTest caninos_time.o labrador_adc.o adc_test.o  -lm

clean veryclean:
	$(RM) *.o


