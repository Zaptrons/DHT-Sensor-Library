#include "DHT.h"

// Constructor implementation
DHT::DHT(uint8_t pin) {
    _pin = pin;
}

// Main public function to perform a full sensor read
bool DHT::read() {
    // 1. Send the start signal to the sensor
    _sendRequest();
    
    // 2. Wait for the sensor's response signal
    if (!_waitForResponse()) {
        return false;
    }
    
    // 3. Read all 40 bits of data
    if (!_readDataBits()) {
        return false;
    }
    
    // 4. Verify the integrity of the received data
    return _verifyChecksum();
}

// Sends the start signal to the DHT sensor
void DHT::_sendRequest() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delay(18); // Wait for at least 18ms as per datasheet
    digitalWrite(_pin, HIGH);
    delayMicroseconds(40); // Wait for sensor to respond
}

// Waits for the sensor's response signal
bool DHT::_waitForResponse() {
    pinMode(_pin, INPUT);
    unsigned long timeout = micros();
    
    // Wait for sensor to pull the line LOW (80us)
    while (digitalRead(_pin) == HIGH) {
        if (micros() - timeout > DHT_TIMEOUT) {
            return false;
        }
    }
    
    // Wait for sensor to pull the line HIGH (80us)
    timeout = micros();
    while (digitalRead(_pin) == LOW) {
        if (micros() - timeout > DHT_TIMEOUT) {
            return false;
        }
    }
    
    return true;
}

// Reads 40 data bits from the sensor and stores them in _data array
bool DHT::_readDataBits() {
    // Reset data array before reading
    for (int i = 0; i < 5; i++) {
        _data[i] = 0;
    }
    
    for (int i = 0; i < 40; i++) {
        unsigned long timeout = micros();
        
        // Wait for the start of a bit (line pulled LOW)
        while (digitalRead(_pin) == LOW) {
            if (micros() - timeout > DHT_TIMEOUT) {
                return false;
            }
        }
        
        // Measure the duration of the HIGH pulse to determine the bit value
        unsigned long start = micros();
        timeout = micros();
        while (digitalRead(_pin) == HIGH) {
            if (micros() - timeout > DHT_TIMEOUT) {
                return false;
            }
        }
        unsigned long duration = micros() - start;
        
        // If the pulse is long (> ~40us), it's a '1'
        if (duration > 40) {
            _data[i / 8] |= (1 << (7 - (i % 8)));
        }
    }
    return true;
}

// Verifies the checksum of the received data
bool DHT::_verifyChecksum() {
    uint8_t sum = _data[0] + _data[1] + _data[2] + _data[3];
    return sum == _data[4];
}

// Returns the humidity value from the data array
float DHT::getHumidity() {
    // For DHT11, humidity is the first byte
    return (float)_data[0];
}

// Returns the temperature value from the data array
float DHT::getTemperature() {
    // For DHT11, temperature is the third byte
    return (float)_data[2];
}