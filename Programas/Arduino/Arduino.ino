#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);

void setup() {
  lcd.begin(16,2);
    // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }
  lcd.print("MOBY");
}

void loop() {
  if (Serial.available() > 0) { 
    String dataReceived = Serial.readStringUntil('\n'); 

    Serial.println("Datos recibidos desde Arduino:");
    Serial.println(dataReceived);

    // Imprime los datos en el LCD
    lcd.clear(); 
    lcd.setCursor(0, 0); 
    lcd.print(dataReceived.substring(0, 16)); 
    lcd.setCursor(0, 1); 
    lcd.print(dataReceived.substring(16));

  }
  /*if (Serial.available()) {
   Serial.write(Serial.read());
  }*/
}
