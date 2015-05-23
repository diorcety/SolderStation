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
LIBS:library
LIBS:arduino
LIBS:74xgxx
LIBS:ac-dc
LIBS:actel
LIBS:analog_devices
LIBS:brooktre
LIBS:cmos_ieee
LIBS:dc-dc
LIBS:elec-unifil
LIBS:ftdi
LIBS:gennum
LIBS:graphic
LIBS:hc11
LIBS:ir
LIBS:logo
LIBS:maxim
LIBS:microchip_dspic33dsc
LIBS:microchip_pic10mcu
LIBS:microchip_pic12mcu
LIBS:microchip_pic16mcu
LIBS:microchip_pic18mcu
LIBS:microchip_pic32mcu
LIBS:motor_drivers
LIBS:msp430
LIBS:nordicsemi
LIBS:nxp_armmcu
LIBS:onsemi
LIBS:powerint
LIBS:pspice
LIBS:references
LIBS:relays
LIBS:rfcom
LIBS:sensors
LIBS:silabs
LIBS:stm8
LIBS:stm32
LIBS:supertex
LIBS:switches
LIBS:transf
LIBS:ttl_ieee
LIBS:video
LIBS:irf7476
LIBS:enc
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
F 2 "Capacitors_SMD:C_0603" H 2138 1550 30  0001 C CNN
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
F 2 "Capacitors_SMD:C_0603" H 4438 1550 30  0001 C CNN
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
P 9550 1400
F 0 "#PWR06" H 9550 1400 30  0001 C CNN
F 1 "GND" H 9550 1330 30  0001 C CNN
F 2 "" H 9550 1400 60  0000 C CNN
F 3 "" H 9550 1400 60  0000 C CNN
	1    9550 1400
	0    -1   -1   0   
$EndComp
Text GLabel 9550 1300 2    60   Input ~ 0
HEATER
Text GLabel 9550 1500 2    60   Input ~ 0
SENSOR
Text GLabel 1000 1350 0    60   Input ~ 0
SENSOR
Text GLabel 1350 5600 0    60   Input ~ 0
MCU_HEATER
Text GLabel 5350 6350 2    60   Input ~ 0
HEATER
$Comp
L CONN_01X02 P2
U 1 1 54B12906
P 9050 2450
F 0 "P2" H 9050 2600 50  0000 C CNN
F 1 "POWER" V 9150 2450 50  0000 C CNN
F 2 "Connect:bornier2" H 9050 2450 60  0001 C CNN
F 3 "" H 9050 2450 60  0000 C CNN
	1    9050 2450
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X05 P3
U 1 1 54B12D31
P 9050 3000
F 0 "P3" H 9050 3250 50  0000 C CNN
F 1 "MCU" V 9150 3000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05" H 9050 3000 60  0001 C CNN
F 3 "" H 9050 3000 60  0000 C CNN
	1    9050 3000
	-1   0    0    -1  
$EndComp
$Comp
L +12V #PWR07
U 1 1 54B12ED6
P 9400 2400
F 0 "#PWR07" H 9400 2350 20  0001 C CNN
F 1 "+12V" H 9400 2500 30  0000 C CNN
F 2 "" H 9400 2400 60  0000 C CNN
F 3 "" H 9400 2400 60  0000 C CNN
	1    9400 2400
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR08
U 1 1 54B130FD
P 9400 2800
F 0 "#PWR08" H 9400 2890 20  0001 C CNN
F 1 "+5V" H 9400 2890 30  0000 C CNN
F 2 "" H 9400 2800 60  0000 C CNN
F 3 "" H 9400 2800 60  0000 C CNN
	1    9400 2800
	0    1    1    0   
$EndComp
$Comp
L GND #PWR09
U 1 1 54B13187
P 9350 3100
F 0 "#PWR09" H 9350 3100 30  0001 C CNN
F 1 "GND" H 9350 3030 30  0001 C CNN
F 2 "" H 9350 3100 60  0000 C CNN
F 3 "" H 9350 3100 60  0000 C CNN
	1    9350 3100
	0    -1   -1   0   
