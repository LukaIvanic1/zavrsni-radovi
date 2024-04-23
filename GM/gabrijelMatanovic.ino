#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

const char* ssid = "Luka";
const char* password = "4 8 15 16 23 42";

const int ledPin1 = 2;
const int ledPin2 = 4;
const int potPin = 34;

int potValue = 0;
bool ledState1 = false;
bool ledState2 = false;

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  Serial.println("Connecting to WiFi...");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.println("Connected to WiFi");

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(potPin, INPUT);


  server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    String ledParam = request->arg("led");
    if (ledParam == "1") {
      ledState1 = !ledState1;
      digitalWrite(ledPin1, ledState1 ? HIGH : LOW);
    } else if (ledParam == "2") {
      ledState2 = !ledState2;
      digitalWrite(ledPin2, ledState2 ? HIGH : LOW);
    }
    request->send(200, "text/plain", "Toggle successful");
  });

  
  
  server.on("/potValue", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(potValue).c_str());
  });

  
  server.begin();
}

void loop() {
  delay(5);
  potValue = analogRead(potPin);
}
