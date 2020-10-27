EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Robot do wydawania leków"
Date "2020-09-13"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L New_LibraryKiCad:RTC_module_DS1307 U2
U 1 1 5F5D2CE7
P 4700 2250
F 0 "U2" H 5178 2301 50  0000 L CNN
F 1 "RTC_module_DS1307" H 5178 2210 50  0000 L CNN
F 2 "" H 4700 2600 50  0001 C CNN
F 3 "" H 4700 2600 50  0001 C CNN
	1    4700 2250
	-1   0    0    -1  
$EndComp
$Comp
L New_LibraryKiCad:ESP8266_module U3
U 1 1 5F5E2559
P 4700 4450
F 0 "U3" H 4700 5450 50  0000 C CNN
F 1 "ESP8266_module" H 4700 5350 50  0000 C CNN
F 2 "RF_Module:ESP-12E" H 4600 4550 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 4350 4550 50  0001 C CNN
	1    4700 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 5F5E72F1
P 1550 3750
F 0 "BT1" H 1668 3846 50  0000 L CNN
F 1 "Battery_Cell" H 1668 3755 50  0000 L CNN
F 2 "" V 1550 3810 50  0001 C CNN
F 3 "~" V 1550 3810 50  0001 C CNN
	1    1550 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 2800 4750 3650
Connection ~ 4750 2800
Wire Wire Line
	7800 2600 7800 2800
$Comp
L New_LibraryKiCad:Driver_module_ULN2003 U4
U 1 1 5F5D966D
P 7850 2250
F 0 "U4" H 7850 2675 50  0000 C CNN
F 1 "Driver_module_ULN2003" H 7850 2584 50  0000 C CNN
F 2 "" H 7850 2700 50  0001 C CNN
F 3 "" H 7850 2700 50  0001 C CNN
	1    7850 2250
	1    0    0    -1  
$EndComp
$Comp
L Motor:Stepper_Motor_unipolar_5pin M1
U 1 1 5F5D38BA
P 9000 3450
F 0 "M1" H 9188 3574 50  0000 L CNN
F 1 "Stepper_Motor_unipolar_5pin" H 9188 3483 50  0000 L CNN
F 2 "" H 9010 3440 50  0001 C CNN
F 3 "http://www.infineon.com/dgdl/Application-Note-TLE8110EE_driving_UniPolarStepperMotor_V1.1.pdf?fileId=db3a30431be39b97011be5d0aa0a00b0" H 9010 3440 50  0001 C CNN
	1    9000 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 2450 8500 3350
Wire Wire Line
	9100 3150 9100 2350
Wire Wire Line
	8800 3150 8800 2150
Wire Wire Line
	8900 3150 8900 2250
Wire Wire Line
	5250 2200 5400 2200
Wire Wire Line
	5400 2200 5400 2800
Connection ~ 5400 2800
Wire Wire Line
	5400 2800 4750 2800
Wire Wire Line
	7200 2400 7200 4650
Wire Wire Line
	7100 2300 7200 2300
Wire Wire Line
	7200 2200 7000 2200
Wire Wire Line
	7000 2200 7000 4450
Wire Wire Line
	7200 2100 6900 2100
Wire Wire Line
	6900 2100 6900 4350
Wire Wire Line
	6900 4350 5300 4350
$Comp
L Transistor_BJT:2N3904 Q1
U 1 1 5F60CB05
P 6000 5250
F 0 "Q1" H 6191 5296 50  0000 L CNN
F 1 "2N3904" H 6191 5205 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 6200 5175 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 6000 5250 50  0001 L CNN
	1    6000 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:Buzzer BZ1
U 1 1 5F640523
P 6000 5850
F 0 "BZ1" H 6152 5879 50  0000 L CNN
F 1 "Buzzer_z_generatorem_FY248" H 6152 5788 50  0000 L CNN
F 2 "" V 5975 5950 50  0001 C CNN
F 3 "~" V 5975 5950 50  0001 C CNN
	1    6000 5850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5F66490C
P 5650 5250
F 0 "R3" V 5443 5250 50  0000 C CNN
F 1 "10k" V 5534 5250 50  0000 C CNN
F 2 "" V 5580 5250 50  0001 C CNN
F 3 "~" H 5650 5250 50  0001 C CNN
	1    5650 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	5800 5750 5900 5750
