// Receiving IR codes: https://github.com/Arduino-IRremote/Arduino-IRremote?tab=readme-ov-file#receiving-ir-codes
// Compile options / macros for this library: https://github.com/Arduino-IRremote/Arduino-IRremote?tab=readme-ov-file#compile-options--macros-for-this-library

#include <Arduino.h>
#include <Servo.h>

Servo servo;

#define IR_RECEIVE_PIN 2
#define RAW_BUFFER_LENGTH 128
#define MARK_EXCESS_MICROS 20
#define RECORD_GAP_MICROS 5000
//#define DEBUG
int offset = 15;

#include <IRremote.hpp>

void setup() {
    Serial.begin(115200);
    IrReceiver.begin(IR_RECEIVE_PIN, false);
    servo.attach(3); 
    servo.write(90);
}

void loop() {
  if (!IrReceiver.decode()) return;
  IrReceiver.resume();
  //IrReceiver.printIRResultShort(&Serial);

  if (IrReceiver.decodedIRData.protocol != 8) return;
  if (IrReceiver.decodedIRData.address != 0) return;

  Serial.println(IrReceiver.decodedIRData.command);

  if(IrReceiver.decodedIRData.command == 70){
    //motor dela
  }

  if(IrReceiver.decodedIRData.command == 68){
    servo.write(120+offset);
  }
  if(IrReceiver.decodedIRData.command == 67){
    servo.write(60-offset);
  }

}
