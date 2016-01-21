# weather-box
A TI SensorTag-based weather station with automatic Bluetooth advertising.

ReadMe.md

#Weather Box

High expectations and enthusiasm for easy Internet of Things (IoT) Cloud-based projects based on the Texas Instruments (TI) CC2650 SensorTag (aka SensorTag 2.0) quickly dissipated into a ho-hum “nice idea, but …” afterthought. Why? It’s tough to wrangle the Bluetooth “smart” connectivity into a simple, practical project. Here’s the problem: SensorTag attempts to establish a link with a Bluetooth Low Energy compliant device by advertising its device ID for approximately 2 minutes. This advertising period is initiated by a user pressing a button located on SensorTag. This direct user physical contact handicaps installing SensorTag in a remote or inaccessible area. Unfortunately, one of the primary use applications for SensorTag is in a remote sensor node weather station configuration.

One of the more common solutions to this irritating limitation is to modify the SensorTag firmware for continuous Bluetooth advertising. In other words, removing the 2 minute operation limit on the SensorTag and thereby enabling it to keep its CC2650 Bluetooth “Smart” microcontroller unit (MCU) ON all of the time. See this discussion about this process:

“How to modify the TI SensorTag (CC2650STK) Firmware to advertise indefinitely?
(stackoverflow.com/questions/30076938/how-to-modify-the-ti-sensortag-cc2650stk-firmware-to-advertise-indefinitely)

This solution seems to preclude one of SensorTag’s greatest attributes: low-power consumption; or, “… lets the device operate on small coin cell batteries and in energy-harvesting applications.”

—see TIDU862-March 2015

This project presents an entirely different way of looking at SensorTag and enabling it to be easily slipped into any remote installation application. Here’s the TL;DR version:

Connect a relay to SensorTag and trip it at predefined intervals.

#Background

Texas Instruments has managed to pack an impressive array of sensors and features into a ridiculously small battery-powered package. Included with SensorTag are:

Accelerometer
Ambient light sensor
Ambient temperature sensor
Barometric pressure sensor
Bluetooth Smart CC2650 MCU
Buzzer
CR2032 battery operation
Gyroscope
Humidity sensor
Infrared temperature sensor
Green LED
Red LED
Magnetic (Reed-like) sensor
Magnetometer
Microphone

In addition to its small physical size, SensorTag is also small in its price sticker with a MSRP of $30.

Remarkably, a complete sensor node weather station can be built with SensorTag plus a couple of low-cost parts. This project is the Weather Box.

Weather Box consists of a 3D-printed enclosure that houses SensorTag, an external MCU, battery, and relay. This relay is used for “flicking” the SensorTag advertising switch. The timing for this relay operation is performed by the external MCU. During inactivity, the MCU is placed into a “deep sleep” mode so that battery life can be preserved. In fact, the expected battery life for Weather Box is about 100+ days. This longevity is exclusive of the SensorTag battery; although TI claims a similar long operational life for its Bluetooth device.

Once a Bluetooth link has been established with Weather Box, reading the sensor node can be accomplished with the TI SensorTag app (FREE). This app provides a barebones utilitarian view of all sensor data. Furthermore, this data can be sent to an IBM Cloud service for interaction by mobile devices. For example, Weather Box data could be received via messaging texts that are distributed with IoT scripts and recipes.

Another method of using Weather Box data is with a paid app called MyWeatherCenter (by Flaschengeist Studios; myweathercenter.net). Unlike the TI app, this app provides an integrated weather view that combines local SensorTag data with national/international weather forecasts.

#The Build

You can either build this project freeform (this can be challenging) or use this kit (this is the easiest way to get going):

