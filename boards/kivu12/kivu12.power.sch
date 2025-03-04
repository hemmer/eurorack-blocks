EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 7
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
L Connector_Generic:Conn_02x05_Odd_Even J0
U 1 1 6095C792
P 4700 4000
F 0 "J0" H 4750 4417 50  0000 C CNN
F 1 "POWER BUS" H 4750 4326 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x05_P2.54mm_Vertical" H 4700 4000 50  0001 C CNN
F 3 "~" H 4700 4000 50  0001 C CNN
F 4 "IDC Header" H 4700 4000 50  0001 C CNN "Device"
F 5 "CONN HEADER VERT 10POS 2.54MM" H 4700 4000 50  0001 C CNN "Description"
F 6 "No" H 4700 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 4700 4000 50  0001 C CNN "Dist"
F 8 "732-2094-ND" H 4700 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/würth-elektronik/61201021621/732-2094-ND/2060590" H 4700 4000 50  0001 C CNN "DistLink"
	1    4700 4000
	1    0    0    -1  
$EndComp
Text HLabel 5000 3900 2    50   Output ~ 0
GND
Text HLabel 5000 4000 2    50   Output ~ 0
GND
Text HLabel 5000 4100 2    50   Output ~ 0
GND
Text HLabel 4500 3900 0    50   Output ~ 0
GND
Text HLabel 4500 4000 0    50   Output ~ 0
GND
Text HLabel 4500 4100 0    50   Output ~ 0
GND
Text HLabel 7200 4450 3    50   Output ~ 0
-12V
Text HLabel 7200 3450 1    50   Output ~ 0
+12V
$Comp
L Device:C C1
U 1 1 6095DF4D
P 7200 4200
F 0 "C1" H 7315 4246 50  0000 L CNN
F 1 "10u" H 7315 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7238 4050 50  0001 C CNN
F 3 "~" H 7200 4200 50  0001 C CNN
F 4 "Ceramic Capacitor" H 7200 4200 50  0001 C CNN "Device"
F 5 "CAP CER 10UF 25V X5R 0805" H 7200 4200 50  0001 C CNN "Description"
F 6 "Yes" H 7200 4200 50  0001 C CNN "Place"
F 7 "Digikey" H 7200 4200 50  0001 C CNN "Dist"
F 8 "1276-2891-1-ND" H 7200 4200 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/samsung-electro-mechanics/CL21A106KAYNNNE/1276-2891-1-ND/3890977" H 7200 4200 50  0001 C CNN "DistLink"
	1    7200 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 6095F9C0
P 7200 3700
F 0 "C2" H 7315 3746 50  0000 L CNN
F 1 "10u" H 7315 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7238 3550 50  0001 C CNN
F 3 "~" H 7200 3700 50  0001 C CNN
F 4 "Ceramic Capacitor" H 7200 3700 50  0001 C CNN "Device"
F 5 "CAP CER 10UF 25V X5R 0805" H 7200 3700 50  0001 C CNN "Description"
F 6 "Yes" H 7200 3700 50  0001 C CNN "Place"
F 7 "Digikey" H 7200 3700 50  0001 C CNN "Dist"
F 8 "1276-2891-1-ND" H 7200 3700 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/samsung-electro-mechanics/CL21A106KAYNNNE/1276-2891-1-ND/3890977" H 7200 3700 50  0001 C CNN "DistLink"
	1    7200 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3550 7200 3450
Wire Wire Line
	7200 3850 7200 3950
Wire Wire Line
	7200 3950 7300 3950
Connection ~ 7200 3950
Wire Wire Line
	7200 3950 7200 4050
Wire Wire Line
	7200 4350 7200 4450
