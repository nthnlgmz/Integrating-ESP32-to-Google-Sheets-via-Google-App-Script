#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "";         // Replace with your Wi-Fi SSID
const char* password = ""; // Replace with your Wi-Fi password

const char* scriptURL = "https://script.google.com/macros/s/ /exec"; // Replace with your Google Apps Script URL

const int buttonPin = 23;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    delay(200);
    sendPostRequest();
  }
  delay(100);
}

void sendPostRequest() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(scriptURL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Customize the payload if necessary
    String postData = "buttonState=pressed";

    int httpResponseCode = http.POST(postData);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response from server: " + response);
    } else {
      Serial.println("Error sending POST request");
    }
    http.end();
  } else {
    Serial.println("Wi-Fi not connected");
  }
}

