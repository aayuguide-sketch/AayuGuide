#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASS";

// SERVER URL (paste your Cloud Shell link)
String serverURL = "http://YOUR_SERVER_URL/ask";

// UART Display
HardwareSerial DisplaySerial(2);

#define TXD2 17
#define RXD2 16

void setup() {
  Serial.begin(115200);
  DisplaySerial.begin(9600, SERIAL_8N1, RXD2, TXD2);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");

  sendToDisplay("Welcome to AayuGuide");
}

void loop() {

  if (Serial.available()) {

    String input = Serial.readStringUntil('\n');

    String response = askServer(input);

    sendToDisplay(response);
    speak(response);
  }
}

// 🌐 SERVER CALL
String askServer(String symptom) {
  HTTPClient http;

  String url = serverURL + "?age=20&symptom=" + symptom + "&lang=English";

  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();

    DynamicJsonDocument doc(4096);
    deserializeJson(doc, payload);

    return doc["response"];
  }

  return "Server Error";
}

// 📺 DISPLAY
void sendToDisplay(String msg) {
  DisplaySerial.println(msg);
}

// 🔊 SPEAKER (basic)
void speak(String text) {
  Serial.println("Speaking: " + text);
}
