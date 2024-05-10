#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int potPin = 34;
const int led1Pin = 2;
const int led2Pin = 4;

int potValue = 0;


void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  SerialBT.begin("ESP32 Matanovic");
  Serial.begin(9600);
  Serial.print("BT Start");
}

void loop() {

    int noviPotValue = analogRead(potPin);
    if (abs(noviPotValue - potValue) > 3) {
      potValue = noviPotValue;
      SerialBT.print(4095 - potValue);
      SerialBT.write(0);
    }


  if (SerialBT.available()) {
    char command = SerialBT.read();
    switch (command) {
      case '1':
        digitalWrite(led1Pin, HIGH);
        break;
      case '2':
        digitalWrite(led2Pin, HIGH);
        break;
      case '3':
        digitalWrite(led1Pin, LOW);
        break;
      case '4':
        digitalWrite(led2Pin, LOW);
        break;
      default:
        Serial.print("Error, krivi input");
        break;
    }
  }
  delay(10);
}
