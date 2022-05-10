#include<iostream>

#include "CityAirPollutionInformer.h"
using namespace std;

// notify when all the spots have same pm2.5 status
void CityAirPollutionInformer :: pm25_alert_wholeCity(string s){
    cout << "The PM2.5 pollution in the whole city is " << s << " now" << endl;
}

// notify when all the spots have same pm10 status
void CityAirPollutionInformer :: pm10_alert_wholeCity(string s){
    cout << "The PM10 pollution in the whole city is " << s << " now" << endl;
}