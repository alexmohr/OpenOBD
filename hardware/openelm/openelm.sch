EESchema Schematic File Version 4
LIBS:74xx
LIBS:switcher
LIBS:adc-dac
LIBS:analog-switches
LIBS:atmel
LIBS:bjt
LIBS:can
LIBS:capacitive
LIBS:cmos4000
LIBS:conn
LIBS:device
LIBS:digital-audio
LIBS:digpot
LIBS:diode
LIBS:display
LIBS:fet
LIBS:hc11
LIBS:i2c
LIBS:inductive
LIBS:intel
LIBS:interface
LIBS:linear
LIBS:memory
LIBS:microchip
LIBS:opto
LIBS:periph
LIBS:power
LIBS:protection
LIBS:regul
LIBS:renesas
LIBS:resist
LIBS:supervisor
LIBS:video
LIBS:figaro
LIBS:radio
LIBS:automation
LIBS:graphic
LIBS:xilinx
LIBS:openelm-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+12C #PWR0101
U 1 1 5C3F78BF
P 800 800
F 0 "#PWR0101" H 800 650 50  0001 C CNN
F 1 "+12C" H 815 973 50  0000 C CNN
F 2 "" H 800 800 50  0001 C CNN
F 3 "" H 800 800 50  0001 C CNN
	1    800  800 
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x08_Top_Bottom J?
U 1 1 5C3F7FD2
P 2600 3250
F 0 "J?" V 2604 2762 50  0000 R CNN
F 1 "Conn_02x08_Top_Bottom" V 2695 2762 50  0000 R CNN
F 2 "SparkFun-Connectors:OBDII" H 2600 3250 50  0001 C CNN
F 3 "~" H 2600 3250 50  0001 C CNN
	1    2600 3250
	0    -1   1    0   
$EndComp
$Comp
L Connector-ML:RPi_GPIO J?
U 1 1 5C3F82F0
P 8450 3900
F 0 "J?" H 9200 4187 60  0000 C CNN
F 1 "RPi_GPIO" H 9200 4081 60  0000 C CNN
F 2 "" H 8450 3900 60  0000 C CNN
F 3 "" H 8450 3900 60  0000 C CNN
	1    8450 3900
	1    0    0    -1  
$EndComp
$Comp
L PIC18F2480-I_SO:PIC18F2480-I_SO U?
U 1 1 5C3F8E3D
P 6300 3100
F 0 "U?" H 6300 4365 50  0000 C CNN
F 1 "PIC18F2480-I_SO" H 6300 4274 50  0000 C CNN
F 2 "SOIC127P1030X265-28N" H 6300 3100 50  0001 L BNN
F 3 "PIC18F2480-I/SO" H 6300 3100 50  0001 L BNN
F 4 "SO-28 Microchip" H 6300 3100 50  0001 L BNN "Field4"
F 5 "Unavailable" H 6300 3100 50  0001 L BNN "Field5"
F 6 "PIC18F Series 16 kB Flash 768 B RAM 40 MHz 8-Bit Microcontroller - SOIC-28" H 6300 3100 50  0001 L BNN "Field6"
F 7 "None" H 6300 3100 50  0001 L BNN "Field7"
F 8 "Microchip" H 6300 3100 50  0001 L BNN "Field8"
	1    6300 3100
	1    0    0    -1  
$EndComp
Wire Bus Line
	10150 4200 10350 4200
Wire Bus Line
	10350 4200 10350 3100
Wire Bus Line
	10350 3100 8000 3100
Wire Bus Line
	10150 4300 10500 4300
Wire Bus Line
	10500 3000 8000 3000
Wire Bus Line
	10500 3000 10500 4300
Text Label 2400 3050 1    50   ~ 0
J1850_BUS+
Text Label 2600 3050 1    50   ~ 0
CHASIS_GROUND
Text Label 2700 3050 1    50   ~ 0
SIGNAL_GROUND
Text Label 2800 3050 1    50   ~ 0
CAN_HIGH
Text Label 2900 3050 1    50   ~ 0
K-LINE
Text Label 2400 3550 3    50   ~ 0
J1850_BUS-
Text Label 2800 3550 3    50   ~ 0
CAN_LOW
Text Label 2900 3550 3    50   ~ 0
L_LINE
Text Label 3000 3550 3    50   ~ 0
BAT+
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 5C3F9B10
P 3500 5000
F 0 "J?" H 3580 4992 50  0000 L CNN
F 1 "Conn_01x04" H 3580 4901 50  0000 L CNN
F 2 "" H 3500 5000 50  0001 C CNN
F 3 "~" H 3500 5000 50  0001 C CNN
	1    3500 5000
	1    0    0    -1  
$EndComp
Text Label 3300 4900 2    50   ~ 0
VO+
Text Label 3300 5000 2    50   ~ 0
GND
Text Label 3300 5100 2    50   ~ 0
IN+
Text Label 3300 5200 2    50   ~ 0
ENABLE
Wire Wire Line
	3050 5100 3050 5150
Wire Wire Line
	3050 5200 3300 5200
Wire Wire Line
	3050 5150 3000 5150
Wire Wire Line
	3000 5150 3000 3550
Connection ~ 3050 5150
Wire Wire Line
	3050 5150 3050 5200
Wire Wire Line
	3300 5000 3100 5000
Wire Wire Line
	3100 5000 3100 2900
Wire Wire Line
	2600 2900 2600 3050
Wire Wire Line
	2600 2900 3100 2900
Wire Wire Line
	3050 5100 3300 5100
Wire Wire Line
	3950 5800 3950 2700
Wire Wire Line
	3950 2700 2700 2700
Wire Wire Line
	2700 2700 2700 3050
Wire Wire Line
	3950 5800 8250 5800
Wire Wire Line
	8000 2200 10650 2200
Wire Wire Line
	10650 2200 10650 4600
Wire Wire Line
	10650 4600 10150 4600
$Comp
L Device:R R120
U 1 1 5C3FB07E
P 3500 1900
F 0 "R120" H 3570 1946 50  0000 L CNN
F 1 "R" H 3570 1855 50  0000 L CNN
F 2 "" V 3430 1900 50  0001 C CNN
F 3 "~" H 3500 1900 50  0001 C CNN
	1    3500 1900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
