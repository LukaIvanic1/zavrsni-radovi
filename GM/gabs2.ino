#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int potPin = 34;
const int led1Pin = 2;
const int led2Pin = 4;

int potValue = 0;
bool led1State = false;
bool led2State = false;

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  SerialBT.begin("ESP32");
  Serial.begin(9600);
  Serial.print("BT Start");
}

void loop() {
  int noviPotValue = analogRead(potPin);
  if (abs(noviPotValue - potValue) > 25) {
    potValue = noviPotValue;
    SerialBT.print(potValue);
    SerialBT.write(0); //šalje se 0 zbog razloga 
  }



  Serial.print(potValue);

  if (SerialBT.available()) {
    char command = SerialBT.read();
    if (command == '1') {
      led1State = !led1State;  // Toggle LED1 
      digitalWrite(led1Pin, led1State ? HIGH : LOW);
    } else if (command == '2') {
      led2State = !led2State;  // Toggle LED2 
      digitalWrite(led2Pin, led2State ? HIGH : LOW);
    }
  }
  delay(10);
}
