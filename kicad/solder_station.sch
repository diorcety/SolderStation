EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:arduino
LIBS:solder_station-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "SolderStation"
Date "9 jan 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L JACK_2P P1
U 1 1 54B0F266
P 8800 1850
F 0 "P1" H 8450 1650 60  0000 C CNN
F 1 "JACK_2P" H 8650 2100 60  0000 C CNN
F 2 "footprint:AC3MMxZV" H 8800 1850 60  0001 C CNN
F 3 "" H 8800 1850 60  0000 C CNN
	1    8800 1850
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 54B0F425
P 1400 1350
F 0 "R3" V 1480 1350 40  0000 C CNN
F 1 "5K6" V 1407 1351 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1330 1350 30  0001 C CNN
F 3 "" H 1400 1350 30  0000 C CNN
	1    1400 1350
	0    1    1    0   
$EndComp
$Comp
L R R19
U 1 1 54B0F548
P 1850 1700
F 0 "R19" V 1930 1700 40  0000 C CNN
F 1 "100K" V 1857 1701 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1780 1700 30  0001 C CNN
F 3 "" H 1850 1700 30  0000 C CNN
	1    1850 1700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 54B0F620
P 1850 2050
F 0 "#PWR01" H 1850 2050 30  0001 C CNN
F 1 "GND" H 1850 1980 30  0001 C CNN
F 2 "" H 1850 2050 60  0000 C CNN
F 3 "" H 1850 2050 60  0000 C CNN
	1    1850 2050
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 54B0F663
P 2100 1700
F 0 "C1" H 2100 1800 40  0000 L CNN
F 1 "10nF" H 2106 1615 40  0000 L CNN
F 2 "SMD_Packages:SMD-0603" H 2138 1550 30  0001 C CNN
F 3 "" H 2100 1700 60  0000 C CNN
	1    2100 1700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 54B0F714
P 2100 2050
F 0 "#PWR02" H 2100 2050 30  0001 C CNN
F 1 "GND" H 2100 1980 30  0001 C CNN
F 2 "" H 2100 2050 60  0000 C CNN
F 3 "" H 2100 2050 60  0000 C CNN
	1    2100 2050
	1    0    0    -1  
$EndComp
$Comp
L TL081 IC1
U 1 1 54B0F833
P 3100 1450
F 0 "IC1" H 3250 1750 70  0000 C CNN
F 1 "OPA336U" H 3250 1650 70  0000 C CNN
F 2 "SMD_Packages:SOIC-8-W" H 3100 1450 60  0001 C CNN
F 3 "" H 3100 1450 60  0000 C CNN
	1    3100 1450
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 54B0F991
P 2500 1850
F 0 "R1" V 2580 1850 40  0000 C CNN
F 1 "100R" V 2507 1851 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2430 1850 30  0001 C CNN
F 3 "" H 2500 1850 30  0000 C CNN
	1    2500 1850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 54B0FAB3
P 3000 2200
F 0 "#PWR03" H 3000 2200 30  0001 C CNN
F 1 "GND" H 3000 2130 30  0001 C CNN
F 2 "" H 3000 2200 60  0000 C CNN
F 3 "" H 3000 2200 60  0000 C CNN
	1    3000 2200
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 54B0FB31
P 2800 900
F 0 "R2" V 2880 900 40  0000 C CNN
F 1 "68K" V 2807 901 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2730 900 30  0001 C CNN
F 3 "" H 2800 900 30  0000 C CNN
	1    2800 900 
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR04
U 1 1 54B0FC95
P 3000 650
F 0 "#PWR04" H 3000 740 20  0001 C CNN
F 1 "+5V" H 3000 740 30  0000 C CNN
F 2 "" H 3000 650 60  0000 C CNN
F 3 "" H 3000 650 60  0000 C CNN
	1    3000 650 
	1    0    0    -1  
