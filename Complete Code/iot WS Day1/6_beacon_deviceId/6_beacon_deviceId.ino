#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#define GROUP 1
#define DHTPIN 4       //DHT11 data pin
#define DHTTYPE DHT11  //DHT11 Sensor type

const char* ssid = "JAYSH";           //your wifi ssid
const char* password = "1111111111";  //your wifi password
const char* serverUrl = "http://api.thynklabs.in:5000/sensor-data";

DHT dht(DHTPIN, DHTTYPE);
HTTPClient http;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connecting to WiFi...");
  //Connect to Wifi newtork
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("WiFi connected.");
}

void loop() {
  float temperature = 27;
  float humidity = 37;

  String data = "{";
  data += "\"deviceId\":";
  data += String("group1_beacon");
  data += ",";
  data += "\"group\":";
  data += String(GROUP);
  data += ",";
  data += "\"humidity\":";
  data += String(humidity);
  data += ",";
  data += "\"temperature\":";
  data += String(temperature);
  data += "}"; 
  
  // To initialize http and make a POST request to the server.
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(data);
  //Check for error
  if (httpResponseCode > 0) {
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("HTTP POST request failed, error: ");
    Serial.println(http.errorToString(httpResponseCode).c_str());
  }
  http.end();  // Close HTTP connection
  delay(5000);
}

