# ArduinoDAC User & Documentation Guide 
**Complete** guide for constructing and operating a four-channel, low-cost, precision 20-bit DAC (EVAL-AD5790) using an Arduino MEGA 2560.

Created by Nikhil Ajjarapu. 

Acknowledgments: Thanks to the Houck Group at Princeton University for their direction, the creators of OpenDacs.com for the initial list of hardware, and the Simon Group at University of Chicago for the initial Arduino code. 


## Table of Contents: 
[Parts List](https://github.com/Nikhil-a29/ArduinoDAC/blob/master/README.md#parts-list)

[Build Instructions with Pictures](https://github.com/Nikhil-a29/ArduinoDAC/blob/master/README.md#build)

[Complete Code](https://github.com/Nikhil-a29/ArduinoDAC/blob/master/README.md#program)

[Operating Instructions](https://github.com/Nikhil-a29/ArduinoDAC/blob/master/README.md#testing)

[Measurement Results](https://github.com/Nikhil-a29/ArduinoDAC/blob/master/README.md#results)

## Introduction/Overview

This device is composed of four EVAL-AD5790 voltage output boards which can be used simultaneously with an Arduino microcontroller and can output from -10V to +10V. This is a very cost efficient alternative to using other DC precision voltage sources. It is more economical than using an SDP board coupled with an EVAL Board since multiple DACS can be controlled at the same time, rather than one at a time. Note that you will need a dedicated computer to enter commands into the Arduino.
Contact me at najjarapu20@lawrenceville.org if you have any questions. 

## Parts List

| Part                                                              | Link/Part Number (Part number is from Digikey)                            | Unit Price ($) | # Needed | Total Price |
|--------------------------------------------------------------------|----------------------------------------------|----------------|----------|-------------|
| EVAL-AD5790                                                        | https://tinyurl.com/y5ac79nn                 | 149            | 4        | 596         |
| 2 position .100” terminal block                                    | A98333-ND                                    | .88            | 1        | .88         |
| 40 position Straight header .100"                                  | S1012EC-40-ND                                | .51            | 1        | .51         |
| Enclosure                                                          | NHC-14153-ND                                 | 69.05          | 1        | 69.05       |
| Switchcraft D3M                                                    | SC1010-ND                                    | 6.72           | 1        | 6.72        |
| Switchcraft A3F                                                    | SC1001-ND                                    | 4.40           | 1        | 4.40        |
| 6" BNC female bulkhead/SMB bulkhead female right angle cable                                             | https://tinyurl.com/yxvmbedu                 | 10             | 4        | 40          |
| Arduino MEGA 2560                                                  | https://store.arduino.cc/usa/                | 38.5           | 1        | 38.5        |
| USB-A to USB B cable (2.0)                                         | https://tinyurl.com/y6thfp5o                 | 5.10           | 1        | 5.10        |
| +/-15 Acopian Dual output power supply TD15-40                     | https://tinyurl.com/yxzm7tsh                 | 230            | 1        | 230         |
| Custom Arduino shield                                              | https://oshpark.com/shared_projects/ftXHJ1GP | 33.90          | 1/3      | 33.90       |
| Custom SPI Board                                                   | https://oshpark.com/shared_projects/pSHPUQew | 18.75          | 1/3      | 18.75       |
| Custom Digital Power Supply Board                                  | https://oshpark.com/shared_projects/pqSsepj0 | 12.35          | 1/3      | 12.35       |
| Custom Analog Power Supply Board                                   | https://oshpark.com/shared_projects/X0koA59b | 14.85          | 1/3      | 14.85       |
| Custom 10 pin Connector Board                                      | https://oshpark.com/shared_projects/PcULHn2O | 1.35           | 4/6      | 2.70        |
| 10 position ribbon cable                                           | A3AAH-1006G                                  | 2.53           | 1        | 2.53        |
| Connector Header Through Hole 3 position 0.200"                    | SAM15957-ND                                  | .43            | 5        | 2.15        |
| Connector Header Through Hole 2 position 0.200"                    | SAM10858-ND                                  | .28            | 5        | 1.40        |
| 6 Position Receptacle Connector .100”                              | A32934-ND                                    | 1.67           | 1        | 1.67        |
| Right Angle 10 Position .100”                                      | S2111E-05-ND                                 | 1.03           | 4        | 4.12        |
| 2 Position wire to board terminal block .200"                      | A113320-ND                                   | 1.04           | 1        | 1.04        |
| 3 Position wire to board terminal block .200"                      | A113321-ND                                   | 1.18           | 1        | 1.18        |
| Hook-Up Wire                                                       | 1568-1357-ND                                 | 16.95          | 1        | 16.95       |
| 10 Position Receptacle Connector 0.100" (2.54mm) Through Hole Gold | A32936-ND                                    | 3.15           | 8        | 25.12       |
| 18 AWG 3 Conductor 3-Prong Power Cord with Open Wiring             | https://tinyurl.com/y67ck8r9                 | 12.99          | 1        | 12.99       |
| 18-22 AWG wire lug                           | A1061CT-ND	                               | .20            | 6        | 1.2         |
| TOTAL                                                              |                                              |                |          | 1144.06     |
| UNIT PRICE (per DAC)                                               |                                              |                |          | 286.02      |


## Build

<img width="487" alt="Screen Shot 2019-08-12 at 2 43 39 PM" src="https://user-images.githubusercontent.com/33910853/62889807-1753b900-bd10-11e9-81da-656170709000.png">

*Note: I accidentally added solder to 44, but there shouldn’t be a pin there. You also don't need to add the three terminal blocks to the bottom unless you want LEDs, they weren't necessary for my setup since the serial monitor will debug for you, but you can add if you'd like.*

1. Solder the 6 position receptacle connector to the MISO SCK RESET MOSI GND 5V group. Solder straight headers to the board where shown which will attach to the Arduino Mega. **Attach solder on the top of the board that connects the 3v3 pin to the 5V pin and do not add a pin to 3v3.** This is because the EVAL board needs 5V between VCC and DGND, but the shield connects the 3.3V pin to the green terminal block.
Attach the shield to the Arduino, making sure the pins line up. I recommend doing all of the drilling (see later steps) all at one time - here, you can drill holes into the bottom of the enclosure and attach the base plastic cover of the Arduino to the screws to secure it. 



<img width="500" alt="Screen Shot 2019-08-12 at 2 53 19 PM" src="https://user-images.githubusercontent.com/33910853/62890206-f8095b80-bd10-11e9-8edb-8e4b8faebb4c.png">


2. Solder four 10 pin receptacle connectors to SPI Board and add 10 straight headers so the ribbon cable can attach. Create holes using drill and attach SPI Board to base of the enclosure. 

<img width="211" alt="Screen Shot 2019-08-12 at 2 54 25 PM" src="https://user-images.githubusercontent.com/33910853/62890255-196a4780-bd11-11e9-8beb-dcd095c52a64.png">

3. Solder 10 pin receptacle connector to 10 pin board.  Solder right angle connector to gold side. Make four of these. 

<img width="350" alt="Screen Shot 2019-08-12 at 2 56 01 PM" src="https://user-images.githubusercontent.com/33910853/62890347-533b4e00-bd11-11e9-805c-0076612a6745.png">

4. Cut hole for USB A to B plug and D3M connector (and 1-2 screw hole(s) for the D3M to keep it in place). Strip ends of hook up wires and solder to D3M connector, strip the other end and attach to the screw terminals shown in step 6. 

<img width="300" alt="Screen Shot 2019-08-12 at 4 50 40 PM" src="https://user-images.githubusercontent.com/33910853/62897481-5e967580-bd21-11e9-8770-2ecbe73073cd.png">

5. Drill holes for BNC cables. Please use a drill press, because of me our lab has to live with this as the face of the box. 

<img width="500" alt="Screen Shot 2019-08-12 at 2 55 22 PM" src="https://user-images.githubusercontent.com/33910853/62890296-3c94f700-bd11-11e9-9452-7d6df5d183cb.png">

6. Attach previously made connectors to J3. On the EVAL board, insert LK7 (LDAC pin needs to be pulled low in order for the DAC register to be updated) and move LK1 from position A to position B since digital power is coming from J1, not SDP board. Connect the BNC cables to VOUT_BUF on the EVAL board. Solder .200” 3 pin and .200” 2 pin connector to Analog & Digital PCB’s, respectively. Solder the 3 position .200” screw terminal and 2 position .200” screw terminal to Analog and Digital power supply boards, respectively. Screw into EVAL boards. Attach this whole complex after attaching the analog power wires to VDD, AGND, and VSS and the digital power wires to VCC and DGND. 

<img width="500" alt="Screen Shot 2019-08-12 at 2 56 41 PM" src="https://user-images.githubusercontent.com/33910853/62890399-6bab6880-bd11-11e9-9b09-8438ec349a96.png">

7. Crimp wire connectors to hook-up wire/appropriate wire. Cover with heat-shrink tubing. Attach to +V, COMMON, -V. ***Keep +S linked to +V and -S linked to -V using the included metal connectors that should already be attached.*** Attach same connectors to a standard cable that plugs into the wall and separate Live, Neutral, and Ground. Connect the COM ground to the AC ground using a wire. ***Do not plug into the wall until done with all steps***
Solder wires to the A3F 3 Position Circular Connector Plug, put metal cover back over the soldered connections. I would also put the power supply in a box so that the AC connections aren't exposed. 

<img width="507" alt="Screen Shot 2019-08-12 at 2 58 43 PM" src="https://user-images.githubusercontent.com/33910853/62890558-b7f6a880-bd11-11e9-8b1c-504505a11eab.png">

8. Strip the ends of the analog power wires (red yellow black) and screw them into the screw terminal. Do the same with the digital power wires. (You will need to remove the DAC complex from the SDP board).  Connect ribbon cable. **Not shown in this picture is the metal front plate.**

## Program

Download the AD5790.h library, ArduinoDACSerial, and ArduinoMegaCode from this repository into the Arduino IDE (I used v. 1.8.9). 

## Testing

Before using the given commands to test, first check if everything is receiving the correct voltages. 

Plug in the power supply, but don’t plug the A3F plug into the D3M yet. Using a voltmeter, check the voltage between +V / COM and -V / COM - this should be around +15V and -15V, respectively. After you check this, plug in the A3F plug into the D3M. Then check the voltage between VDD & AGND and VCC & AGND, if these are +15 and -15V respectively, then your soldering was good.
Now, plug in the USB A wire into the computer you want to control the Arduino with. Check the voltage between VCC and DGND, this should be +5V.  
**Always make sure that you plug in the Acopian before the USB into your computer, the digital power supply should not be on if the analog power supply isn't.**

Now, you can use the Arduino Program to try it out. Download the Arduino IDE. Make three folders in a sketch and import the MEGA_Code, AD5790.h, and DACSerial. Press “verify” to make sure the code is good syntax-wise. Press upload, and once it says “uploaded” on the bottom then you can open the Serial Monitor, which is shown using this icon in the top right corner: . Once you open it, you can start operating the DACs using the premade commands below. 

**Remember to put the pins in the correct orientation according to step 6.**

## Operating Commands
**Unfortunately, because floats in Arduino only range from -3.4028235E38 to 3.4028235E38, you cannot read an accurate voltage from the DAC itself (since the range is from -10 to 10). I suggest using an oscilloscope to find the correct voltage you want. Use the following equation to estimate the corresponding bitcode for the voltage you want: y = 13225x + 132536.**

There are five commands: `Initialize`, `Set`, `Read`, `Ramp`, and `Help`.



Syntax:  To initialize a specific DAC before you can do anything with it, deliver the following command:

`INIT [DAC#]`

Example: `INIT 2`

To set the voltage ouput for a specific DAC, deliver the following command:

`SET [DAC#] [DAC Value - bitcode]`

Example: `SET 1 196540`

This would set it to 5.0 V. 

To ramp the voltage ouput for a specific DAC at a specific rate for an amount of time, deliver the following command:

`RAMP [DAC#] [DAC_Final_Value] [Step_Size] [Step_Time]`

Example: `RAMP 1 196540 13225 10000`

This would ramp dac 1 from 0V to 5V at a rate of 1 V per second (Step_Time is in millis)

To Read voltage from the DAC register, deliver the following command: 

`READ [DAC#]`

Example: `READ 1`

## Results

We measured the voltage noise by using a Keysight S-Series Oscilloscope. To measure the noise, we did a fast fourier transform on the signal and got the average noise floor in dBm. We took some data at "high frequency" and simulated a low-pass filter on the other to see how it compared against our currently used voltage source, the Yokogawa GS200. 

The ArduinoDAC outperformed the Yokogawa GS200 at both frequencies at **7% of the price.**
<img width="682" alt="Screen Shot 2019-08-12 at 3 18 52 PM" src="https://user-images.githubusercontent.com/33910853/62891737-8501e400-bd14-11e9-95f2-e9d5f99091fc.png">
The blue signal is the voltage coming from the DAC, and the green plot is a Fast Fourier Transform of it. We observed that it had a noise floor of -108.687 dB.

We compared this to using the SDP Board with the EVAL-AD5790 and the precision voltage source we currently use, the Yokogawa GS200. 