$EndComp
$Comp
L R R18
U 1 1 54B0FCF5
P 4050 1450
F 0 "R18" V 4130 1450 40  0000 C CNN
F 1 "5K6" V 4057 1451 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 3980 1450 30  0001 C CNN
F 3 "" H 4050 1450 30  0000 C CNN
	1    4050 1450
	0    1    1    0   
$EndComp
$Comp
L C C3
U 1 1 54B0FE42
P 4400 1700
F 0 "C3" H 4400 1800 40  0000 L CNN
F 1 "10nF" H 4406 1615 40  0000 L CNN
F 2 "SMD_Packages:SMD-0603" H 4438 1550 30  0001 C CNN
F 3 "" H 4400 1700 60  0000 C CNN
	1    4400 1700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 54B0FEEA
P 4400 2100
F 0 "#PWR05" H 4400 2100 30  0001 C CNN
F 1 "GND" H 4400 2030 30  0001 C CNN
F 2 "" H 4400 2100 60  0000 C CNN
F 3 "" H 4400 2100 60  0000 C CNN
	1    4400 2100
	1    0    0    -1  
$EndComp
Text GLabel 4650 1450 2    60   Input ~ 0
MCU_SENSOR
$Comp
L GND #PWR06
U 1 1 54B103F4
P 9500 1350
F 0 "#PWR06" H 9500 1350 30  0001 C CNN
F 1 "GND" H 9500 1280 30  0001 C CNN
F 2 "" H 9500 1350 60  0000 C CNN
F 3 "" H 9500 1350 60  0000 C CNN
	1    9500 1350
	0    -1   -1   0   
$EndComp
Text GLabel 9500 1250 2    60   Input ~ 0
HEATER
Text GLabel 9500 1450 2    60   Input ~ 0
SENSOR
Text GLabel 1000 1350 0    60   Input ~ 0
SENSOR
Text GLabel 1200 3000 0    60   Input ~ 0
MCU_HEATER
$Comp
L R R5
U 1 1 54B1056B
P 1550 3000
F 0 "R5" V 1630 3000 40  0000 C CNN
F 1 "1K" V 1557 3001 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1480 3000 30  0001 C CNN
F 3 "" H 1550 3000 30  0000 C CNN
	1    1550 3000
	0    1    1    0   
$EndComp
$Comp
L BSS138 T2
U 1 1 54B1101F
P 2250 2950
F 0 "T2" H 2250 2801 40  0000 R CNN
F 1 "BSN20" H 2250 3100 40  0000 R CNN
F 2 "SMD_Packages:SOT-23" H 2120 3052 29  0001 C CNN
F 3 "" H 2250 2950 60  0000 C CNN
	1    2250 2950
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 54B1119D
P 2650 2800
F 0 "R4" V 2730 2800 40  0000 C CNN
F 1 "10K" V 2657 2801 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2580 2800 30  0001 C CNN
F 3 "" H 2650 2800 30  0000 C CNN
	1    2650 2800
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR07
U 1 1 54B1130B
P 2350 3350
F 0 "#PWR07" H 2350 3350 30  0001 C CNN
F 1 "GND" H 2350 3280 30  0001 C CNN
F 2 "" H 2350 3350 60  0000 C CNN
F 3 "" H 2350 3350 60  0000 C CNN
	1    2350 3350
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR08
U 1 1 54B12089
P 2850 2350
F 0 "#PWR08" H 2850 2300 20  0001 C CNN
F 1 "+12V" H 2850 2450 30  0000 C CNN
F 2 "" H 2850 2350 60  0000 C CNN
F 3 "" H 2850 2350 60  0000 C CNN
	1    2850 2350
	1    0    0    -1  
