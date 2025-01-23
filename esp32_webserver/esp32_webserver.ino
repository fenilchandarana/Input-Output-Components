#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Fenil";
const char* password = "876543210";

AsyncWebServer server(80);

void setup() {
  Serial.begin(9600);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print the IP address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hello, world!");
  });

  // Start server
  server.begin();
}

void loop() {
  
}
