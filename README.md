#LinkIt ONE WiFi to IBM Bluemix Connection Sample

This repository contains the quickstart and registered device sample, and contains samples for connecting LinkIt ONE devices to the IBM Internet of Things Foundation
The events that are emitted in this sample are:
  •	Internal sensor temperature & humidity
  
#Pre-requisite setup for the 2 flows

  1.	Connect LinkIt ONE board to the work station ( laptop /desktop )
  2.	Install sketch on desktop / laptop
  3.	Download knolleary client library for the Arduino, from this link
   https://github.com/knolleary/pubsubclient  
  In the sketch, to load it into the Arduino IDE, Select Sketch -> Import Library -> Add Library and select the folder which contains PubSubClient.cpp and PubSubClient.h files.
  4.	Connect the USB cable to the LinkIt ONE and other end to desktop / laptop which has the sketch installed on it
  5.	Connect temperature and humidity sensor to the LinkIt ONE board. The sample code assume that the sensor has been connected to the D2 PIN of the LinkIt ONE board.
  6.	The samples folder of this repository (https://github.com/iotgeek/LinkItONE-IBMBluemix/) contains 2 examples, 
  a) Quickstart flow –quickstart.ino 
  b) Registered flow – registereduser.ino
  7.	Compile the 2 sketch codes (corresponding to the flows)
  8.	Depending upon the requirement, push one of the flows to the  LinkIt ONE board
  
#Quickstart flow

  1.	Modify the WIFI_AP, WIFI_PASSWORD & WIFI_AUTH values to your Wifi AP name, password and security type .
  2.	Modify the macstr  with the MAC Address of the LinkIt ONE, compile and upload to the LinkIt ONE board. Now the device should be ready to send temperature and humidity data to the IBM Bluemix cloud.
  3.	Open the quickstart dashboard from browser (http://quickstart.internetofthings.ibmcloud.com/#/)
  4.	Provide the MAC Address (in case of the example, its “aabbccddeeff”) in the textbox "Ready to View data?"
  5.	You can see the graph with temperature and humidity details.


#Registered Flow

  1.	Modify the WIFI_AP, WIFI_PASSWORD & WIFI_AUTH values to your Wifi AP name, password and type of encryption.
  2.	Modify the servername , clientName  and password  in the sketch code
  3.	Modify the macstr  with the MAC Address of the device, compile and upload to the LinkIt ONE board
  4.	Modify the servername, in the sketch code, by providing the values in the following format "666666.messaging.internetofthings.ibmcloud.com", by replacing "666666" with your organization
  5.	Modify the clientName  , in the sketch code, by providing the values in the following format "d:666666: LinkItONE: aabbccddeeff ", by replacing " aabbccddeeff " with the MAC Address , "666666" with the organization and LinkItONE by device type.
  
#Development
  •	The code contains comments, which explains how to modify the parameters  
  •	In case of registered flow, you will have to connect to https://internetofthings.ibmcloud.com/dashboard/#/ and create the     following  
      •	Organization  
      •	Device  
      •	Auth tokens  




