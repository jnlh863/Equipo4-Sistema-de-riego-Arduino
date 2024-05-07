#include "DHT.h"
#include <SoftwareSerial.h> 
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define DHTPIN 4
#define DHTTYPE DHT11 // DHT 11
#define WIFI_SSID "HOME-6C86"                                  
#define WIFI_PASSWORD "5B6A6240DE485087"  
#define API_KEY "AIzaSyBhGWjM2IEoMMO0l_OujUsBJPHfjKqCH90"
#define DATABASE_URL "https://sistema-de-riego-24fc2-default-rtdb.firebaseio.com/"
#define FIREBASE_PROJECT_ID "sistema-de-riego-24fc2"    

  FirebaseData fbdo;
  FirebaseAuth auth;
  FirebaseConfig config;

  unsigned long sendDataPrevMillis = 0;
  int count = 0;
  bool signupOK = false;           
  const int sensorPin = A0;         

  DHT dht(DHTPIN, DHTTYPE);

  float t;
  float h;
  String ruta = "ambientquality";

  void setup(){

    Serial.begin(115200);
    Serial1.begin(115200);
    Serial.println(F("Dtxx Text!!!"));
    dht.begin();
     if (isnan(h) || isnan(t)){                                   
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    } 
    
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");

    while (WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(300);
    }

    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    config.api_key = API_KEY;

    config.database_url = DATABASE_URL;

    if (Firebase.signUp(&config, &auth, "", "")){
      Serial.println("ok");
      signupOK = true;
    }else{
      Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }

    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
    
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

  }
  
  void loop(){

    String documentPath = "EspData/ambientquality";
    String documentPathT = "EspData/intervals";
    FirebaseJson content;

    h = dht.readHumidity();
    t = dht.readTemperature();
    String estado = "off";

    int sensorHumedad = analogRead(sensorPin);
    float valorHumedad = ( 100.00 - ( (sensorHumedad/1023.00) * 100.00 ) );

    if(valorHumedad<0){
      valorHumedad = 0;
    }

    if(t>=25 && h <=20){
      estado = "on";
    }

    if(valorHumedad<20){
      estado = "on";
    }

    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
      sendDataPrevMillis = millis();
    }

    if(!isnan(t) && !isnan(h)){
      content.set("fields/Temperature/stringValue", String(t, 2));
      content.set("fields/Humidity/stringValue", String(h,2));
      Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw(), "Temperature");
      Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw(), "Humidity");
    }else{
      Serial.println("Failed to read DHT data");
    }


    if(!isnan(sensorHumedad)){
      content.set("fields/SoilMoisture/stringValue", String(valorHumedad, 2));
      Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw(), "SoilMoisture");
    }else{
      Serial.println("Failed to read Soil Moisture Sensor data");
    }

    String path = "EspData/intervals";

    if(Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), "")){

      StaticJsonDocument<384> doc;

      DeserializationError error = deserializeJson(doc, fbdo.payload().c_str());

      if (!error) {
          const char* name = doc["name"]; 
          const int temp = doc["fields"]["interval"]["integerValue"];
          const bool interruptor = doc["fields"]["waterPlants"]["booleanValue"];
          mostrarInfo((int) t, h, valorHumedad, estado, temp, interruptor);
      }
    }

     
    if (Serial.available() > 0) { 
      String dataReceived = Serial.readStringUntil('\n');
      if(dataReceived.length() == 6){
        content.set("fields/waterPlants/booleanValue", false);
        Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPathT.c_str(), content.raw(), "waterPlants");
      }  
    }


    if (!Firebase.RTDB.setFloat(&fbdo, ruta + "/Temperature", (int) t)){
        Serial.println("Failed to Read from the Sensor");
        Serial.println("REASON: " + fbdo.errorReason());
    }

    if (!Firebase.RTDB.setFloat(&fbdo, ruta + "/Humidity", h)){
        Serial.println("Failed to Read from the Sensor");
        Serial.println("REASON: " + fbdo.errorReason());
    }

    if (!Firebase.RTDB.setFloat(&fbdo, ruta + "/SoilMoisture", valorHumedad)){
        Serial.println("Failed to Read from the Sensor");
        Serial.println("REASON: " + fbdo.errorReason());
    }

    delay(3000);
  }

  void mostrarInfo(int temp, float hum, float valorHumedad, String estado, int t, bool inter){
      String strdht = String("H:")+String(hum)+String("%")+String(" T:")+String(temp)+String(" C");
      String strvH = String(" SoilMoisture:")+String(valorHumedad)+String("%") ;
      String strEst = String(" State:")+estado;
      String strtemp = String(" Temp:") + String(t);
      String strinter = String(" B:") + String(inter);

      String arduino = String(strdht)+String(strvH)+strEst+String(strtemp)+String(strinter);
      Serial.println(arduino);

  }
