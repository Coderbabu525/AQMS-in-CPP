#pragma once
using namespace std;
class CityAirPollutionInformer{
    public:
        bool is_on = true;
    
    public:
        void pm25_alert_wholeCity(string s);
        void pm10_alert_wholeCity(string s);
};