$EndComp
Text GLabel 4100 2950 2    60   Input ~ 0
HEATER
$Comp
L CONN_01X02 P2
U 1 1 54B12906
P 9050 2450
F 0 "P2" H 9050 2600 50  0000 C CNN
F 1 "POWER" V 9150 2450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 9050 2450 60  0001 C CNN
F 3 "" H 9050 2450 60  0000 C CNN
	1    9050 2450
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X04 P3
U 1 1 54B12D31
P 9050 3000
F 0 "P3" H 9050 3250 50  0000 C CNN
F 1 "MCU" V 9150 3000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 9050 3000 60  0001 C CNN
F 3 "" H 9050 3000 60  0000 C CNN
	1    9050 3000
	-1   0    0    -1  
$EndComp
$Comp
L +12V #PWR09
U 1 1 54B12ED6
P 9300 2400
F 0 "#PWR09" H 9300 2350 20  0001 C CNN
F 1 "+12V" H 9300 2500 30  0000 C CNN
F 2 "" H 9300 2400 60  0000 C CNN
F 3 "" H 9300 2400 60  0000 C CNN
	1    9300 2400
	0    1    1    0   
$EndComp
$Comp
L GND #PWR010
U 1 1 54B1305B
P 9350 2500
F 0 "#PWR010" H 9350 2500 30  0001 C CNN
F 1 "GND" H 9350 2430 30  0001 C CNN
F 2 "" H 9350 2500 60  0000 C CNN
F 3 "" H 9350 2500 60  0000 C CNN
	1    9350 2500
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR011
U 1 1 54B130FD
P 9300 2850
F 0 "#PWR011" H 9300 2940 20  0001 C CNN
F 1 "+5V" H 9300 2940 30  0000 C CNN
F 2 "" H 9300 2850 60  0000 C CNN
F 3 "" H 9300 2850 60  0000 C CNN
	1    9300 2850
	0    1    1    0   
$EndComp
$Comp
L GND #PWR012
U 1 1 54B13187
P 9400 3050
F 0 "#PWR012" H 9400 3050 30  0001 C CNN
F 1 "GND" H 9400 2980 30  0001 C CNN
F 2 "" H 9400 3050 60  0000 C CNN
F 3 "" H 9400 3050 60  0000 C CNN
	1    9400 3050
	0    -1   -1   0   
$EndComp
Text GLabel 9400 3200 2    60   Input ~ 0
MCU_HEATER
Text GLabel 9450 2900 2    60   Input ~ 0
MCU_SENSOR
$Comp
L IRF7606PBF T1
U 1 1 54B10A82
P 3250 3000
F 0 "T1" H 3085 3285 40  0000 C CNN
F 1 "IRF7416" H 3250 2765 40  0000 C CNN
F 2 "SMD_Packages:SOIC-8-W" H 3250 3200 30  0001 C CIN
F 3 "" V 3250 3000 60  0000 C CNN
	1    3250 3000
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 54B589BD
P 6250 2750
F 0 "SW1" H 6250 2850 70  0000 C CNN
F 1 "SPST" H 6250 2650 70  0000 C CNN
F 2 "footprint:SW_65_45" H 6250 2750 60  0001 C CNN
F 3 "" H 6250 2750 60  0000 C CNN
	1    6250 2750
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 54B58A5E
P 6250 3050
F 0 "SW2" H 6250 3150 70  0000 C CNN
F 1 "SPST" H 6250 2950 70  0000 C CNN
F 2 "footprint:SW_65_45" H 6250 3050 60  0001 C CNN
F 3 "" H 6250 3050 60  0000 C CNN
	1    6250 3050
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW3
U 1 1 54B58AB3
P 6250 3350
F 0 "SW3" H 6250 3450 70  0000 C CNN
F 1 "SPST" H 6250 3250 70  0000 C CNN
F 2 "footprint:SW_65_45" H 6250 3350 60  0001 C CNN
F 3 "" H 6250 3350 60  0000 C CNN
	1    6250 3350
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW4
U 1 1 54B58AE8
P 6250 3650
F 0 "SW4" H 6250 3750 70  0000 C CNN
F 1 "SPST" H 6250 3550 70  0000 C CNN
F 2 "footprint:SW_65_45" H 6250 3650 60  0001 C CNN
F 3 "" H 6250 3650 60  0000 C CNN
	1    6250 3650
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X07 P4
U 1 1 54B58CE8
P 7700 1850
F 0 "P4" H 7700 2250 50  0000 C CNN
F 1 "KEYPAD" V 7800 1850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x07" H 7700 1850 60  0001 C CNN
F 3 "" H 7700 1850 60  0000 C CNN
	1    7700 1850
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 54B59175
P 7550 3100
F 0 "R11" V 7630 3100 40  0000 C CNN
F 1 "100K" V 7557 3101 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 7480 3100 30  0001 C CNN
F 3 "" H 7550 3100 30  0000 C CNN
	1    7550 3100
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 54B5924C
P 7350 3400
F 0 "R10" V 7430 3400 40  0000 C CNN
F 1 "100K" V 7357 3401 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 7280 3400 30  0001 C CNN
F 3 "" H 7350 3400 30  0000 C CNN
	1    7350 3400
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 54B5928D
P 7150 3700
F 0 "R9" V 7230 3700 40  0000 C CNN
F 1 "100K" V 7157 3701 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 7080 3700 30  0001 C CNN
F 3 "" H 7150 3700 30  0000 C CNN
	1    7150 3700
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 54B592D0
P 6950 4000
F 0 "R8" V 7030 4000 40  0000 C CNN
F 1 "100K" V 6957 4001 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 6880 4000 30  0001 C CNN
F 3 "" H 6950 4000 30  0000 C CNN
	1    6950 4000
	1    0    0    -1  
