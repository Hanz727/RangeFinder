#pragma once

#if defined(__has_include) && __has_include(<Arduino.h>)
    #include <Arduino.h>
#else
    // Some defines to make the LSP happy, this is ignored on the arduino boards
    void delayMicroseconds(int x);
    void digitalWrite(int a, int b);
    #define OUTPUT 1
    #define INPUT  0
    
    #define LOW 0
    #define HIGH 1
    
    void pinMode(int a, int b);
    int pulseIn(int a, int b);
#endif

#if defined(__has_include) && __has_include(<stdint.h>)
    #include <stdint.h>
#endif

#define ULTRASONIC_PING 0
#define ULTRASONIC_HC_SR04 1

class RangeFinder {
private:
    const uint8_t* m_sensors;
    uint8_t  m_sensor_count;
    uint8_t  m_sensor_type;

    double m_tempC = 20.;

    double* m_ranges;
private:
    double usToCm(unsigned long microseconds);
public:
    RangeFinder() = default;
    ~RangeFinder();
    RangeFinder(const uint8_t* sensors, const uint8_t count, const uint8_t sensorType);

    void setTempC(double tempCelcius);

    void   init(const uint8_t* sensors, const uint8_t count, const uint8_t sensorType);
    void   update(); // updates all the distances of all the sensors
    double getDistance(const uint8_t sensor); // returns distance in cm
};
