#include "DHT.h"
#include <SoftwareSerial.h> //instead of parenthesis () put angle bracket as YouTube description does not allow angle bracket 
#define DHTPIN 4

// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11

  DHT dht(DHTPIN, DHTTYPE);
  String str;

  void setup(){
    Serial.begin(115200);
    Serial1.begin(115200);
    dht.begin();
    delay(2000);
  }
  void loop(){
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    str = String("H=")+String(h)+String("%")+String("T=")+String(t)+String("C");
    Serial.println(str);
    delay(1000);
  }