$EndComp
Text GLabel 9650 3200 2    60   Input ~ 0
MCU_HEATER
Text GLabel 10000 3000 2    60   Input ~ 0
MCU_SENSOR
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
F 2 "footprint:SMT1x7" H 7700 1850 60  0001 C CNN
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
F 2 "LEDs:LED-5MM" H 6400 4050 60  0001 C CNN
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
F 2 "Diodes_SMD:Diode_SOT23" H 6470 4452 29  0001 C CNN
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
L +5V #PWR010
U 1 1 54BBCFD3
P 9600 3350
F 0 "#PWR010" H 9600 3440 20  0001 C CNN
F 1 "+5V" H 9600 3440 30  0000 C CNN
F 2 "" H 9600 3350 60  0000 C CNN
F 3 "" H 9600 3350 60  0000 C CNN
	1    9600 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 54BBD137
P 9600 6300
F 0 "#PWR011" H 9600 6300 30  0001 C CNN
F 1 "GND" H 9600 6230 30  0001 C CNN
F 2 "" H 9600 6300 60  0000 C CNN
F 3 "" H 9600 6300 60  0000 C CNN
	1    9600 6300
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 P5
U 1 1 54C97D24
P 9050 1350
F 0 "P5" H 9050 1550 50  0000 C CNN
F 1 "JACK" V 9150 1350 50  0000 C CNN
F 2 "Connect:bornier4" H 9050 1350 60  0001 C CNN
F 3 "" H 9050 1350 60  0000 C CNN
	1    9050 1350
	-1   0    0    1   
$EndComp
$Comp
L +12V #PWR012
U 1 1 54E59C79
P 3950 5050
F 0 "#PWR012" H 3950 5000 20  0001 C CNN
F 1 "+12V" H 3950 5150 30  0000 C CNN
F 2 "" H 3950 5050 60  0000 C CNN
F 3 "" H 3950 5050 60  0000 C CNN
	1    3950 5050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 54EB97DD
P 9400 2500
F 0 "#PWR013" H 9400 2500 30  0001 C CNN
F 1 "GND" H 9400 2430 30  0001 C CNN
F 2 "" H 9400 2500 60  0000 C CNN
F 3 "" H 9400 2500 60  0000 C CNN
	1    9400 2500
	0    -1   -1   0   
$EndComp
Text GLabel 9300 2900 2    60   Input ~ 0
MCU_STANDBY
Text GLabel 8450 4550 0    60   Input ~ 0
MCU_STANDBY
Text GLabel 9950 1200 2    60   Input ~ 0
STANDBY
$Comp
L R R12
U 1 1 5536EDCE
P 2850 4500
F 0 "R12" V 2930 4500 40  0000 C CNN
F 1 "100K" V 2857 4501 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2780 4500 30  0001 C CNN
F 3 "" H 2850 4500 30  0000 C CNN
	1    2850 4500
	0    -1   -1   0   
$EndComp
Text GLabel 1400 4500 0    60   Input ~ 0
STANDBY
Text GLabel 3800 4500 2    60   Input ~ 0
MCU_STANDBY
Wire Wire Line
	1850 1850 1850 2050
Wire Wire Line
	1850 1350 1850 1550
Wire Wire Line
	1550 1350 2600 1350
Wire Wire Line
	2100 1350 2100 1550
Connection ~ 1850 1350
Wire Wire Line
	2100 1850 2100 2050
Wire Wire Line
	2500 2100 3000 2100
Wire Wire Line
	3000 1850 3000 2200
Connection ~ 3000 2100
Wire Wire Line
	2600 1550 2500 1550
Wire Wire Line
	2500 900  2500 1700
Wire Wire Line
	2500 900  2650 900 
Connection ~ 2500 1550
Wire Wire Line
	2950 900  3700 900 
Wire Wire Line
	3700 900  3700 1450
