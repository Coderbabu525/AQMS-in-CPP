#include "AirQualitySensor.h"
using namespace std;

// to turn the sensor on
void AirQualitySensor :: turn_on(){
    is_on = true;
}

// to turn the sensor off
void AirQualitySensor :: turn_off(){
    is_on = false;
}

// to connect the sensor with the hardware
void AirQualitySensor :: connect_to_sensorHardware(){
    is_connected_to_sensorHardware = true;
}