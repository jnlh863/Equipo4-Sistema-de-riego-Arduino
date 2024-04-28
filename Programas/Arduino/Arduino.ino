#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);
int bombaAgua = 8;

void setup() {
  lcd.begin(16,2);
  Serial.begin(115200);
  while (!Serial) {
    ;
    }
  lcd.print("Equipo 4");
  pinMode(bombaAgua, OUTPUT);
  delay(1000);
}

  bool turno = true;

void loop() {

  digitalWrite(bombaAgua, LOW);
  delay(8000);

  digitalWrite(bombaAgua, HIGH);
  delay(1000);

  if (Serial.available() > 0) { 

    String dataReceived = Serial.readStringUntil('\n'); 
    Serial.println("Datos recibidos desde Arduino:");
    Serial.println(dataReceived);

    int hIndex = dataReceived.indexOf("H:");
    int tIndex = dataReceived.indexOf(" T:");
    int vHIndex = dataReceived.indexOf(" SoilMoisture:");

    String humedad = dataReceived.substring(hIndex + 2, tIndex);
    String temperatura = dataReceived.substring(tIndex + 3, vHIndex);
    String sm = dataReceived.substring(vHIndex + 14);

 
    lcd.clear(); 
    lcd.setCursor(0, 0); 
    if (turno) {
      lcd.print("Humdty:");
      lcd.print(humedad);
      lcd.setCursor(0, 1);
      lcd.print("Temp:");
      lcd.print(temperatura);
    } else {
      lcd.print("Soil Moisture:");
      lcd.setCursor(0, 1);
      lcd.print(sm);
    }

    turno = !turno;

  }
}