Wire Wire Line
	3600 1450 3900 1450
Connection ~ 2100 1350
Wire Wire Line
	3000 650  3000 1050
Connection ~ 3700 1450
Wire Wire Line
	4200 1450 4650 1450
Wire Wire Line
	4400 1450 4400 1550
Wire Wire Line
	4400 1850 4400 2100
Connection ~ 4400 1450
Wire Wire Line
	7550 4650 7550 3250
Wire Wire Line
	5600 4650 7550 4650
Wire Wire Line
	6950 4150 6950 4650
Wire Wire Line
	7150 3850 7150 4650
Connection ~ 7150 4650
Wire Wire Line
	7350 3550 7350 4650
Connection ~ 7350 4650
Wire Wire Line
	6950 3650 6950 3850
Wire Wire Line
	6550 3350 7800 3350
Wire Wire Line
	7150 3350 7150 3550
Wire Wire Line
	6550 3050 7800 3050
Wire Wire Line
	7350 3050 7350 3250
Wire Wire Line
	6550 2750 7800 2750
Wire Wire Line
	7550 2750 7550 2950
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
	6150 4400 6400 4400
Wire Wire Line
	6000 4050 6200 4050
Wire Wire Line
	5450 4050 5700 4050
Connection ~ 5450 3650
Wire Wire Line
	5600 4400 5850 4400
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
	9250 1500 9550 1500
Wire Wire Line
	9250 1400 9550 1400
Wire Wire Line
	9250 1300 9550 1300
Wire Wire Line
	5350 6350 4850 6350
Wire Wire Line
	3950 6350 4350 6350
Wire Wire Line
	9400 2500 9250 2500
Wire Wire Line
	9400 2400 9250 2400
Wire Wire Line
	1350 5600 2550 5600
Wire Wire Line
	9250 2800 9400 2800
Wire Wire Line
	9650 3200 9250 3200
Wire Wire Line
	8450 4550 8650 4550
Wire Wire Line
	8650 4550 8650 4500
Wire Wire Line
	8650 4500 8900 4500
Wire Wire Line
	9300 2900 9250 2900
Wire Wire Line
	10000 3000 9250 3000
Wire Wire Line
	9350 3100 9250 3100
Wire Wire Line
	9250 1200 9950 1200
Wire Wire Line
	1400 4500 2700 4500
Wire Wire Line
	3000 4500 3800 4500
$Comp
L FUSE F1
U 1 1 54E3A642
P 4600 6350
F 0 "F1" H 4700 6400 40  0000 C CNN
F 1 "FUSE" H 4500 6300 40  0000 C CNN
F 2 "footprint:SMD-3121" H 4600 6350 60  0001 C CNN
F 3 "" H 4600 6350 60  0000 C CNN
	1    4600 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2000 2500 2100
Wire Wire Line
	1250 1350 1000 1350
$Comp
L BSS138 T2
U 1 1 55374818
P 3150 5900
F 0 "T2" H 3150 5751 40  0000 R CNN
F 1 "BSN20" H 3150 6050 40  0000 R CNN
F 2 "Diodes_SMD:Diode_SOT23" H 3020 6002 29  0001 C CNN
F 3 "" H 3150 5900 60  0000 C CNN
	1    3150 5900
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 55374D90
P 3550 5150
F 0 "R4" V 3630 5150 40  0000 C CNN
F 1 "10K" V 3557 5151 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 3480 5150 30  0001 C CNN
F 3 "" H 3550 5150 30  0000 C CNN
	1    3550 5150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3700 5150 4250 5150
Connection ~ 3950 5150
Wire Wire Line
	3400 5150 3400 5500
Connection ~ 3400 5500
Wire Wire Line
	3250 5500 3650 5500
Wire Wire Line
	2550 5600 2550 5950
$Comp
L GND #PWR014
U 1 1 55375734
P 3250 6250
F 0 "#PWR014" H 3250 6250 30  0001 C CNN
F 1 "GND" H 3250 6180 30  0001 C CNN
F 2 "" H 3250 6250 60  0000 C CNN
F 3 "" H 3250 6250 60  0000 C CNN
	1    3250 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 6100 3250 6250
