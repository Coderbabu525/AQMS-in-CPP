#pragma once

class AirQualitySensor{
    public:
        float pm25_sensor = 0.0;
        float pm10_sensor = 0.0;
        bool is_on = true;
        bool is_connected_to_sensorHardware = true;
    
    public:
        void turn_on();
        void turn_off();
        void connect_to_sensorHardware();
};