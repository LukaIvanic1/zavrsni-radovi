#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int ledPin = 2; 
const int potPin = 34; 
int potValue;

void setup() {
  SerialBT.begin("ESP32-BT"); 
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  
  potValue = analogRead(potPin);

  
  if (SerialBT.available()) {
    char cmd = SerialBT.read();
    if (cmd == '1') {
      digitalWrite(ledPin, HIGH);
    } else if (cmd == '0') {
      digitalWrite(ledPin, LOW);
    }
  }


  SerialBT.print(potValue);
  delay(100);
}
