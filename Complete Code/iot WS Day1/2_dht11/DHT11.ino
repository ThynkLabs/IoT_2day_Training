#include<DHT.h>
#define DHTPIN 27       //GPIO pin connected to DHT11 data pin
#define DHTTYPE DHT11   //DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(115200);    //begin Serial Monitor
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();   //used to read Temprature
  float humidity = dht.readHumidity();         //used to read Humidity

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" \tHumidity: ");
  Serial.print(humidity);
  Serial.print("%");
  delay(2000);          // Delay of 2 Seconds
}
