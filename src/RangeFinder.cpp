#include "RangeFinder.h"

void RangeFinder::init(const uint8_t* sensors, const uint8_t count, const uint8_t sensorType) {
    m_sensors = sensors;
    m_sensor_count = count;
    m_sensor_type = sensorType;

    m_ranges = new double[count];
	
	if (m_sensor_type == ULTRASONIC_HC_SR04) {
		for (int i = 0; i < count; i++) {
			uint8_t trigPin = m_sensors[2*i];
			uint8_t echoPin = m_sensors[2*i+1];
			pinMode(trigPin, OUTPUT);
			pinMode(echoPin, INPUT);
		}
	}
}

RangeFinder::~RangeFinder() {
    delete[] m_ranges;
}

RangeFinder::RangeFinder(const uint8_t* sensors, const uint8_t count, const uint8_t sensorType) {
    init(sensors, count, sensorType);
}

void RangeFinder::setTempC(double tempCelcius) {
   m_tempC = tempCelcius; 
}

double RangeFinder::usToCm(unsigned long microseconds) {
    double v = 331.3 + 0.606 * m_tempC;
    double speedOfSoundPerMicrosecond = v * 0.0001; // cm/µs
    return (microseconds * speedOfSoundPerMicrosecond) / 2.;
}

void RangeFinder::update() {
    for (int i = 0; i < m_sensor_count; i++) {
        uint8_t pin = m_sensors[i];

        if (m_sensor_type == ULTRASONIC_PING) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW);

            delayMicroseconds(2);
            digitalWrite(pin, HIGH);

            delayMicroseconds(5);
            digitalWrite(pin, LOW);

            pinMode(pin, INPUT);

            unsigned long duration = pulseIn(pin, HIGH, 1500);
            if (!duration)
                duration = 1500;
            m_ranges[i] = usToCm(duration);
        } else if (m_sensor_type == ULTRASONIC_HC_SR04) {
            uint8_t trigPin = m_sensors[2*i];
            uint8_t echoPin = m_sensors[2*i+1];
			
            digitalWrite(trigPin, LOW);
            delayMicroseconds(2);
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);

            unsigned long duration = pulseIn(echoPin, HIGH, 5000);
            if (!duration)
                duration = 5000;
            m_ranges[i] = usToCm(duration);
        }
        delay(20); // avoid echo
    }
}

double RangeFinder::getDistance(const uint8_t sensor) {
    return m_ranges[sensor];
}

