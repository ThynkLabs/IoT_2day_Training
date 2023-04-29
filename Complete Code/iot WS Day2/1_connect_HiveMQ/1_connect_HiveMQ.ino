#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Test";
const char* password = "Test1234";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

//Callback Function Here

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  client.setServer(mqtt_server, mqtt_port);
  //Set Callback
}

void loop() {
  if (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker"); 
      //Subscribe Code Here
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
      return;
    }
  }
  client.loop();
  client.publish("iot_workshop/bncoe/group/1", "Hello from ESP32");
  delay(100);
}