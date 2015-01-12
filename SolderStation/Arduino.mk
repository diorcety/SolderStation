### DISCLAIMER
### This is an example Makefile and it MUST be configured to suit your needs.
### For detailled explanations about all the avalaible options,
### please refer to https://github.com/sudar/Arduino-Makefile/blob/master/arduino-mk-vars.md
### Original project where this Makefile comes from: https://github.com/WeAreLeka/Bare-Arduino-Project

ifeq ($(OS),Windows_NT)
    PLATFORM=windows
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        PLATFORM=linux
    endif
    ifeq ($(UNAME_S),Darwin)
        PLATFORM=darwin
    endif
endif

### PROJECT_DIR
### This is the path to where you have created/cloned your project
PROJECT_DIR = .
### ARDMK_DIR
### Path to the Arduino-Makefile directory.
ARDMK_DIR = $(PROJECT_DIR)/../Arduino-Makefile
### ARDUINO_DIR
### Path to the Arduino application and ressources directory.
ifeq ($(PLATFORM),darwin)
    ARDUINO_DIR = /Applications/Arduino.app/Contents/Resources/Java
endif
ifeq ($(PLATFORM),linux)
    ARDUINO_DIR = /usr/share/arduino
endif
ifeq ($(PLATFORM),windows)
    ARDUINO_DIR = C:/Arduino
endif
### USER_LIB_PATH
### Path to where the your project's libraries are stored.
USER_LIB_PATH := $(PROJECT_DIR)/../libraries
### MONITOR_BAUDRATE
### It must be set to Serial baudrate value you are using.
MONITOR_BAUDRATE = 115200
### AVR_TOOLS_DIR
### Path to the AVR tools directory such as avr-gcc, avr-g++, etc.
ifeq ($(PLATFORM),darwin)
    AVR_TOOLS_DIR = /usr/local
endif
ifeq ($(PLATFORM),linux)
    AVR_TOOLS_DIR = /usr
endif
ifeq ($(PLATFORM),windows)
    AVR_TOOLS_DIR = $(ARDUINO_DIR)/hardware/tools/avr
endif
### AVRDDUDE
### Path to avrdude directory.
ifeq ($(PLATFORM),darwin)
    AVRDDUDE = /usr/local/bin/avrdude
endif
ifeq ($(PLATFORM),linux)
   AVRDDUDE = /usr/bin/avrdude
endif
### CFLAGS_STD
### Set the C standard to be used during compilation. Documentation (https://github.com/WeAreLeka/Arduino-Makefile/blob/std-flags/arduino-mk-vars.md#cflags_std)
CFLAGS_STD = 
### CXXFLAGS_STD
### Set the C++ standard to be used during compilation. Documentation (https://github.com/WeAreLeka/Arduino-Makefile/blob/std-flags/arduino-mk-vars.md#cxxflags_std)
CXXFLAGS_STD = 
### CXXFLAGS
### Flags you might want to set for debugging purpose. Comment to stop.
CXXFLAGS += -Wall -Wextra
### MONITOR_PORT
### The port your board is connected to. Using an '*' tries all the ports and finds the right one.
MONITOR_PORT = /dev/tty.usbmodem*
### CURRENT_DIR
### Do not touch - used for binaries path
CURRENT_DIR = $(shell basename $(CURDIR))
### OBJDIR
### This is were you put the binaries you just compile using 'make'
OBJDIR = $(PROJECT_DIR)/bin/$(BOARD_TAG)/$(CURRENT_DIR)
### path to Arduino.mk, inside the ARDMK_DIR, don't touch.
include $(ARDMK_DIR)/Arduino.mk