Wire Wire Line
	3250 5700 3250 5500
Wire Wire Line
	3650 5500 3650 5750
Wire Wire Line
	3950 6100 3950 6350
$Comp
L IRF7476 T1
U 1 1 5537EABA
P 3950 5750
F 0 "T1" H 3960 5920 60  0000 R CNN
F 1 "IRF7476" H 4000 5550 39  0000 R CNN
F 2 "SMD_Packages:SOIC-8-N" H 3950 5750 60  0001 C CNN
F 3 "" H 3950 5750 60  0000 C CNN
	1    3950 5750
	1    0    0    1   
$EndComp
Wire Wire Line
	3650 5750 3750 5750
Wire Wire Line
	4250 5650 4200 5650
Wire Wire Line
	4250 5150 4250 5650
Wire Wire Line
	4250 5550 4200 5550
Wire Wire Line
	4200 5600 4250 5600
Connection ~ 4250 5600
Connection ~ 4250 5550
Wire Wire Line
	3950 5150 3950 5050
Wire Wire Line
	4200 5850 4250 5850
Wire Wire Line
	4250 5850 4250 6100
Wire Wire Line
	4250 6100 3950 6100
Wire Wire Line
	4200 5900 4250 5900
Connection ~ 4250 5900
Wire Wire Line
	4200 5950 4250 5950
Connection ~ 4250 5950
Wire Wire Line
	4200 6000 4250 6000
Connection ~ 4250 6000
$Comp
L +5V #PWR?
U 1 1 555F6C15
P 5700 950
F 0 "#PWR?" H 5700 1040 20  0001 C CNN
F 1 "+5V" H 5700 1040 30  0000 C CNN
F 2 "" H 5700 950 60  0000 C CNN
F 3 "" H 5700 950 60  0000 C CNN
	1    5700 950 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 555F6C5C
P 5700 1350
F 0 "#PWR?" H 5700 1350 30  0001 C CNN
F 1 "GND" H 5700 1280 30  0001 C CNN
F 2 "" H 5700 1350 60  0000 C CNN
F 3 "" H 5700 1350 60  0000 C CNN
	1    5700 1350
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 555F6CC1
P 5700 1150
F 0 "C2" H 5700 1250 40  0000 L CNN
F 1 "100nF" H 5706 1065 40  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5738 1000 30  0001 C CNN
F 3 "" H 5700 1150 60  0000 C CNN
	1    5700 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 950  5700 1000
Wire Wire Line
	5700 1300 5700 1350
$Comp
L R R5
U 1 1 555FA70B
P 2750 5950
F 0 "R5" V 2830 5950 40  0000 C CNN
F 1 "1K" V 2757 5951 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2680 5950 30  0001 C CNN
F 3 "" H 2750 5950 30  0000 C CNN
	1    2750 5950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2950 5950 2900 5950
Wire Wire Line
	2550 5950 2600 5950
$Comp
L ENC SW5
U 1 1 5560728B
P 6900 3500
F 0 "SW5" H 6900 3250 60  0000 C CNN
F 1 "ENC" H 6900 3700 60  0000 C CNN
F 2 "footprint:encoder_alps-ec12d" H 6900 3500 60  0001 C CNN
F 3 "" H 6900 3500 60  0000 C CNN
	1    6900 3500
	1    0    0    -1  
$EndComp
Connection ~ 5450 3500
Wire Wire Line
	6600 3450 6700 3450
Wire Wire Line
	6550 3650 7800 3650
Wire Wire Line
	6700 3550 6650 3550
Wire Wire Line
	6650 3550 6650 3350
Connection ~ 6650 3350
Wire Wire Line
	6600 3450 6600 3650
Connection ~ 6600 3650
Wire Wire Line
	6700 3500 5450 3500
$EndSCHEMATC
