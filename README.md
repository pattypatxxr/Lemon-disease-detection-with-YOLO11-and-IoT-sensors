# Lemon-disease-detection-with-YOLO11-and-IoT-sensors

## Features
 
-  **Real-time Environmental Monitoring** — Temperature, humidity, and light intensity via DHT11 & LDR sensors
-  **MQTT Data Transmission** — Sensor data published to topics over Wi-Fi using ESP32-C6
-  **AI/ML Plant Disease Classification** — YOLO11n-cls model trained on 9 lemon leaf disease classes (93.4% top-1 accuracy)
  
### Hardware Components
- **MCU:** ESP32-C6
- **Sensors:** DHT11 (temperature & humidity), LDR (light intensity), Webcam (AI inference)

##  AI / ML Component
 
- **Model:** YOLO11n-cls (47 layers, 1.5M parameters, 3.2 GFLOPs)
- **Framework:** Ultralytics + Roboflow preprocessing pipeline
- **Dataset:** Lemon Leaf Disease Dataset (LLDD) — 3,436 images total
- roboflow: https://app.roboflow.com/torpat-rnkue/lemon-leaf-disease-o6qho/1
 
**Disease Classes:** Anthracnose, Bacterial Blight, Citrus Canker, Curl Virus, Deficiency Leaf, Dry Leaf, Healthy Leaf, Sooty Mold, Spider Mites
 
**Results:**
- Top-1 Accuracy: **93.4%**
- Top-5 Accuracy: **100%**
### Preprocessing & Augmentation
- Resize to 224×224 (center crop)
- Horizontal flip, zoom (0–20%), rotation (±15°), brightness (±15%)
- Dropout: 0.3 | Early stopping patience: 15 epochs
---
##  Getting Started
 
### Requirements

- Arduino IDE (for ESP32-C6 firmware)
- Python 3.x + Ultralytics (for AI/ML component)
### Libraries (Arduino)
 
```cpp
#include "DHT.h"
#include <WiFi.h>
#include <PubSubClient.h>
```
 
### ESP32-C6 Configuration
 
1. Open `SmartFarm.ino` in Arduino IDE
2. Set your Wi-Fi credentials:
```cpp
const char *ssid     = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";
```
3. Verify MQTT broker address (default: `broker.emqx.io`, port `1883`)
4. IoT wiring : Open 'V1_SmartFarm.fzz' or 'V1_SmartFarm_bb.png'
5. Upload to ESP32-C6
### MQTT Topics
 
| Topic | Data |
|-------|------|
| `smartfarm/temperature` | Temperature in °C |
| `smartfarm/humidity` | Humidity in %RH |
| `smartfarm/light` | Light intensity (analog value) 

---
 
##  Testing & Validation
 
### Wireshark Filters
 
```
mqtt                                        # Show all MQTT packets
tcp.port == 1883                            # Show MQTT port traffic
mqtt.topic == "smartfarm/humidity"          # Filter by topic
```

##  Known Limitations
 
- This project is a **prototype/concept** and not intended for large-scale real farm deployment
