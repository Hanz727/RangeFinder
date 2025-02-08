#include "RangeFinder.h"

const int sensors = {6,7,8}; // PING pins, one pin for each sensor

RangeFinder rangeFinder;

void setup() {
    rangeFinder.init(sensors, 3, ULTRASONIC_PING);
}

void update() {
    rangeFinder.update(); // updates the ranges for all sensors

    // Gets measured distance from sensor on pin 6 in cm
    double dist0 = rangeFinder.getDistance(0);

}
