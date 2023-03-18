# Embedde-System
Wi-Fi Based Smart Home Automated System Using Thingspeak 
ABSTRACT
With the increasing cost of living, technology is being involved to lower the prices. Wi-Fi Based Smart Home Automated System allows us to minimize energy consumption providing more and more automated applications. Smart Home Automated System will give complete control over the environment whether the user is present at the site or away. Such kind of system works at its best in energy performance. By implementing this system different engineering challenges can be explored including software programming, Wi-Fi, TCP/IP protocols and web server designing etc.

TASK DESCRIPTION:

This is one of the most important Arduino based projects using nodemcu. In smart home automation system using nodemcu module, an html page is designed for controlling and accessing the controlled environment from anywhere over the internet. This page shows the current updated state of all the attached devices with in the system. In this home automated system we have used DHT11 sensor for measuring the current temperature and humidity values. Relays are being used to control light, fan and servo motor for door lock. Nodemcu module is connected with the Wi-Fi and with the help of port forwarding this module can be accessed easily from anywhere.  

In this task, data collected by the DHT11 sensor is sent privately to the cloud using thingspeak so that allows us to aggregate, visualize and analyze live data streams in cloud.

DESIGNING

 Hardware requirement:
1.	Nodemcu module
2.	Relay modules
3.	DHT11 sensor
4.	Light
5.	Fan
6.	Servo motor
7.	Power Supply
8.	Connecting wires
Software requirement:
1.	Arduino compiler
2.	Notepad++
3.	Thingspeak
HARDWARE DESCRIPTION
NodeMcu ESP8266

The term NodeMCU usually refers to the firmware, while the board is called Devkit. NodeMCU Devkit 1.0 consists of an ESP-12E on a board, which facilitates its use. It also has a voltage regulator, a USB interface. The ESP-12E is a board created by AI-THINKER, which consists of an ESP8266EX inside the metal cover. Made by Espressif, this microchip has integrated WiFi and low-power consumption.
NodeMcu pin configuration

Relay
Relay is the most commonly used switching device in electronics.
•	Trigger Voltage (Voltage across coil) : 5V DC
•	Trigger Current (Nominal current) : 70mA
•	Maximum AC load current: 10A @ 250/125V AC
•	Maximum DC load current: 10A @ 30/28V DC
•	Compact 5-pin configuration with plastic moulding
•	Operating time: 10msec Release time: 5msec
•	Maximum switching: 300 operating/minute (mechanically)

Before we proceed with the circuit to drive the relay we have to consider two important parameters of the relay. Once is the Trigger Voltage, this is the voltage required to turn on the relay that is to change the contact from Common->NC to Common->NO. Our relay here has 5V trigger voltage.. The other parameter is Load Voltage & Current, this is the amount of voltage or current that the NC, NO or Common terminal of the relay could withstand, in our case for DC it is maximum of 30V and 10A. 
The above circuit shows a bare-minimum concept for a relay to operate. Since the relay has 5V trigger voltage we have used a +5V DC supply to one end of the coil and the other end to ground through a switch. This switch can be anything from a small transistor to a microcontroller or a microprocessor which can perform switching operation. We can also notice a diode connected across the coil of the relay, this diode is called the Fly back Diode. The purpose of the diode is to protect the switch from high voltage spike that can produced by the relay coil. As shown one end of the load can be connected to the Common pin and the other end is either connected to NO or NC. If connected to NO the load remains disconnected before trigger and if connected to NC the load remains connected before trigger.
DHT11 sensor

DHT11 is a sensor which measures temperature as well as humidity from the surrounding environment. There are two sensors DHT11 and DHT22, are low cost and provide greater performance. The DHT11 temperature range is from 0 to 50 degrees Celsius with +-2 degrees accuracy while the humidity range is from 20 to 80% with 5% accuracy. There are two specifications where the DHT11 is better than the DHT22. That’s the sampling rate which for the DHT11 is 1Hz or one reading every second, while the DHT22 sampling rate is 0.5Hz or one reading every two seconds and also the DHT11 has smaller body size. The operating voltage of both sensors is from 3 to 5 volts, while the max current used when measuring is 2.5mA.

DHT11 sensor
Servo Motor

A servomotor is a rotatory actuator or linear actuator that allows for precise control of angular or linear position, velocity and acceleration. Used as a door lock here.

Memory of Arduino: 32k

Frequency of pin: 495~=500HZ

T=1/500=2ms

Fake analog signal can be generated by using pwm as Arduino has not any analog output

Motors operate at 50Hz frequency, T=1/50=20 msec.
We will convert 2ms to 20msec using pwm

Servo motor angles:

180 degree: 18msec off, 2msec on

0 degree: 19msec off, 1 msec on

90 degree: 18.5msec off, 1.5msec on   

Power Supply

A power supply is an electrical device that supplies electric power to an electrical load.
Connecting Wires

Connecting wires allows an electrical current to travel from one point on a circuit to another because electricity needs a medium through which it can move.

SOFTWARE DESCRIPTION

THINGSPEAK:

Thingspeak is an IoT platform that allows us to aggregate, visualize and analyze data by sending it privately to the cloud and provide instant visualizations of the data collected by our devices or sensors attached.

Thingspeak provides us:

•	Easy configuration of devices for sending collected data to Thingspeak

•	Visualization of data as received

•	Use of MATLAB to generate graphs of the collected data for better understanding

Basic steps are collection and analyzation of data collected by the sensors and devices. In our case, we are using DHT11 sensor for measuring temperature and humidity from the surrounding environment. By configuring sensor to Thingspeak and creating a private channel, data collected by the sensor will automatically get stored to the cloud and we will be able to visualize the collected data in real time. Data will be analyzed with the graphs created at real time.
