#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <MQUnifiedsensor.h>

#define DHTPIN A0
#define FLAMEPIN D6  // Flame sensor connected to D6 (digital pin)
#define MQ2PIN D5    // MQ2 sensor digital output (DOUT) connected to D5 (digital pin)
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "kingfaris";
const char* password = "jayajaya";
const char* serverURL = "http://127.0.0.1:5000";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  dht.begin();
  pinMode(MQ2PIN, INPUT);  // Set D5 (MQ2 DOUT) as input
  pinMode(FLAMEPIN, INPUT); // Setup flame sensor
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  int flame = digitalRead(FLAMEPIN);  // Read flame sensor
  int gas = digitalRead(MQ2PIN);     // Read gas detection status (digital HIGH/LOW)

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    begin(WiFiClient url);

    String jsonData = "{\"temperature\": " + String(temp) + 
                      ", \"humidity\": " + String(humidity) + 
                      ", \"flame\": " + String(flame) + 
                      ", \"gas_detected\": " + String(gas) + "}";

    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      Serial.println("Data sent successfully");
    } else {
      Serial.println("Error sending data");
    }
    http.end();
  }
  delay(5000); // Send data every 5 seconds
}
