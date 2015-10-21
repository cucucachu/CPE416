SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
BOARD_LIB = $(SELF_DIR)/library
SOURCE_LIB = $(wildcard $(BOARD_LIB)/*.c)
CLOCK_RATE = 16000000L

lab: lab4 program_mac

neunet:
	gcc -I$(BOARD_LIB) Lab4.c NeuralNetwork.c Neuron.c Motors.c IRSensors.c LineFollowing.c -lm

lab4: lab4.c 	$(wildcard $(BOARD_LIB)/*.c) 
	$(CC) -I$(BOARD_LIB) -DF_CPU=$(CLOCK_RATE) -Wall -mmcu=atmega645a -O2 -o main.elf Lab4.c $(wildcard $(BOARD_LIB)/*.c)  $(wildcard $(SELF_DIR)/*.c) 
	/home/jseng/avr_bin/bin/avr-objcopy -O ihex main.elf main.hex
	/home/jseng/avr_bin/bin/avr-size main.elf

test: test.c $(wildcard $(BOARD_LIB)/*.c)
	avr-gcc -I$(BOARD_LIB) -DF_CPU=$(CLOCK_RATE) -Wall -mmcu=atmega645a -O2 -o main.elf test.c $(wildcard $(BOARD_LIB)/*.c)
	avr-objcopy -O ihex main.elf main.hex
	avr-size main.elf

lib: $(wildcard $(BOARD_LIB)/*.c)
	$(foreach var,$(SOURCE_LIB), \
        avr-gcc -I$(BOARD_LIB) -DF_CPU=$(CLOCK_RATE) -Wall -mmcu=atmega645a -O2 -c -o $(var:.c=.o) $(var); )

program_windows: 
	avrdude -F -pm645 -Pcom4 -carduino -u -U flash:w:main.hex

#edit the device to match the device on your computer
MAC_DEVICE = `ls /dev/cu*modem*`
program_mac: main.elf
	avrdude -pm645 -P $(MAC_DEVICE) -c arduino -F -u -U flash:w:main.hex

program_linux: main.elf
	avrdude -pm645 -P /dev/bumblebee -c arduino -F -u -U flash:w:main.hex

clean:
	rm -fr *.elf *.hex *.o
