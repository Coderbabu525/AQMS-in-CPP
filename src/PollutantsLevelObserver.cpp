#include<iostream>
#include "PollutantsLevelObserver.h"

using namespace std;

// to change status of pm2.5 sensor when it is different from current one
void PollutantsLevelObserver :: change_status_pm25(string status){
    pm25_status = status;
}

// to change status of pm10 sensor when it is different from current one
void PollutantsLevelObserver :: change_status_pm10(string status){
    pm10_status = status;
}