SparkFun H2OhNo! ATtiny Dev Board/Water Alarm DEV-12069
(https://www.sparkfun.com/products/12069)

Either way, the parts required are:

Atmel AVR ATtiny85
20mm Coin cell battery holder
CR2032 Coin cell battery
Switch (or, 2-pin Header with jumper shunt)
Jumper wire
[You don’t have to use/solder the remaining parts from this kit.]

And this part:

IXYS LCA710 Single Pole, Normally Open OptMOS Relay
from BGMicro #REL1133 (bgmicro.com).

And, naturally, this part, too:

TI SensorTag CC2650 2.0

Assembling instructions for the kit are here:

H2OhNo! Tutorial
(https://learn.sparkfun.com/tutorials/h2ohno)

There are several ways to program the ATtiny85, the easiest method is to use this AVR programmer:

Tiny AVR Programmer SparkFun PGM-11801
(https://www.sparkfun.com/products/11801)

Finally, setting up the Arduino Integrated Development Environment (IDE) for programming the ATtiny85, can be found here:

Tiny AVR Programmer Hookup Guide
(https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide/)

After all of these choices and steps have been completed, follow these steps for assembling Weather Box:

Step 1. Remove the SensorTag container from its red rubber jacket (NB: that’s TI nomenclature, not mine), lift the clear lid off the container, and remove the battery. Set these pieces aside for reassembly in a later step.

Step 2. Locate and remove switch SW1 (ON/OFF). This is a Diptronics MTA2-WNC-V-T/R switch. In order to understand the layout of this component, read the datasheet for this switch before you remove it.

Step 3. Use a multimeter to determine which of the switch’s pads is connected to GND (i.e., a continuity test between the negative battery terminal (Bat-) and each pad). Use a black wire (or, blue wire) for soldering to this pad in the next step.

Step 4. Solder a single wire to each of the switch’s contact pads, tape these wires to the SensorTag PCB, route the wires outside of the container and through a slit in the red rubber jacket, reinstall the battery, and reassemble the parts that you set aside in Step 1. Test your modification by touching the two wires together: the SensorTag green LED should begin flashing and the Bluetooth MCU should begin advertising.

Step 5. Snip off and discard pin #3 on the IXYS relay. Solder pins #4 and #6 together on the relay. Connect these joint combined pins to the red wire (or, non-GND wire) from SensorTag as determined in Step 4 and the black or blue wire from SensorTag (from Step 3) to the relay’s pin #5.

Step 6. Solder a wire from pin #1 of the relay to pin #5 of the ATtiny85 (or, the appropriate pad for this pin on the H2OhNo! PCB) and another wire from pin #2 of the relay to the GND pin of the ATtiny85 (i.e., pin #4).

Step 7. Connect a battery to the ATtiny85 or insert a battery into the H2OhNo! PCB and slide the power switch to ON. Every five (5) minutes the ATtiny85 will wake up and trigger the relay. This triggering action will activate the SensorTag Bluetooth advertising system. The Bluetooth advertising lasts approximately two (2) minutes. During this advertising period, use your smartphone to locate Weather Box with the FREE TI SensorTag app.

You should be able to see the SensorTag green LED flashing through the slats on the back of the red rubber jacket. If you don’t immediately see SensorTag in the app, ensure that your mobile device has its Bluetooth service active and try to reconnect to Weather Box after several minutes. There is a two-minute window for pairing a device with Weather Box every five minutes, or, about three (3) minutes of SensorTag inactivity.

#Installation

There are two STL format files for printing an enclosure for Weather Box. This enclosure has a sliding door, as well as an opening shaped like a sun on one side. Slide SensorTag, ATtiny85, battery, and relay into the enclosure. For proper weather reading, ensure that the SensorTag red rubber jacket slats are facing the sun pictographic opening on the side of the enclosure.

Find a suitable location outside for installing Weather Box. Avoid areas with direct sunlight and those that can get wet from precipitation. Use the small handle on the top of 3D-printed enclosure for hanging Weather Box. This installation will allow you to use accelerometer data for measuring wind speed.

Your Weather Box is now ready for use.

Files for Weather Box:

Pix = Photographs of Weather Box.

STLFiles = the 3D STL format files for printing the Weather Box enclosure: https://github.com/How2-Oh/weather-box/files/99459/STLFiles.zip

Code = the Arduino IDE INO code for programming the ATtiny85

Readme.md = this file