Text HLabel 7300 3950 2    50   Output ~ 0
GND
Text Notes 7450 7000 0    276  ~ 0
POWER
$Comp
L Device:Ferrite_Bead L1
U 1 1 5FCFE7A2
P 6750 3550
F 0 "L1" V 6476 3550 50  0000 C CNN
F 1 "Ferrite_Bead" V 6567 3550 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric" V 6680 3550 50  0001 C CNN
F 3 "~" H 6750 3550 50  0001 C CNN
F 4 "Ferrite Bead" H 6750 3550 50  0001 C CNN "Device"
F 5 "FERRITE BEAD 1 KOHM 0603 1LN" H 6750 3550 50  0001 C CNN "Description"
F 6 "Yes" H 6750 3550 50  0001 C CNN "Place"
F 7 "Digikey" H 6750 3550 50  0001 C CNN "Dist"
F 8 "732-1586-1-ND" H 6750 3550 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/würth-elektronik/742792664/732-1586-1-ND/1639530" H 6750 3550 50  0001 C CNN "DistLink"
	1    6750 3550
	0    1    1    0   
$EndComp
$Comp
L Device:D_Schottky D23
U 1 1 5FCFEAAA
P 6250 3550
F 0 "D23" H 6250 3334 50  0000 C CNN
F 1 "D_Schottky" H 6250 3425 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 6250 3550 50  0001 C CNN
F 3 "~" H 6250 3550 50  0001 C CNN
F 4 "Rectifier Diode" H 6250 3550 50  0001 C CNN "Device"
F 5 "DIODE SCHOTTKY 40V 1A SOD123" H 6250 3550 50  0001 C CNN "Description"
F 6 "Yes" H 6250 3550 50  0001 C CNN "Place"
F 7 "Digikey" H 6250 3550 50  0001 C CNN "Dist"
F 8 "1N5819HW-FDICT-ND" H 6250 3550 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/diodes-incorporated/1N5819HW-7-F/1N5819HW-FDICT-ND/815283" H 6250 3550 50  0001 C CNN "DistLink"
	1    6250 3550
	-1   0    0    1   
$EndComp
$Comp
L Device:D_Schottky D24
U 1 1 5FCFF182
P 6250 4350
F 0 "D24" H 6250 4566 50  0000 C CNN
F 1 "D_Schottky" H 6250 4475 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 6250 4350 50  0001 C CNN
F 3 "~" H 6250 4350 50  0001 C CNN
F 4 "Rectifier Diode" H 6250 4350 50  0001 C CNN "Device"
F 5 "DIODE SCHOTTKY 40V 1A SOD123" H 6250 4350 50  0001 C CNN "Description"
F 6 "Yes" H 6250 4350 50  0001 C CNN "Place"
F 7 "Digikey" H 6250 4350 50  0001 C CNN "Dist"
F 8 "1N5819HW-FDICT-ND" H 6250 4350 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/diodes-incorporated/1N5819HW-7-F/1N5819HW-FDICT-ND/815283" H 6250 4350 50  0001 C CNN "DistLink"
	1    6250 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:Ferrite_Bead L2
U 1 1 5FCFF328
P 6750 4350
F 0 "L2" V 6476 4350 50  0000 C CNN
F 1 "Ferrite_Bead" V 6567 4350 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric" V 6680 4350 50  0001 C CNN
F 3 "~" H 6750 4350 50  0001 C CNN
F 4 "Ferrite Bead" H 6750 4350 50  0001 C CNN "Device"
F 5 "FERRITE BEAD 1 KOHM 0603 1LN" H 6750 4350 50  0001 C CNN "Description"
F 6 "Yes" H 6750 4350 50  0001 C CNN "Place"
F 7 "Digikey" H 6750 4350 50  0001 C CNN "Dist"
F 8 "732-1586-1-ND" H 6750 4350 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/würth-elektronik/742792664/732-1586-1-ND/1639530" H 6750 4350 50  0001 C CNN "DistLink"
	1    6750 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	6400 4350 6600 4350
Wire Wire Line
	6900 3550 7200 3550
Wire Wire Line
	6900 4350 7200 4350
Wire Wire Line
	6400 3550 6600 3550
Connection ~ 7200 3550
Text Label 5000 4200 0    50   ~ 0
+12E
Text Label 4500 4200 2    50   ~ 0
+12E
Text Label 5000 3800 0    50   ~ 0
-12E
Text Label 4500 3800 2    50   ~ 0
-12E
Text Label 6100 3550 2    50   ~ 0
+12E
Text Label 6100 4350 2    50   ~ 0
-12E
Connection ~ 7200 4350
$EndSCHEMATC