$EndComp
Text GLabel 5250 3200 0    60   Input ~ 0
PIN_V+
Text GLabel 5600 4650 0    60   Input ~ 0
PIN_GND
$Comp
L LED D1
U 1 1 54B59B66
P 6400 4050
F 0 "D1" H 6400 4150 50  0000 C CNN
F 1 "LED" H 6400 3950 50  0000 C CNN
F 2 "LEDs:LED-0805" H 6400 4050 60  0001 C CNN
F 3 "" H 6400 4050 60  0000 C CNN
	1    6400 4050
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 54B59E50
P 6000 4400
F 0 "R7" V 6080 4400 40  0000 C CNN
F 1 "1K" V 6007 4401 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 5930 4400 30  0001 C CNN
F 3 "" H 6000 4400 30  0000 C CNN
	1    6000 4400
	0    1    1    0   
$EndComp
$Comp
L BSS138 T3
U 1 1 54B5A089
P 6600 4350
F 0 "T3" H 6600 4201 40  0000 R CNN
F 1 "BSN20" H 6600 4500 40  0000 R CNN
F 2 "SMD_Packages:SOT-23" H 6470 4452 29  0001 C CNN
F 3 "" H 6600 4350 60  0000 C CNN
	1    6600 4350
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 54B5A476
P 5850 4050
F 0 "R6" V 5930 4050 40  0000 C CNN
F 1 "220R" V 5857 4051 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 5780 4050 30  0001 C CNN
F 3 "" H 5850 4050 30  0000 C CNN
	1    5850 4050
	0    1    1    0   
