# Cortex M4 Sensor Status Monitor

This is an ARM Cortex-M4 32b application that uses the [STM32F429 Discovery Kit](http://www.st.com/content/ccc/resource/technical/document/user_manual/6b/25/05/23/a9/45/4d/6a/DM00093903.pdf/files/DM00093903.pdf/jcr:content/translations/en.DM00093903.pdf) with an STM32F429ZITx core running at 180MHz implementing the following hardware functions:

 - PWM Control (for a simple computer fan control)
 - Modified I2C communication (for the interface with SHT15)
 - Normal I2C communication (for the embedded LCD touch-screen)


## Project Description

This projects implements the following functionalities:

 - Temperature sensor reading in real-time
 - Configurable temperature threshold indicator
 - Humidity sensor reading in real-time
 - Configurable humidity threshold indicator
 - Fan speed sensor in real-time
 - Configurable fan speed threshold indicator
 - Touch Screen LCD Display interface
 - Draggable threshold configurations

## Code Organization

 - All code is written in pure C.
 - The screens are divided in views.
 - Each view is a specific state in a state machine.
 - Alarms are globally-set threshold pairs that can be set in a specific view

## Modified I2C

Due to how the SHT15 Humidity and Temperature Sensor works, a manual I2C communication had to be built based on the timing diagramns specified in the [sht datasheet](http://www.farnell.com/datasheets/317085.pdf):

![Timing Diagram](https://i.imgur.com/zK0e3VD.png)

The connection was done in the following :

![SHT15 Pin Connection Schematic](https://hobbybotics.files.wordpress.com/2012/05/hobbybotics-sht1x-breakout-v1-0-schematic.png)

## Hardware

The STM32F429 Discovery board offers the following features:

 - 2 MB Flash Memory
 - 256 KB RAM
 - 2.4" LCD QVGA Touch screen

## Credits

I developed this project as a learning experiment for my Computer Engineering course with the help of my Prof. Dr. Juliano D'Ornelas Benfica in April, 2018