#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);

void setup() {
  lcd.begin(16,2);
  Serial.begin(115200);
  while (!Serial) {
    ;
    }
  lcd.print("Equipo 4");
  delay(1000);
}

  String strdht;  
  String strmq;
  bool turno = true;

void loop() {
  if (Serial.available() > 0) { 
    String dataReceived = Serial.readStringUntil('\n'); 
    Serial.println("Datos recibidos desde Arduino:");
    Serial.println(dataReceived);


    int hIndex = dataReceived.indexOf("H:");
    int tIndex = dataReceived.indexOf(" T:");
    int mqIndex = dataReceived.indexOf("MQ:");
    int vIndex = dataReceived.indexOf(" V:");
    int ppmIndex = dataReceived.indexOf(" PPM:");

    String humedad = dataReceived.substring(hIndex + 2, tIndex);
    String temperatura = dataReceived.substring(tIndex + 3, mqIndex);
    String mq = dataReceived.substring(mqIndex + 3, vIndex);
    String v = dataReceived.substring(vIndex + 3, ppmIndex);
    String ppm = dataReceived.substring(ppmIndex + 6);

 
    lcd.clear(); 
    lcd.setCursor(0, 0); 
    if (turno) {
      lcd.print("Humedad:");
      lcd.print(humedad);
      lcd.setCursor(0, 1);
      lcd.print("Temp:");
      lcd.print(temperatura);
    } else {
      lcd.print("MQ:");
      lcd.print(mq);
      lcd.print(" V:");
      lcd.print(v); 
      lcd.setCursor(0, 1);
      lcd.print(" PPM:");
      lcd.print(ppm);
    }

    turno = !turno;

  }
}
