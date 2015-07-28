/*
   MQTT IOT Example : LinkIt ONE board to IBM Bluemix registered user account
 - continuously obtains values from the Virtuabotix DHT11 temperature/humidity sensor
 - formats the results as a JSON string for the IBM IOT example
 - connects to an MQTT server (either local or at the IBM IOT Cloud)
 - and publishes the JSON String to the topic named quickstart:MY_MAC_ADDRESS
 */

#include <SPI.h>
#include <LWiFi.h>
#include <LWiFiClient.h>

/* PubSubClient has been taken from https://github.com/knolleary/pubsubclient/tree/master/PubSubClient */
#include <PubSubClient.h>

#include "DHT.h"

/*  The PIN number to which the temperature sensor has been connected to. 
    Make sure that you have connected the temperature sensor to the D2 pin of Grove Shield/ D2 of LinkIt ONE Board.
*/
#define DHTPIN 2    
#define DHTTYPE DHT22 

/* MOdification Needed : 
   Enter your WIFI Access Credentials. 
*/
#define WIFI_AP "your_ap_ssid"
#define WIFI_PASSWORD "your_password"
#define WIFI_AUTH LWIFI_WEP  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.


/* Please modify this part
   Enter your IBM Bluemix details here.
*/
char servername[] = "666666.messaging.internetofthings.ibmcloud.com";  // Enter Org Id here. 666666 is the dummy irg Id here
char clientName[] = "d:666666:LinkItONE:aabbccddeeff" ;  // Enter Org Id (666666), Device Type(LinkItONE) & Device Mac address (aabbccddeeff)  Format is : d:orgId:DeviceType:DeviceId
char password[]  ="abcdefghij^%&@%#"; // your password for the device you created in Bluemix

char topicName[] = "iot-2/evt/status/fmt/json"; // No Change needed here.
char username[]  ="use-token-auth"; // No Change needed here.

/* If you are using mosquitto set up to test MQTT locally, you enter your local IP address here.*/
char localserver[] = "192.168.1.196";


float tempF = 0.0;
float tempC = 0.0;
float humidity = 0.0;

unsigned long time = 0;

   
DHT dht(DHTPIN, DHTTYPE);
LWiFiClient wifiClient;

// Uncomment this next line and comment out the line after it to test against a local MQTT  
//PubSubClient client(localserver, 1883, 0, wifiClient);

PubSubClient client(servername, 1883, 0, wifiClient);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  /* Initialise and connect to WIFI access point */   
  InitLWiFi();

}

void loop()
{
  
  getData();
  
  if (!client.connected()) {
    Serial.print("Trying to connect to: ");
    Serial.println(clientName);
    client.connect(clientName,username,password);
  }
  delay(2000);
  if (client.connected() ) {
    
    Serial.println("Connected !!: ");
    String json = buildJson();
    char jsonStr[200];
    json.toCharArray(jsonStr,200);
    Serial.println("publishing... !!: ");
    boolean pubresult = client.publish(topicName,jsonStr);
    Serial.print("attempt to send ");
    Serial.println(jsonStr);
    Serial.print("to ");
    Serial.println(topicName);
    if (pubresult)
      Serial.println("successfully sent");
    else
      Serial.println("unsuccessfully sent");
  }
  else 
    Serial.println("NOT Connected !!: connect FAILED ");
  
  /* Wait for some more time */
  delay(120000);
}

/* Build the jason content with temperature and humidity values */
String buildJson() {
  String data = "{";
  data+="\n";
  data+= "\"d\": {";
  data+="\n";
  data+="\"myName\": \"LinkIt ONE\",";
  data+="\n";
  data+="\"temperature (F)\": ";
  data+=(int)tempF;
  data+= ",";
  data+="\n";
  data+="\"temperature (C)\": ";
  data+=(int)tempC;
  data+= ",";
  data+="\n";
  data+="\"humidity\": ";
  data+=(int)humidity;
  data+="\n";
  data+="}";
  data+="\n";
  data+="}";
  return data;
}

void getData() 
{
    /* Get temperature and humidity values from the connected sensor */
    if(dht.readHT(&tempC, &humidity))
    {
        Serial.println("------------------------------");
        Serial.print("temperature = ");
        Serial.println(tempC);
        tempF = (tempC * 2 ) + 30;
        
        Serial.print("humidity = ");
        Serial.println(humidity);
    }
    
    delay(2000);
  
}

/* Initialise LinkIt ONE Wifi Module and connect to Wifi AP */
void InitLWiFi()
{
  LWiFi.begin();
  

  // keep retrying until connected to AP
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
  {
    delay(1000);
  }
  Serial.println("Connected to AP");
}