$Comp
L Device:R R6
U 1 1 5F6615A0
P 5650 5750
F 0 "R6" V 5443 5750 50  0000 C CNN
F 1 "R" V 5534 5750 50  0000 C CNN
F 2 "" V 5580 5750 50  0001 C CNN
F 3 "~" H 5650 5750 50  0001 C CNN
	1    5650 5750
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 5F690B7A
P 6100 4900
F 0 "R1" H 6050 4950 50  0000 R CNN
F 1 "1k" H 6050 4850 50  0000 R CNN
F 2 "" V 6030 4900 50  0001 C CNN
F 3 "~" H 6100 4900 50  0001 C CNN
	1    6100 4900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_LED SW1
U 1 1 5F5DAB3D
P 6100 3600
F 0 "SW1" H 6100 3985 50  0000 C CNN
F 1 "SW_Push_LED" H 6100 3894 50  0000 C CNN
F 2 "" H 6100 3900 50  0001 C CNN
F 3 "~" H 6100 3900 50  0001 C CNN
	1    6100 3600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5F5F7A20
P 6000 4050
F 0 "R2" H 5950 4100 50  0000 R CNN
F 1 "100k" H 5950 4000 50  0000 R CNN
F 2 "" V 5930 4050 50  0001 C CNN
F 3 "~" H 6000 4050 50  0001 C CNN
	1    6000 4050
	1    0    0    -1  
$EndComp
$Comp
L pspice:0 GND
U 1 1 5F603E61
P 5550 2150
F 0 "GND" H 5450 2050 50  0000 L CNN
F 1 "0" H 5550 2239 50  0001 C CNN
F 2 "" H 5550 2150 50  0001 C CNN
F 3 "~" H 5550 2150 50  0001 C CNN
	1    5550 2150
	1    0    0    -1  
$EndComp
$Comp
L pspice:0 GND
U 1 1 5F60C623
P 7900 2600
F 0 "GND" H 7800 2500 50  0000 L CNN
F 1 "0" H 7900 2689 50  0001 C CNN
F 2 "" H 7900 2600 50  0001 C CNN
F 3 "~" H 7900 2600 50  0001 C CNN
	1    7900 2600
	1    0    0    -1  
$EndComp
$Comp
L pspice:0 GND
U 1 1 5F6174EB
P 6000 4200
F 0 "GND" H 5900 4100 50  0000 L CNN
F 1 "0" H 6000 4289 50  0001 C CNN
F 2 "" H 6000 4200 50  0001 C CNN
F 3 "~" H 6000 4200 50  0001 C CNN
	1    6000 4200
	1    0    0    -1  
$EndComp
$Comp
L pspice:0 GND
U 1 1 5F62A071
P 4700 5050
F 0 "GND" H 4600 4950 50  0000 L CNN
F 1 "0" H 4700 5139 50  0001 C CNN
F 2 "" H 4700 5050 50  0001 C CNN
F 3 "~" H 4700 5050 50  0001 C CNN
	1    4700 5050
	1    0    0    -1  
$EndComp
$Comp
L pspice:0 GND
U 1 1 5F62B8B6
P 5900 6000
F 0 "GND" H 5800 5900 50  0000 L CNN
F 1 "0" H 5900 6089 50  0001 C CNN
F 2 "" H 5900 6000 50  0001 C CNN
F 3 "~" H 5900 6000 50  0001 C CNN
	1    5900 6000
	1    0    0    -1  
$EndComp
$Comp
L pspice:0 GND
U 1 1 5F62CD02
P 6100 5450
F 0 "GND" H 6000 5350 50  0000 L CNN
F 1 "0" H 6100 5539 50  0001 C CNN
F 2 "" H 6100 5450 50  0001 C CNN
F 3 "~" H 6100 5450 50  0001 C CNN
	1    6100 5450
	1    0    0    -1  
$EndComp
$Comp
L pspice:0 GND
U 1 1 5F63417C
P 1550 3850
F 0 "GND" H 1450 3750 50  0000 L CNN
F 1 "0" H 1550 3939 50  0001 C CNN
F 2 "" H 1550 3850 50  0001 C CNN
F 3 "~" H 1550 3850 50  0001 C CNN
	1    1550 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5F6361A7
