# Smart Classroom Monitoring System

## Project Overview
A smart classroom monitoring system developed using ESP32 to monitor environmental conditions and automate classroom appliances.

## Hardware Components
- ESP32
- DHT22 Sensor
- PIR Motion Sensor
- LDR Sensor
- Relay Module
- DC Fan
- LED Light
- Breadboard and Jumper Wires

## Working Principle
- The fan turns ON when the temperature exceeds 35°C.
- The light turns ON when the LDR reading is greater than 1000 and the PIR sensor detects motion.
- Sensor readings and output status are displayed in the Arduino IDE Serial Monitor.

## Software Requirements
- Arduino IDE
- Embedded C/C++
- ESP32 Board Support Package
- DHT Sensor Library

## Source Code
The Arduino source code is available in `smart_classroom.ino`.
