# MyDHT - A Simple Arduino Library for DHT Sensors

![Arduino Library Badge](https://img.shields.io/badge/Arduino%20Library-MyDHT-blue.svg)

A lightweight and easy-to-use library for reading temperature and humidity from DHT11 and DHT22 sensors.

## Features
- Supports both **DHT11** and **DHT22** sensors.
- Uses **micros()** for precise timing, ensuring reliable data acquisition.
- Includes a **checksum verification** to guarantee data integrity.
- Designed to be **small and efficient**.

## Installation

1.  Open the Arduino IDE.
2.  Go to **Sketch > Include Library > Manage Libraries...**
3.  Search for **"MyDHT"** and click **Install**.

Alternatively, you can manually install the library by downloading the ZIP file and adding it via **Sketch > Include Library > Add .ZIP Library...**

## Usage

### Simple Example

This example shows how to read and print temperature and humidity values to the Serial Monitor.

```cpp
#include "MyDHT.h"

// Initialize the DHT sensor object on pin 2.
// Note: This library supports only DHT11 for now.
DHT dht(2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Try to read sensor data every 2 seconds
  delay(2000);
  
  // Read sensor and check if the operation was successful
  if (dht.read()) {
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();
    
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }
}
```
## Contributing
If you have any suggestions or want to report a bug, please open an issue or create a pull request on the GitHub repository.