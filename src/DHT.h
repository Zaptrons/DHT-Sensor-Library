#ifndef DHT_H
#define DHT_H

#include <Arduino.h>

// Define a timeout constant for better readability and maintainability
#define DHT_TIMEOUT 100 // microseconds

class DHT {
public:
    // Constructor: Initializes the sensor with its data pin
    DHT(uint8_t pin);
    
    // Main function to initiate a full read cycle from the sensor
    bool read();
    
    // Public functions to retrieve the last measured values
    float getHumidity();
    float getTemperature();

private:
    // Private member variables to store the pin number and sensor data
    uint8_t _pin;
    uint8_t _data[5] = {0};
    
    // Helper function to send the start signal to the sensor
    void _sendRequest();
    
    // Helper function to wait for the sensor's response
    bool _waitForResponse();
    
    // Helper function to read all 40 data bits from the sensor
    bool _readDataBits();
    
    // Helper function to verify data integrity using the checksum
    bool _verifyChecksum();
};

#endif