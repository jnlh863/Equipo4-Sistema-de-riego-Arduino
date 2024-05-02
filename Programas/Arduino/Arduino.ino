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
  delay(1000);
}

  bool turno = true;

void loop() {

  if (Serial.available() > 0) { 

    String dataReceived = Serial.readStringUntil('\n'); 
    Serial.println("Datos recibidos desde Arduino:");
    Serial.println(dataReceived);
    
    int hIndex = dataReceived.indexOf("H:");
    int tIndex = dataReceived.indexOf(" T:");
    int vHIndex = dataReceived.indexOf(" SoilMoisture:");
    int estIndex = dataReceived.indexOf(" State:");

    String humedad = dataReceived.substring(hIndex + 2, tIndex);
    String temperatura = dataReceived.substring(tIndex + 3, vHIndex);
    String sm = dataReceived.substring(vHIndex + 14, estIndex);
    String est = dataReceived.substring(estIndex + 7);

    Serial.println(est);
    
    lcd.clear(); 
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

    if(est.length() == 3){
      digitalWrite(bombaAgua, LOW);
      delay(5000);
    }else{
      digitalWrite(bombaAgua, HIGH);
    }


  }
}
