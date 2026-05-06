#include "DHT.h"
#include <WiFi.h>
#include <PubSubClient.h>

#define DHTPIN 4
#define LDRPIN 1
#define DHTTYPE DHT11

const char *ssid = "WIFI_SSID";
const char *password = "PASSWORD";
const char *mqttServer = "broker.emqx.io";  
const int mqttPort = 1883;                   

DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long previousMillis = 0;
const long interval = 1000;

void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

void setup_wifi() {                          
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {       
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("SmartFarm")) {
      Serial.println("connected");
      client.subscribe("smartfarm/reconnect/test");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 1s...");
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(LDRPIN, INPUT);

  setup_wifi();                              
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  Serial.println("Smart Farm Monitoring System");
}

void loop() {
  if (!client.connected()) {
    reconnect();                            
  }
  client.loop();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float humidity    = dht.readHumidity();
    float temperature = dht.readTemperature();
    int light_intensity = analogRead(LDRPIN);

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    client.publish("smartfarm/humidity",    String(humidity).c_str());
    client.publish("smartfarm/temperature", String(temperature).c_str());
    client.publish("smartfarm/light",       String(light_intensity).c_str());

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("% | Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
    Serial.print("Light Intensity: ");
    Serial.println(light_intensity);

    if (light_intensity < 1500) {
      Serial.println("Status: Light Level is low.");
    } else {
      Serial.println("Status: Light level is sufficient.");
    }
    Serial.println("-----------------------");
  }
}