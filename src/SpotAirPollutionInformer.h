#pragma once
using namespace std;

class SpotAirPollutionInformer{
    public:
        bool is_on = true;
        string spot_name = "\0";
    
    public:
        SpotAirPollutionInformer(string name);
        void pm25_alert(string s);
        void pm10_alert(string s);
        void pm_pollution_alert_onSpot(string s);
};