#include<iostream>

#include "SpotAirPollutionInformer.h"
using namespace std;

// dafault constructor to set spot name
SpotAirPollutionInformer :: SpotAirPollutionInformer(string name){
    spot_name = name;
}

// to generate pm2.5 alert in a particular spot
void SpotAirPollutionInformer :: pm25_alert(string s){
    cout << "The PM2.5 pollution level in " <<  spot_name << " is " << s << endl;
}

// to generate pm10 alert in a particular spot
void SpotAirPollutionInformer :: pm10_alert(string s){
    cout << "The PM10 pollution level in " <<  spot_name << " is " << s << endl;
}

// to generate both pm2.5 and pm10 alert when both are same in a particular spot
void SpotAirPollutionInformer :: pm_pollution_alert_onSpot(string s){
    cout << "The Overall PM pollution level in " << spot_name << " is " << s << endl;
}