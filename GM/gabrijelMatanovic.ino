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

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(potPin, INPUT);

  // Define server routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><head><script>";
    html += "setInterval(function() {";
    html += "fetch('/potValue')";
    html += ".then(response => response.text())";
    html += ".then(data => document.getElementById('potValue').innerText = 'Potentiometer Value: ' + data);";
    html += "}, 100);</script></head><body>";
    html += "<h1>ESP32 Web Server</h1>";
    html += "<p id='potValue'>Potentiometer Value: " + String(potValue) + "</p>";
    html += "<button onclick=\"toggleLED(1)\">Toggle LED 1</button>";
    html += "<button onclick=\"toggleLED(2)\">Toggle LED 2</button>";
    html += "<script>function toggleLED(led) { fetch('/toggle?led=' + led); }</script>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

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

  // Start server
  server.begin();
}

void loop() {
  // Read potentiometer value every 50ms
  delay(5);
  potValue = analogRead(potPin);
}
