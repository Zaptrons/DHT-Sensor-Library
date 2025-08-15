#include "DHT.h"

// Initialize the DHT sensor object on pin 2
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