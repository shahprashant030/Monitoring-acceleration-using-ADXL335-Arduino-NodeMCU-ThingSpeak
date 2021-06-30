//Include Lib to send data to NodeMCU
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Initialise the adxl335 pin connected to arduino analog pins
const int x1pin = A1;
const int x2pin = A2;
const int x3pin = A3;
const int x4pin = A4;
const int x5pin = A5;
float x1, x2, x3, x4, x5;

SoftwareSerial s(5, 6);

void setup() {
  Serial.begin(9600);
  s.begin(9600);
}

void loop() {

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  //Read x_acceleration value from five adxl355 sensors
  x1 = analogRead(x1pin); delay(20);
  x2 = analogRead(x2pin); delay(20);
  x3 = analogRead(x3pin); delay(20);
  x4 = analogRead(x4pin); delay(20);
  x5 = analogRead(x5pin); delay(20);

  //Convert sensors values to the required values
  x1 = x1 - 322;  x1 = x1 / 9.8;
  x2 = x2 - 322;  x2 = x2 / 9.8;
  x3 = x3 - 322;  x3 = x3 / 9.8;
  x4 = x4 - 322;  x4 = x4 / 9.8;
  x5 = x5 - 322;  x5 = x5 / 9.8;
  
  //Assign collected data to JSON Object
  root["x1"] = x1;
  root["x2"] = x2;
  root["x3"] = x3;
  root["x4"] = x4;
  root["x5"] = x5;
  if (s.available() > 0)
  {
    root.printTo(s); //send data to Arduino
  }
}
