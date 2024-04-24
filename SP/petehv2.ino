#include <Arduino.h>
#include <Servo.h>

Servo servo;

#define IR_RECEIVE_PIN 2
#define RAW_BUFFER_LENGTH 128
#define MARK_EXCESS_MICROS 20
#define RECORD_GAP_MICROS 5000

int offset = 15;

int pogon = 4;

#include <IRremote.hpp>

void setup() {
    Serial.begin(115200);
    IrReceiver.begin(IR_RECEIVE_PIN, false);
    servo.attach(3); 
    servo.write(90);
    pinMode(pogon,OUTPUT);
}

void loop() {
  if (!IrReceiver.decode()) return;

  IrReceiver.resume();

  if (IrReceiver.decodedIRData.protocol != 8) return;
  if (IrReceiver.decodedIRData.address != 0) return;

  Serial.println(IrReceiver.decodedIRData.command);


  int cmd = IrReceiver.decodedIRData.command; 
  if(cmd == 70){
    pogonNaprijed();   
  }

  if(cmd == 68){
    servo.write(120+offset);
    pogonNaprijed();
    servo.write(90);
  }
  if(cmd == 67){
    servo.write(60-offset);
    pogonNaprijed();
    servo.write(90);
  }

}

void pogonNaprijed(){
  digitalWrite(pogon,HIGH);
  delay(2000);
  digitalWrite(pogon,LOW);
}

