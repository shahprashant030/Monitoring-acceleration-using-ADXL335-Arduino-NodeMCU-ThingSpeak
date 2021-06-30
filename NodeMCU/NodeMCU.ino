//Include library to receive data from Arduino
#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>

//Include library to send data to ThingSpeak
#include <ESP8266WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h"

//WiFi network initialization
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

//ThingSpeak channel initialization
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our sensor values
float x1;
float x2;
float x3;
float x4;
float x5;
String myStatus = "We are getting the value";

 
void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  s.begin(9600);
  //while (!Serial) continue;
  
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
 
}
 
void loop() {
 StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return;
 
  Serial.println("JSON received and parsed");
  //root.prettyPrintTo(Serial); //print data comming from arudino

  //Data needed for us to send the data to thingspeak
  Serial.println("");
  Serial.print("X1:\t");    x1=root["x1"];    /*x1=limit_15(x1);*/  Serial.println(x1);
  Serial.print("X2:\t");    x2=root["x2"];    /*x2=limit_15(x2);*/  Serial.println(x2);
  Serial.print("X3:\t");    x3=root["x3"];    /*x3=limit_15(x3);*/  Serial.println(x3);
  Serial.print("X4:\t");    x4=root["x4"];    /*x4=limit_15(x4);*/  Serial.println(x4);
  Serial.print("X5:\t");    x5=root["x5"];    /*x5=limit_15(x5);*/  Serial.println(x5);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
  
  connect();
  
  // set the fields with the values
  ThingSpeak.setField(1, x1);
  ThingSpeak.setField(2, x2);
  ThingSpeak.setField(3, x3);
  ThingSpeak.setField(4, x4);
  ThingSpeak.setField(5, x5);
  
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(1000);
}

void connect(){
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
}
/*
float limit_15(float x){
if (x>(+15.0)||x<(-15)){
x = 0.0/0.0;
}
return x;
}
*/
