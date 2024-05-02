#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int triggerPin = 3;
int echoPin = 2;

LiquidCrystal_I2C lcd(0x27,20,4); 

int tareTipka = 7;

double visinaCase; 


void setup() {

  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(tareTipka,INPUT_PULLUP);
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);

  visinaCase = readDistance();
}



void loop() {

  if(!digitalRead(tareTipka)){

    visinaCase = readDistance();

  }
  Serial.println(visinaCase);

  lcd.setCursor(0, 0);
  lcd.print(100-(trunc((readDistance()/visinaCase)*100)));
  lcd.print("%");
  
  lcd.setCursor(0,1);
  lcd.print(readDistance());

  delay(800); 
  lcd.clear();
  delay(50);
  
}

double readDistance() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  double distanceCM = (duration / 2.0) * 0.0343;
  return distanceCM;
}
