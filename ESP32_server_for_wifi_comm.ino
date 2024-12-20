/* #include <WiFi.h>

const char* ssid = "OMOTECH_2.4GHz";
const char* password = "Omotech@23";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.print("Received request: ");
        Serial.println(request);
        
        client.flush();

        // Send the response to the client
        String response = "Hello from ESP32 server!";
        client.print(response);
        Serial.print("Sent response: ");
        Serial.println(response);
        break;
      }
    }
    
    delay(10);
    client.stop();
    Serial.println("Client disconnected");
  }
}
 */


 #include <WiFi.h>

const char* ssid = "OMOTECH_2.4GHz";
const char* password = "Omotech@23";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        String message = client.readStringUntil('\n');
        Serial.print("Received message: ");
        Serial.println(message);

        // Echo the message back to the client
        client.print("Server received: ");
        client.println(message);
        Serial.print("Sent response: Server received: ");
        Serial.println(message);
      }
    }
    
    delay(10);
    client.stop();
    Serial.println("Client disconnected");
  }
}
