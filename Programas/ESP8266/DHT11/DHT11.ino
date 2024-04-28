#include <MQ135.h>
#include "DHT.h"
#include <SoftwareSerial.h> 
#include <ESP8266WiFi.h>
#include <Arduino.h>
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
    FirebaseJson content;

    h = dht.readHumidity();
    t = dht.readTemperature();

    int sensorHumedad = analogRead(sensorPin);
    float valorHumedad = ( 100.00 - ( (sensorHumedad/1023.00) * 100.00 ) );

    mostrarInfo((int) t, (int) h, valorHumedad);

    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
      sendDataPrevMillis = millis();
    }

    if(!isnan(t) && !isnan(h)){
      content.set("fields/Temperature/stringValue", String(t, 2));
      content.set("fields/Humidity/stringValue", String(h,2));

      /*if(Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw(), "Temperature") && Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw(), "Humidity")){
        Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
      }else{
        Serial.println(fbdo.errorReason());
      }*/

    }else{
      Serial.println("Failed to read DHT data");
    }


    if(!isnan(sensorHumedad)){
      content.set("fields/SoilMoisture/stringValue", String(valorHumedad, 2));

      /*if(Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw(), "SoilMoisture")){
        Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
      }else{
        Serial.println(fbdo.errorReason());
      }*/

    }else{
      Serial.println("Failed to read Soil Moisture Sensor data");
    }


    if (!Firebase.RTDB.setFloat(&fbdo, ruta + "/Temperature", t)){
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


    delay(1000);
  }

  void mostrarInfo(int temp, int hum, float valorHumedad){
      String strdht = String("H:")+String(h)+String(" %")+String(" T:")+String(t)+String(" C");
      String strvH = String(" SoilMoisture:")+String(valorHumedad)+String("%") ;

      String arduino = String(strdht)+String(strvH);
      Serial.println(arduino);

  }