$EndComp
Text GLabel 5600 4400 0    60   Input ~ 0
PIN_LED
Text GLabel 7800 2750 2    60   Input ~ 0
PIN_B1
Text GLabel 7800 3050 2    60   Input ~ 0
PIN_B2
Text GLabel 7800 3350 2    60   Input ~ 0
PIN_B3
Text GLabel 7800 3650 2    60   Input ~ 0
PIN_B4
Text GLabel 7300 1550 0    60   Input ~ 0
PIN_V+
Text GLabel 6850 1650 0    60   Input ~ 0
PIN_LED
Text GLabel 7300 2150 0    60   Input ~ 0
PIN_GND
Text GLabel 7300 1750 0    60   Input ~ 0
PIN_B1
Text GLabel 6850 1850 0    60   Input ~ 0
PIN_B2
Text GLabel 7300 1950 0    60   Input ~ 0
PIN_B3
Text GLabel 6850 2050 0    60   Input ~ 0
PIN_B4
$Comp
L arduino_mini U1
U 1 1 54BBC0FA
P 9600 4600
F 0 "U1" H 10100 3650 70  0000 C CNN
F 1 "arduino_mini" H 10350 3550 70  0000 C CNN
F 2 "arduino:arduino_mini" H 9600 4550 60  0000 C CNN
F 3 "" H 9600 4600 60  0000 C CNN
	1    9600 4600
	1    0    0    -1  
$EndComp
Text GLabel 8450 4400 0    60   Input ~ 0
MCU_SENSOR
Text GLabel 10550 5100 2    60   Input ~ 0
MCU_HEATER
$Comp
L +5V #PWR013
U 1 1 54BBCFD3
P 9600 3350
F 0 "#PWR013" H 9600 3440 20  0001 C CNN
F 1 "+5V" H 9600 3440 30  0000 C CNN
F 2 "" H 9600 3350 60  0000 C CNN
F 3 "" H 9600 3350 60  0000 C CNN
	1    9600 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 54BBD137
P 9600 6300
F 0 "#PWR014" H 9600 6300 30  0001 C CNN
F 1 "GND" H 9600 6230 30  0001 C CNN
F 2 "" H 9600 6300 60  0000 C CNN
F 3 "" H 9600 6300 60  0000 C CNN
	1    9600 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 1950 1850 2050
Wire Wire Line
	1850 1450 1850 1350
Wire Wire Line
	1650 1350 2600 1350
Wire Wire Line
	2100 1350 2100 1500
Connection ~ 1850 1350
Wire Wire Line
	2100 1900 2100 2050
Wire Wire Line
	2500 2100 3000 2100
Wire Wire Line
	3000 1850 3000 2200
Connection ~ 3000 2100
Wire Wire Line
	2600 1550 2500 1550
Wire Wire Line
	2500 900  2500 1600
Wire Wire Line
	2500 900  2550 900 
Connection ~ 2500 1550
Wire Wire Line
	3050 900  3700 900 
Wire Wire Line
	3700 900  3700 1450
Wire Wire Line
	3600 1450 3800 1450
Connection ~ 2100 1350
Wire Wire Line
	3000 650  3000 1050
Connection ~ 3700 1450
Wire Wire Line
	4300 1450 4650 1450
Wire Wire Line
	4400 1450 4400 1500
Wire Wire Line
	4400 1900 4400 2100
Connection ~ 4400 1450
Wire Wire Line
	1150 1350 1000 1350
Wire Wire Line
	1200 3000 1300 3000
Wire Wire Line
	1800 3000 2050 3000
Wire Wire Line
	2350 3150 2350 3350
Wire Wire Line
	2350 2750 2350 2700
Wire Wire Line
	9300 2400 9250 2400
Wire Wire Line
	9350 2500 9250 2500
Wire Wire Line
	9250 2850 9300 2850
Wire Wire Line
	9400 2950 9250 2950
Wire Wire Line
	9400 2950 9400 2900
Wire Wire Line
	9400 2900 9450 2900
Wire Wire Line
	2450 3150 2950 3150
Wire Wire Line
	2900 3000 2950 3000
Wire Wire Line
	2900 2900 2950 2900
Connection ~ 2900 2900
Wire Wire Line
	3550 2800 3600 2800
Wire Wire Line
	3600 2800 3600 3100
Wire Wire Line
	3600 2900 3550 2900
Wire Wire Line
	3600 3000 3550 3000
Connection ~ 3600 2900
Wire Wire Line
	3600 3100 3550 3100
