#pragma once
using namespace std;

class PollutantsLevelObserver{
    public:
        string pm25_status = "\0";
        string pm10_status = "\0";
    
    public:
        void change_status_pm25(string status);
        void change_status_pm10(string status);
};