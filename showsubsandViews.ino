#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "AR~Yan";
const char* password = "00000000";
const char* url = "https://www.googleapis.com/youtube/v3/channels?part=statistics&id=UC03O7iCHrdm19HZHUxylVTQ&key=AIzaSyCKFSg6HbNMrzu0pdNK077gUSFzez_MkWQ";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Create an HTTPClient object
  HTTPClient http;

  // Send GET request to the URL
  http.begin(url);

  int httpCode = http.GET();

  if (httpCode > 0) {
    // Check if response is JSON
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Received JSON:\n");
      //Serial.println(payload);

    // Stream& input;

StaticJsonDocument<768> doc;

DeserializationError error = deserializeJson(doc, payload);

if (error) {
  Serial.print("deserializeJson() failed: ");
  Serial.println(error.c_str());
  return;
}

JsonObject items_0 = doc["items"][0];

JsonObject items_0_statistics = items_0["statistics"];
const char* viewCount = items_0_statistics["viewCount"]; // "203882"
const char* subscriberCount = items_0_statistics["subscriberCount"]; // "1080"

 Serial.println("YouTube Channel: TFK ");
 Serial.print("Total Views: ");
 Serial.println(viewCount);
 Serial.print("Total Subscriber: ");
 Serial.println(subscriberCount);

    } else {
      Serial.println("HTTP request failed");
    }
  } else {
    Serial.println("Connection failed");
  }

  // Close the HTTP connection
  http.end();

  delay(6000);  // delay
}
