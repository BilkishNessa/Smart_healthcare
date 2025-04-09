#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";
const char* serverURL = "http://your-PC-IP:5000/update";  // Replace with Flask server IP

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.");
}

void loop() {
  int heartRate = random(65, 100);  // bpm
  int systolic = random(110, 130);  // mmHg
  int diastolic = random(70, 85);   // mmHg
  float temp = random(360, 375) / 10.0;  // °C

  String bloodPressure = String(systolic) + "/" + String(diastolic);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"heart_rate\":" + String(heartRate) +
                     ", \"blood_pressure\":\"" + bloodPressure +
                     "\", \"temperature\":" + String(temp) + "}";

    int response = http.POST(payload);
    Serial.println("Data sent: " + payload);
    Serial.println("Server response: " + String(response));
    http.end();
  }

  delay(10000);  // Send every 10 seconds
}