P 5800 2300
F 0 "R4" V 5593 2300 50  0000 C CNN
F 1 "10k" V 5684 2300 50  0000 C CNN
F 2 "" V 5730 2300 50  0001 C CNN
F 3 "~" H 5800 2300 50  0001 C CNN
	1    5800 2300
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 5F638A6A
P 5800 2600
F 0 "R5" V 5593 2600 50  0000 C CNN
F 1 "10k" V 5684 2600 50  0000 C CNN
F 2 "" V 5730 2600 50  0001 C CNN
F 3 "~" H 5800 2600 50  0001 C CNN
	1    5800 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	8500 2050 8600 2050
Wire Wire Line
	8600 2050 8600 3550
Wire Wire Line
	8800 2150 8500 2150
Wire Wire Line
	8900 2250 8500 2250
Wire Wire Line
	9100 2350 8500 2350
Wire Wire Line
	8700 3350 8500 3350
Wire Wire Line
	8600 3550 8700 3550
Wire Wire Line
	5900 6000 5900 5950
Wire Wire Line
	5250 2100 5550 2100
Wire Wire Line
	5550 2100 5550 2150
$Comp
L New_LibraryKiCad:Converter_module U1
U 1 1 5F67BEC6
P 2750 2950
F 0 "U1" H 2750 3365 50  0000 C CNN
F 1 "Converter_module" H 2750 3274 50  0000 C CNN
F 2 "" H 2750 3400 50  0001 C CNN
F 3 "" H 2750 3400 50  0001 C CNN
	1    2750 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 2800 2100 2800
Wire Wire Line
	2100 3050 2100 2950
Wire Wire Line
	3400 3050 3400 2950
$Comp
L pspice:0 GND
U 1 1 5F685D19
P 2100 3050
F 0 "GND" H 2000 2950 50  0000 L CNN
F 1 "0" H 2100 3139 50  0001 C CNN
F 2 "" H 2100 3050 50  0001 C CNN
F 3 "~" H 2100 3050 50  0001 C CNN
	1    2100 3050
	1    0    0    -1  
$EndComp
$Comp
L pspice:0 GND
U 1 1 5F687759
P 3400 3050
F 0 "GND" H 3300 2950 50  0000 L CNN
F 1 "0" H 3400 3139 50  0001 C CNN
F 2 "" H 3400 3050 50  0001 C CNN
F 3 "~" H 3400 3050 50  0001 C CNN
	1    3400 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 4550 7100 2300
Wire Wire Line
	5300 4650 7200 4650
Wire Wire Line
	5300 4550 7100 4550
Wire Wire Line
	5300 4450 7000 4450
Wire Wire Line
	5300 3600 3950 3600
Wire Wire Line
	3950 3600 3950 4850
Wire Wire Line
	3950 4850 4100 4850
Wire Wire Line
	5300 3600 5300 3850
Wire Wire Line
	5450 3950 5300 3950
Wire Wire Line
	5300 4050 5550 4050
Wire Wire Line
	5450 2400 5250 2400
Wire Wire Line
	5250 2300 5550 2300
Wire Wire Line
	6000 3800 6000 3900
Wire Wire Line
	6000 3900 5650 3900
Wire Wire Line
	5650 3900 5650 4150
Wire Wire Line
	5650 4150 5300 4150
Connection ~ 6000 3900
Wire Wire Line
	6000 3400 6000 2800
Wire Wire Line
	5400 2800 6000 2800
Connection ~ 6000 2800
Wire Wire Line
	6000 2800 7800 2800
Wire Wire Line
	3400 2800 4750 2800
Wire Wire Line
	1550 2800 1550 3550
Wire Wire Line
	6100 3800 6100 4750
Wire Wire Line
	5300 4250 5500 4250
Wire Wire Line
	5500 4250 5500 5250
Text GLabel 6100 3400 1    50   Input ~ 0
12V
Wire Wire Line
	5500 5750 5500 5250
Connection ~ 5500 5250
Wire Wire Line
	5450 2400 5450 2600
Wire Wire Line
	5550 2300 5550 4050
Wire Wire Line
	5650 2300 5550 2300
Connection ~ 5550 2300
Wire Wire Line
	5650 2600 5450 2600
Connection ~ 5450 2600
Wire Wire Line
	5450 2600 5450 3950
Wire Wire Line
	5950 2600 5950 2300
Text GLabel 6100 2300 2    50   Input ~ 0
3V3
Connection ~ 5950 2300
Wire Wire Line
	5950 2300 6100 2300
$EndSCHEMATC