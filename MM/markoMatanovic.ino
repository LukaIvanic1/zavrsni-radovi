#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define pedeset 51


int triggerPin = 3;
int echoPin = 2;
LiquidCrystal_I2C lcd(0x27,20,4); 
int tareTipka = 7;


double visinaCase; //jedan je na pocetku da u slučaju pogreške ne dijelimo sa nulom (mislimo u naprijed)
//bool tipkaStisnuta = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(tareTipka,INPUT_PULLUP);
  Serial.begin(9600);
    lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  //lcd.setCursor(1,0)
  
  lcd.setCursor(0,0);
  visinaCase = readDistance();
}



void loop() {
  // put your main code here, to run repeatedly:
  // initialize the lcd
 /* if (!digitalRead(KITA)){
    tipkaStisnuta = true;
  }*/
  if(!digitalRead(tareTipka)){
    visinaCase = readDistance();
  }
  Serial.println(visinaCase);
  lcd.setCursor(0, 0);
  lcd.print(100-(trunc((readDistance()/visinaCase)*100)));
  lcd.print("%");
  //if(tipkaStisnuta && digitalRead(KITA)){
  lcd.setCursor(0,1);
  lcd.print(readDistance());
  delay(800); //koliko često se mjeri, svakih x ms
  
  lcd.clear();
  delay(pedeset);
  
  //} else {
  //  lcd.println("KITA");
  //}

  //Serial.write(readDistance());
  //Serial.write("\n");
}

double readDistance() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  double distanceCM = (duration / 2.0) * 0.0343;
  //double normalizedDistance = constrain(distanceCM / MAX_DISTANCE_CM, 0.0, 1.0);
  return distanceCM;
}