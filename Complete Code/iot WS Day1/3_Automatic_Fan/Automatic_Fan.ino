#include <DHT.h>
#define DHTPIN 27
#define FAN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  pinMode(FAN, OUTPUT);
  Serial.begin(115200);
  dht.begin();
  if (humidity >= 35 && temperature >= 25) {
    digitalWrite(FAN, HIGH);
    delay(1000);
  } else {
    (humidity < 35 && temperature < 25);
    digitalWrite(FAN, LOW);
    delay(1000);
  }
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  pinMode(FAN, OUTPUT);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" \tHumidity: ");
  Serial.print(humidity);
  Serial.print("%");
  delay(2000);
}
