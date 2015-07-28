/*
  MQTT IOT Example - LinkIt One board to IBM Bluemix Connection quick start
 - continuously obtains values from the Virtuabotix DHT11 temperature/humidity sensor
 - formats the results as a JSON string for the IBM IOT example
 - connects to an MQTT server (either local or at the IBM IOT Cloud)
 - and publishes the JSON String to the topic named quickstart:MY_MAC_ADDRESS
 */



#include <SPI.h>


#include <LWiFi.h>
#include <LWiFiClient.h>
#include "DHT.h"

/* PubSubClient has been taken from https://github.com/knolleary/pubsubclient/tree/master/PubSubClient */
#include <PubSubClient.h>

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

/* Modification Needed : 
   Enter your WIFI Access Credentials. 
*/
#define WIFI_AP "your_ap_ssid"
#define WIFI_PASSWORD "your_password"
#define WIFI_AUTH LWIFI_WEP  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.



char macstr[] = "aabbccddeeff";  // Enter the device mac address here
// Note this next value is only used if you intend to test against a local MQTT server
byte localserver[] = {192,168,1,196};

char servername[] = "quickstart.messaging.internetofthings.ibmcloud.com";
String clientName = String("d:quickstart:arduino:") + macstr; 
String topicName = String("iot-2/evt/status/fmt/json");

float tempF = 0.0;
float tempC = 0.0;
float humidity = 0.0;

DHT dht(DHTPIN, DHTTYPE);
LWiFiClient wifiClient;
PubSubClient client(servername, 1883, 0, wifiClient);

// Uncomment this next line and comment out the line after it to test against a local MQTT server
//PubSubClient client(localserver, 1883, 0, ethClient);


void InitLWiFi()
{
  LWiFi.begin();
  // Keep retrying until connected to AP
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
  {
    delay(1000);
  }
  Serial.println("Connected to AP");
}

void setup()
{
   Serial.begin(9600);
   dht.begin();
   InitLWiFi();
}

void loop()
{
  IPAddress server(localserver);
  
  char deviceName[] = "Linkitone";
  char clientStr[34];
  clientName.toCharArray(clientStr,34);
  char topicStr[26];
  topicName.toCharArray(topicStr,26);
  
  
  getData();
  
 


  if (!client.connected()) {
    Serial.print("Trying to connect to: ");
    Serial.println(clientStr);
   
    Serial.println("Connecting to server "); 
    while (! client.connect(clientStr))
    {
      Serial.println("Re-Connecting to SERVER");
      delay(3000);
    }
   Serial.println("Connected to server");
    
  }
  
  if (client.connected() ) {
    
    Serial.println("Connected to server : Building jason");
    
    String json = buildJson();
    char jsonStr[200];
    json.toCharArray(jsonStr,200);
    Serial.println("Connected to server : publishing");
    boolean pubresult = client.publish(topicStr,jsonStr);
    Serial.print("attempt to send ");
    Serial.println(jsonStr);
    Serial.print("to ");
    Serial.println(topicStr);
    if (pubresult)
      Serial.println("successfully sent");
    else
      Serial.println("unsuccessfully sent");
  }
  delay(5000);
}

String buildJson() {
  String data = "{";
  data+="\n";
  data+= "\"d\": {";
  data+="\n";
  data+="\"myName\": \"LinkIt ONE DHT11\",";
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

void getData() {

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
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






