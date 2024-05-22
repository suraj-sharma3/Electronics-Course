#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "OMOTECH_2.4GHz";
const char* password = "Omotech@23";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to the WiFi Network");

}

void loop() {
}
