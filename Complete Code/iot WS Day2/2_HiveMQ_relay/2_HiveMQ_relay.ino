#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Test";
const char* password = "Test1234";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
#define Relay 4

//Callback Function Here
void callback(char* topic, byte* payload, unsigned int length) {
	 // Log incoming message and topic
  Serial.print("Topic:");
  Serial.println(topic);
  Serial.print("Message:");
  Serial.println((char*)payload);
  

  // Check if the message is 1
  if((char)payload[0] == '1'){
  // Set Esp32 pin 4 LOW
    digitalWrite(Relay, LOW);
  }
  else if((char)payload[0] == '0'){
  // Set Esp32 pin 4 HIGH
    digitalWrite(Relay, HIGH);
  }
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(Relay,OUTPUT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  client.setServer(mqtt_server, mqtt_port);
  //Set Callback
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("esp_thynk")) {
      Serial.println("Connected to MQTT broker"); 
      //Subscribe Code Here
      client.subscribe("iot_workshop/bncoe/group/1/relay");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
      return;
    }
  }
  client.loop();
  delay(100);
}