#include <Wire.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);
int bombaAgua = 8;


void setup() {
  lcd.begin(16,2);
  Serial.begin(115200);
  while (!Serial) {
    ;
    }
  lcd.print("    Equipo 4");
  pinMode(bombaAgua, OUTPUT);
}

  bool turno = true;

void loop() {

  if (Serial.available() > 0) { 

    String dataReceived = Serial.readStringUntil('\n'); 
    dataReceived.trim();
    int hIndex = dataReceived.indexOf("H:");
    int tIndex = dataReceived.indexOf(" T:");
    int vHIndex = dataReceived.indexOf(" SoilMoisture:");
    int estIndex = dataReceived.indexOf(" State:");
    int tempIndex = dataReceived.indexOf(" Temp:");
    int inteIndex = dataReceived.indexOf(" B:");

    String humedad = dataReceived.substring(hIndex + 2, tIndex);
    String temperatura = dataReceived.substring(tIndex + 3, vHIndex);
    String sm = dataReceived.substring(vHIndex + 14, estIndex);
    String est = dataReceived.substring(estIndex + 7, tempIndex);
    String temp = dataReceived.substring(tempIndex + 6, inteIndex);
    String inter = dataReceived.substring(inteIndex+3);
  

    Wire.setClock(10000);
    lcd.setCursor(0, 0); 
    if (turno) {
      lcd.print("   Hum: ");
      lcd.print(humedad);
      lcd.setCursor(0, 1);
      lcd.print("   Temp: ");
      lcd.print(temperatura);
    } else {
      lcd.print(" Soil Moisture:");
      lcd.setCursor(0, 1);
      lcd.print("    " + sm);
    }

    turno = !turno;

    if(inter == "1"){
      if(temp.toInt() != 0){  
        Wire.setClock(10000);
        lcd.begin(16, 2);
        lcd.print("   Regando... ");
        digitalWrite(bombaAgua, LOW);
        lcd.clear();
        delay(temp.toInt());
        
      }
    }else{
      digitalWrite(bombaAgua, HIGH);
    }

    

    if(est.length() == 2){
      Wire.setClock(10000);
      lcd.begin(16, 2);
      lcd.print("   Regando... ");
      digitalWrite(bombaAgua, LOW);
      lcd.clear();
      delay(5000);
    }else{
      digitalWrite(bombaAgua, HIGH);
    }

    String off = "false";
    Serial.println(off);
  }
  delay(1000);
}