Connection ~ 3600 3000
Wire Wire Line
	3600 2950 4100 2950
Connection ~ 3600 2950
Wire Wire Line
	2350 2700 2450 2700
Wire Wire Line
	2450 2700 2450 3150
Wire Wire Line
	2900 2350 2900 3000
Wire Wire Line
	2900 2800 2950 2800
Wire Wire Line
	2650 2350 2900 2350
Connection ~ 2900 2800
Wire Wire Line
	2650 2350 2650 2550
Connection ~ 2850 2350
Wire Wire Line
	2650 3050 2650 3150
Connection ~ 2650 3150
Wire Wire Line
	7550 4650 7550 3350
Wire Wire Line
	5600 4650 7550 4650
Wire Wire Line
	6950 4650 6950 4250
Wire Wire Line
	7150 3950 7150 4650
Connection ~ 7150 4650
Wire Wire Line
	7350 3650 7350 4650
Connection ~ 7350 4650
Wire Wire Line
	6550 3650 7800 3650
Wire Wire Line
	6950 3650 6950 3750
Wire Wire Line
	6550 3350 7800 3350
Wire Wire Line
	7150 3350 7150 3450
Wire Wire Line
	6550 3050 7800 3050
Wire Wire Line
	7350 3050 7350 3150
Wire Wire Line
	6550 2750 7800 2750
Wire Wire Line
	7550 2750 7550 2850
Wire Wire Line
	5450 2750 5950 2750
Wire Wire Line
	5450 2750 5450 4050
Wire Wire Line
	5450 3050 5950 3050
Wire Wire Line
	5450 3350 5950 3350
Connection ~ 5450 3050
Wire Wire Line
	5450 3650 5950 3650
Connection ~ 5450 3350
Wire Wire Line
	5250 3200 5450 3200
Connection ~ 5450 3200
Connection ~ 6950 4650
Wire Wire Line
	6600 4050 6700 4050
Wire Wire Line
	6700 4050 6700 4150
Wire Wire Line
	6700 4550 6700 4650
Connection ~ 6700 4650
Wire Wire Line
	6250 4400 6400 4400
Wire Wire Line
	6200 4050 6100 4050
Wire Wire Line
	5450 4050 5600 4050
Connection ~ 5450 3650
Wire Wire Line
	5600 4400 5750 4400
Connection ~ 7550 2750
Connection ~ 7350 3050
Connection ~ 7150 3350
Connection ~ 6950 3650
Wire Wire Line
	7300 1550 7500 1550
Wire Wire Line
	6850 1650 7500 1650
Wire Wire Line
	7500 1750 7300 1750
Wire Wire Line
	7500 1850 6850 1850
Wire Wire Line
	7500 1950 7300 1950
Wire Wire Line
	6850 2050 7500 2050
Wire Wire Line
	7500 2150 7300 2150
Wire Wire Line
	8900 4400 8450 4400
Wire Wire Line
	10300 5100 10550 5100
Wire Wire Line
	9600 3350 9600 3450
Wire Wire Line
	9600 6150 9600 6300
Wire Wire Line
	9250 3050 9400 3050
Wire Wire Line
	9250 3150 9350 3150
Wire Wire Line
	9350 3150 9350 3200
Wire Wire Line
	9350 3200 9400 3200
$Comp
L CONN_01X03 P6
U 1 1 54C97BD7
P 10150 1850
F 0 "P6" H 10150 2050 50  0000 C CNN
F 1 "JACK" V 10250 1850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 10150 1850 60  0001 C CNN
F 3 "" H 10150 1850 60  0000 C CNN
	1    10150 1850
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P5
U 1 1 54C97D24
P 9050 1350
F 0 "P5" H 9050 1550 50  0000 C CNN
F 1 "JACK" V 9150 1350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 9050 1350 60  0001 C CNN
F 3 "" H 9050 1350 60  0000 C CNN
	1    9050 1350
	-1   0    0    1   
