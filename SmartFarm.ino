#include "DHT.h"
#include <PubSubClient.h>

#define DHTPIN 4
#define LDRPIN 1
#define DHTTYPE DHT11

const char *ssid = "ป๋าฮอล";
const char *password = "Jkpun449944";
const char *mqttServer = "broker.emqx.io";
const int mqqtPort = 1883;

hw_timer_t * timer = NULL;

// void IRAM_ATTR timerISR() {
//   timerFlag = true;
// }

DHT dht(DHTPIN, DHTTYPE);
unsigned long previousMillis = 0;
const long interval = 6000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
  pinMode(LDRPIN, INPUT);
  Serial.println("Smart Farm Monitoring System");
  Serial.println("Initializing sensors...");
}

void loop() {
  // if (timerFlag) {
  //   timerFlag = false;
  // }
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    int light_intensity = analogRead(LDRPIN);
    if(isnan(humidity) || isnan(temperature) || isnan(light_intensity)) {
      Serial.println("Failed to read from DHT sensors!");
    } else {
      Serial.println("Humidity: ");
      Serial.println(humidity);
      Serial.println("Teperature: ");
      Serial.print(temperature);
      Serial.println("C");
    }
    Serial.println(light_intensity);
    if (light_intensity < 1500) {
      Serial.println("Status: Light Level is low.");
      Serial.println("Additional lighting may be required");
    } else {
      Serial.println("Status: Light level is sufficient for plant growht.");
    }
  }
}
