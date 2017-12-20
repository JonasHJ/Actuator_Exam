# Actuator_Exam

This program utilises master-slave communication (I2C). 
It uses two Arduino Unos, one being the slave, the other being the master.

The slave:
Reads from an Ultrasonic Sensor (HC-SR04) to calculate distances.
At a request from the master it splits the distance into two bytes, and returns them.

The master:
Establishes the master-slave relationship and continually requests two bytes from the slave.
While a button is pressed, it converts the distance to inches instead of centimeters.
It outputs the inches or centimeters to a LiquidCrystal Display.

A picture of the hardware setup can be seen in the file: "hardware_setup.png".