$EndComp
Wire Wire Line
	9500 1450 9250 1450
Wire Wire Line
	9500 1350 9250 1350
Wire Wire Line
	9500 1250 9250 1250
Wire Wire Line
	9250 1950 9750 1950
Wire Wire Line
	9750 1950 9750 1750
Wire Wire Line
	9750 1750 9950 1750
Wire Wire Line
	9250 1850 9950 1850
Wire Wire Line
	9950 1950 9800 1950
Wire Wire Line
	9800 1950 9800 1700
Wire Wire Line
	9800 1700 9250 1700
$Comp
L CONN_01X02 P7
U 1 1 54CABC82
P 850 5750
F 0 "P7" H 850 5900 50  0000 C CNN
F 1 "TRANSFO" V 950 5750 50  0000 C CNN
F 2 "Connect:bornier2" H 850 5750 60  0001 C CNN
F 3 "" H 850 5750 60  0000 C CNN
	1    850  5750
	-1   0    0    1   
$EndComp
$Comp
L BRIDGE D2
U 1 1 54CABD9B
P 3800 5800
F 0 "D2" H 3800 5850 70  0000 C CNN
F 1 "BRIDGE" H 3800 5750 70  0000 C CNN
F 2 "footprint:DiodeBridge" H 3800 5800 60  0001 C CNN
F 3 "" H 3800 5800 60  0000 C CNN
	1    3800 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4850 3800 4950
Wire Wire Line
	2300 5750 2750 5750
Wire Wire Line
	2750 5750 2750 4850
Wire Wire Line
	2750 4850 3800 4850
Wire Wire Line
	1200 5850 2700 5850
Wire Wire Line
	2700 5850 2700 6750
Wire Wire Line
	2700 6750 3800 6750
Wire Wire Line
	3800 6750 3800 6650
$Comp
L CAPAPOL C2
U 1 1 54CAD24A
P 4850 6200
F 0 "C2" H 4900 6300 40  0000 L CNN
F 1 "CAPAPOL" H 4900 6100 40  0000 L CNN
F 2 "Capacitors_ThroughHole:Capacitor30x51RM10" H 4950 6050 30  0001 C CNN
F 3 "" H 4850 6200 300 0000 C CNN
	1    4850 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 5800 6300 5800
Wire Wire Line
	4850 5800 4850 6000
Wire Wire Line
	2950 5800 2950 6550
Wire Wire Line
	2950 6550 4850 6550
Wire Wire Line
	4850 6550 4850 6400
$Comp
L CONN_01X02 P8
U 1 1 54CAD746
P 6750 5900
F 0 "P8" H 6750 6050 50  0000 C CNN
F 1 "POWER" V 6850 5900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 6750 5900 60  0001 C CNN
F 3 "" H 6750 5900 60  0000 C CNN
	1    6750 5900
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P9
U 1 1 54CAD7EC
P 6750 6450
F 0 "P9" H 6750 6600 50  0000 C CNN
F 1 "POWER" V 6850 6450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 6750 6450 60  0001 C CNN
F 3 "" H 6750 6450 60  0000 C CNN
	1    6750 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 5800 6300 6400
Wire Wire Line
	6300 5850 6550 5850
Connection ~ 4850 5800
Wire Wire Line
	6300 6400 6550 6400
Connection ~ 6300 5850
Wire Wire Line
	6550 6500 4850 6500
Connection ~ 4850 6500
Wire Wire Line
	6550 5950 6450 5950
Wire Wire Line
	6450 5950 6450 6500
Connection ~ 6450 6500
Wire Wire Line
	1050 5700 2300 5700
Wire Wire Line
	1200 5800 1050 5800
Wire Wire Line
	2300 5700 2300 5750
Wire Wire Line
	1200 5850 1200 5800
$EndSCHEMATC
