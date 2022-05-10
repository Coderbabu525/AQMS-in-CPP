#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <sys/time.h>
#include <sys/resource.h>
using namespace std;
using namespace std::chrono;

#include "AirQualitySensor.h"
#include "PollutantsLevelObserver.h"
#include "SpotAirPollutionInformer.h"
#include "CityAirPollutionInformer.h"

double getMemoryUsage() 
{
  struct rusage usage;
  if(0 == getrusage(RUSAGE_SELF, &usage))
    return usage.ru_maxrss; // bytes
  else
    return 0;
}

int main()
{
    AirQualitySensor AQSensor_uni, AQSensor_road, AQSensor_center;
    PollutantsLevelObserver PLO_uni, PLO_road, PLO_center;
    SpotAirPollutionInformer SAPInformer_uni("University"), SAPInformer_road("RoadSide"), SAPInformer_center("CityCenter");
    CityAirPollutionInformer CAPInformer_city;
    double exec_time=0.0;
    // File pointer
    fstream fin_u, fin_c, fin_r;
  
    // Open an existing file
    /*fin_c.open("CityCenter.csv");
    fin_r.open("RoadSide.csv");
    fin_u.open("University.csv");*/
    fin_c.open("data1.csv");
    fin_r.open("data2.csv");
    fin_u.open("data3.csv");
    // Read the Data from the file
    // as String Vector
    vector<string> row_c, row_r, row_u;
    string line_c, line_u, line_r, word_c, word_r, word_u, temp_c, temp_u, temp_r;
    getline(fin_c, line_c);
    getline(fin_u, line_u);
    getline(fin_r, line_r);
    //cout << fin_c << endl;
    int cnt = 0;
    while (fin_c >> temp_c && fin_r >> temp_r && fin_u >> temp_u){
        //cout << "inside first while" << endl;
        cnt++;
        row_c.clear();
        row_r.clear();
        row_u.clear();

        stringstream c(temp_c), r(temp_r), u(temp_u);
        //cout << line_c << endl;
        // read every column data of a row and
        // store it in a string variable, 'word'
        // for(int j = 0; j <= 7; j++)
        while (getline(c, word_c, ';')) {
            getline(r, word_r, ';');
            getline(u, word_u, ';');

            //cout << "inside second while" << endl;
            //cout << word_c << endl;
            // add all the column data
            // of a row to a vector
            row_c.push_back(word_c);
            row_r.push_back(word_r);
            row_u.push_back(word_u);
        }
        string p10 = row_c.at(3), p25 = row_c.at(8);
        //cout << "before conversion" << endl;
        //cout << p25 << endl;
        //cout << typeid(p10).name() << typeid(p25).name() << endl;
        float pm10 = stof(p10), pm25 = stof(p25);
        
        AQSensor_center.pm25_sensor = pm25;
        AQSensor_center.pm10_sensor = pm10;
        
        p10 = row_r.at(3), p25 = row_r.at(8);
        pm10 = stof(p10), pm25 = stof(p25);
        AQSensor_road.pm25_sensor = pm25;
        AQSensor_road.pm10_sensor = pm10;

        p10 = row_u.at(3), p25 = row_u.at(8);
        pm10 = stof(p10), pm25 = stof(p25);
        AQSensor_uni.pm25_sensor = pm25;
        AQSensor_uni.pm10_sensor = pm10;
        
        auto start = high_resolution_clock::now();
        //cout << "Start of Rules" << endl;

        // Rules

        // Rules 1 - 18 for pm2.5 in 3 different spots
        // Rule 1 
        // CONDITION
        if ( 
            AQSensor_uni.is_on          == true             &&      // Premise 1
            AQSensor_uni.pm25_sensor    <= 5.0              &&   	// Premise 2
            PLO_uni.pm25_status         != "Excellent" 	    &&    	// Premise 3
            SAPInformer_uni.is_on 	    == true)		            // Premise 4
        
        // ACTION
        {
            SAPInformer_uni.pm25_alert("Excellent");            // Instigation 1
            PLO_uni.change_status_pm25("Excellent");			// Instigation 2
        }

        // Rule 2
        // CONDITION
        if ( 
            AQSensor_uni.is_on          == true             &&      // Premise 1
            AQSensor_uni.pm25_sensor    <= 10.0             &&   	// Premise 2
            AQSensor_uni.pm25_sensor    >  5.0              &&      // Premise 3
            PLO_uni.pm25_status         != "Fine" 	        &&    	// Premise 4
            SAPInformer_uni.is_on 	    == true)		            // Premise 5
        
        // ACTION
        {
            SAPInformer_uni.pm25_alert("Fine");             // Instigation 1
            PLO_uni.change_status_pm25("Fine");			    // Instigation 2
        }

        // Rule 3
        // CONDITION
        if ( 
            AQSensor_uni.is_on          == true             &&      // Premise 1
            AQSensor_uni.pm25_sensor    <= 20.0             &&   	// Premise 2
            AQSensor_uni.pm25_sensor    >  10.0             &&      // Premise 3
            PLO_uni.pm25_status         != "Moderate" 	    &&    	// Premise 4
            SAPInformer_uni.is_on 	    == true)		            // Premise 5
        
        // ACTION
        {
            SAPInformer_uni.pm25_alert("Moderate");             // Instigation 1
            PLO_uni.change_status_pm25("Moderate");			    // Instigation 2
        }

        // Rule 4
        // CONDITION
        if ( 
            AQSensor_uni.is_on          == true             &&      // Premise 1
            AQSensor_uni.pm25_sensor    <= 25.0             &&   	// Premise 2
            AQSensor_uni.pm25_sensor    >  20.0             &&      // Premise 3
            PLO_uni.pm25_status         != "Poor" 	        &&    	// Premise 4
            SAPInformer_uni.is_on 	    == true)		            // Premise 5
        
        // ACTION
        {
            SAPInformer_uni.pm25_alert("Poor");             // Instigation 1
            PLO_uni.change_status_pm25("Poor");			    // Instigation 2
        }

        // Rule 5
        // CONDITION
        if ( 
            AQSensor_uni.is_on          == true             &&      // Premise 1
            AQSensor_uni.pm25_sensor    <= 60.0             &&   	// Premise 2
            AQSensor_uni.pm25_sensor    >  25.0             &&      // Premise 3
            PLO_uni.pm25_status         != "Very Poor" 	    &&    	// Premise 4
            SAPInformer_uni.is_on 	    == true)		            // Premise 5
        
        // ACTION
        {
            SAPInformer_uni.pm25_alert("Very Poor");             // Instigation 1
            PLO_uni.change_status_pm25("Very Poor");			 // Instigation 2
        }

        // Rule 6
        // CONDITION
        if ( 
            AQSensor_uni.is_on          == true             &&      // Premise 1
            AQSensor_uni.pm25_sensor    >  60.0             &&      // Premise 2
            PLO_uni.pm25_status         != "Severe" 	    &&    	// Premise 3
            SAPInformer_uni.is_on 	    == true)		            // Premise 4
        
        // ACTION
        {
            SAPInformer_uni.pm25_alert("Severe");               // Instigation 1
            PLO_uni.change_status_pm25("Severe");			    // Instigation 2
        }

        // Rule 7 
        // CONDITION
        if ( 
            AQSensor_road.is_on          == true             &&     // Premise 1
            AQSensor_road.pm25_sensor    <= 5.0              &&   	// Premise 2
            PLO_road.pm25_status         != "Excellent" 	 &&    	// Premise 3
            SAPInformer_road.is_on 	     == true)		            // Premise 4
        
        // ACTION
        {
            SAPInformer_road.pm25_alert("Excellent");           // Instigation 1
            PLO_road.change_status_pm25("Excellent");			// Instigation 2
        }

        // Rule 8
        // CONDITION
        if ( 
            AQSensor_road.is_on          == true             &&      // Premise 1
            AQSensor_road.pm25_sensor    <= 10.0             &&   	 // Premise 2
            AQSensor_road.pm25_sensor    >  5.0              &&      // Premise 3
            PLO_road.pm25_status         != "Fine" 	         &&    	 // Premise 4
            SAPInformer_road.is_on 	     == true)		             // Premise 5
        
        // ACTION
        {
            SAPInformer_road.pm25_alert("Fine");             // Instigation 1
            PLO_road.change_status_pm25("Fine");			 // Instigation 2
        }

        // Rule 9
        // CONDITION
        if ( 
            AQSensor_road.is_on          == true             &&      // Premise 1
            AQSensor_road.pm25_sensor    <= 20.0             &&   	 // Premise 2
            AQSensor_road.pm25_sensor    >  10.0             &&      // Premise 3
            PLO_road.pm25_status         != "Moderate" 	     &&    	 // Premise 4
            SAPInformer_road.is_on 	     == true)		             // Premise 5
        
        // ACTION
        {
            SAPInformer_road.pm25_alert("Moderate");             // Instigation 1
            PLO_road.change_status_pm25("Moderate");			 // Instigation 2
        }

        // Rule 10
        // CONDITION
        if ( 
            AQSensor_road.is_on          == true             &&      // Premise 1
            AQSensor_road.pm25_sensor    <= 25.0             &&   	 // Premise 2
            AQSensor_road.pm25_sensor    >  20.0             &&      // Premise 3
            PLO_road.pm25_status         != "Poor" 	         &&    	 // Premise 4
            SAPInformer_road.is_on 	     == true)		             // Premise 5
        
        // ACTION
        {
            SAPInformer_road.pm25_alert("Poor");             // Instigation 1
            PLO_road.change_status_pm25("Poor");			 // Instigation 2
        }

        // Rule 11
        // CONDITION
        if ( 
            AQSensor_road.is_on          == true             &&      // Premise 1
            AQSensor_road.pm25_sensor    <= 60.0             &&   	 // Premise 2
            AQSensor_road.pm25_sensor    >  25.0             &&      // Premise 3
            PLO_road.pm25_status         != "Very Poor" 	 &&    	 // Premise 4
            SAPInformer_road.is_on 	     == true)		             // Premise 5
        
        // ACTION
        {
            SAPInformer_road.pm25_alert("Very Poor");             // Instigation 1
            PLO_road.change_status_pm25("Very Poor");			  // Instigation 2
        }

        // Rule 12
        // CONDITION
        if ( 
            AQSensor_road.is_on          == true             &&      // Premise 1
            AQSensor_road.pm25_sensor    >  60.0             &&      // Premise 2
            PLO_road.pm25_status         != "Severe" 	     &&    	 // Premise 3
            SAPInformer_road.is_on 	     == true)		             // Premise 4
        
        // ACTION
        {
            SAPInformer_road.pm25_alert("Severe");               // Instigation 1
            PLO_road.change_status_pm25("Severe");			     // Instigation 2
        }

        // Rule 13 
        // CONDITION
        if ( 
            AQSensor_center.is_on          == true             &&       // Premise 1
            AQSensor_center.pm25_sensor    <= 5.0              &&   	// Premise 2
            PLO_center.pm25_status         != "Excellent" 	   &&    	// Premise 3
            SAPInformer_center.is_on 	   == true)		                // Premise 4
        
        // ACTION
        {
            SAPInformer_center.pm25_alert("Excellent");            // Instigation 1
            PLO_center.change_status_pm25("Excellent");			   // Instigation 2
        }

        // Rule 14
        // CONDITION
        if ( 
            AQSensor_center.is_on          == true             &&       // Premise 1
            AQSensor_center.pm25_sensor    <= 10.0             &&   	// Premise 2
            AQSensor_center.pm25_sensor    >  5.0              &&       // Premise 3
            PLO_center.pm25_status         != "Fine" 	       &&    	// Premise 4
            SAPInformer_center.is_on 	   == true)		                // Premise 5
        
        // ACTION
        {
            SAPInformer_center.pm25_alert("Fine");              // Instigation 1
            PLO_center.change_status_pm25("Fine");			    // Instigation 2
        }

        // Rule 15
        // CONDITION
        if ( 
            AQSensor_center.is_on          == true             &&       // Premise 1
            AQSensor_center.pm25_sensor    <= 20.0             &&   	// Premise 2
            AQSensor_center.pm25_sensor    >  10.0             &&       // Premise 3
            PLO_center.pm25_status         != "Moderate" 	   &&    	// Premise 4
            SAPInformer_center.is_on 	   == true)		                // Premise 5
        
        // ACTION
        {
            SAPInformer_center.pm25_alert("Moderate");              // Instigation 1
            PLO_center.change_status_pm25("Moderate");			    // Instigation 2
        }

        // Rule 16
        // CONDITION
        if ( 
            AQSensor_center.is_on          == true             &&       // Premise 1
            AQSensor_center.pm25_sensor    <= 25.0             &&   	// Premise 2
            AQSensor_center.pm25_sensor    >  20.0             &&       // Premise 3
            PLO_center.pm25_status         != "Poor" 	       &&    	// Premise 4
            SAPInformer_center.is_on 	   == true)		                // Premise 5
        
        // ACTION
        {
            SAPInformer_center.pm25_alert("Poor");              // Instigation 1
            PLO_center.change_status_pm25("Poor");			    // Instigation 2
        }

        // Rule 17
        // CONDITION
        if ( 
            AQSensor_center.is_on          == true             &&       // Premise 1
            AQSensor_center.pm25_sensor    <= 60.0             &&   	// Premise 2
            AQSensor_center.pm25_sensor    >  25.0             &&       // Premise 3
            PLO_center.pm25_status         != "Very Poor" 	   &&    	// Premise 4
            SAPInformer_center.is_on 	   == true)		                // Premise 5
        
        // ACTION
        {
            SAPInformer_center.pm25_alert("Very Poor");             // Instigation 1
            PLO_center.change_status_pm25("Very Poor");			    // Instigation 2
        }

        // Rule 18
        // CONDITION
        if ( 
            AQSensor_center.is_on          == true             &&       // Premise 1
            AQSensor_center.pm25_sensor    >  60.0             &&       // Premise 2
            PLO_center.pm25_status         != "Severe" 	       &&    	// Premise 3
            SAPInformer_center.is_on 	   == true)		                // Premise 4
        
        // ACTION
        {
            SAPInformer_center.pm25_alert("Severe");                // Instigation 1
            PLO_center.change_status_pm25("Severe");			    // Instigation 2
        }

        // Rules 19 - 36 for pm10 in 3 different spots

        // Rule 19 
        // CONDITION
        if ( 
            AQSensor_uni.is_on          == true             &&      // Premise 1
            AQSensor_uni.pm10_sensor    <= 10.0             &&   	// Premise 2
            PLO_uni.pm10_status         != "Excellent" 	    &&    	// Premise 3
            SAPInformer_uni.is_on 	    == true)		            // Premise 4
        
        // ACTION
        {
            SAPInformer_uni.pm10_alert("Excellent");            // Instigation 1
            PLO_uni.change_status_pm10("Excellent");			// Instigation 2
        }

        // Rule 20
        // CONDITION
        if ( 
            AQSensor_uni.is_on          == true             &&      // Premise 1
            AQSensor_uni.pm10_sensor    <= 20.0             &&   	// Premise 2
            AQSensor_uni.pm10_sensor    >  10.0             &&      // Premise 3
            PLO_uni.pm10_status         != "Fine" 	        &&    	// Premise 4
            SAPInformer_uni.is_on 	    == true)		            // Premise 5
        
        // ACTION
        {
            SAPInformer_uni.pm10_alert("Fine");             // Instigation 1
            PLO_uni.change_status_pm10("Fine");			    // Instigation 2
        }

        // Rule 21
        // CONDITION
        if ( 
            AQSensor_uni.is_on          == true             &&      // Premise 1
            AQSensor_uni.pm10_sensor    <= 35.0             &&   	// Premise 2
            AQSensor_uni.pm10_sensor    >  20.0             &&      // Premise 3
            PLO_uni.pm10_status         != "Moderate" 	    &&    	// Premise 4
            SAPInformer_uni.is_on 	    == true)		            // Premise 5
        
        // ACTION
        {
            SAPInformer_uni.pm10_alert("Moderate");             // Instigation 1
            PLO_uni.change_status_pm10("Moderate");			    // Instigation 2
        }

        // Rule 22
        // CONDITION
        if ( 
            AQSensor_uni.is_on          == true             &&      // Premise 1
            AQSensor_uni.pm10_sensor    <= 50.0             &&   	// Premise 2
            AQSensor_uni.pm10_sensor    >  35.0             &&      // Premise 3
            PLO_uni.pm10_status         != "Poor" 	        &&    	// Premise 4
            SAPInformer_uni.is_on 	    == true)		            // Premise 5
        
        // ACTION
        {
            SAPInformer_uni.pm10_alert("Poor");             // Instigation 1
            PLO_uni.change_status_pm10("Poor");			    // Instigation 2
        }

        // Rule 23
        // CONDITION
        if ( 
            AQSensor_uni.is_on          == true             &&      // Premise 1
            AQSensor_uni.pm10_sensor    <= 100.0            &&   	// Premise 2
            AQSensor_uni.pm10_sensor    >  50.0             &&      // Premise 3
            PLO_uni.pm10_status         != "Very Poor" 	    &&    	// Premise 4
            SAPInformer_uni.is_on 	    == true)		            // Premise 5
        
        // ACTION
        {
            SAPInformer_uni.pm10_alert("Very Poor");             // Instigation 1
            PLO_uni.change_status_pm10("Very Poor");			 // Instigation 2
        }

        // Rule 24
        // CONDITION
        if ( 
            AQSensor_uni.is_on          == true             &&      // Premise 1
            AQSensor_uni.pm10_sensor    >  100.0            &&      // Premise 2
            PLO_uni.pm10_status         != "Severe" 	    &&    	// Premise 3
            SAPInformer_uni.is_on 	    == true)		            // Premise 4
        
        // ACTION
        {
            SAPInformer_uni.pm10_alert("Severe");               // Instigation 1
            PLO_uni.change_status_pm10("Severe");			    // Instigation 2
        }

        // Rule 25 
        // CONDITION
        if ( 
            AQSensor_road.is_on          == true             &&     // Premise 1
            AQSensor_road.pm10_sensor    <= 10.0             &&   	// Premise 2
            PLO_road.pm10_status         != "Excellent" 	 &&    	// Premise 3
            SAPInformer_road.is_on 	     == true)		            // Premise 4
        
        // ACTION
        {
            SAPInformer_road.pm10_alert("Excellent");           // Instigation 1
            PLO_road.change_status_pm10("Excellent");			// Instigation 2
        }

        // Rule 26
        // CONDITION
        if ( 
            AQSensor_road.is_on          == true             &&      // Premise 1
            AQSensor_road.pm10_sensor    <= 20.0             &&   	 // Premise 2
            AQSensor_road.pm10_sensor    >  10.0             &&      // Premise 3
            PLO_road.pm10_status         != "Fine" 	         &&    	 // Premise 4
            SAPInformer_road.is_on 	     == true)		             // Premise 5
        
        // ACTION
        {
            SAPInformer_road.pm10_alert("Fine");             // Instigation 1
            PLO_road.change_status_pm10("Fine");			 // Instigation 2
        }

        // Rule 27
        // CONDITION
        if ( 
            AQSensor_road.is_on          == true             &&      // Premise 1
            AQSensor_road.pm10_sensor    <= 35.0             &&   	 // Premise 2
            AQSensor_road.pm10_sensor    >  20.0             &&      // Premise 3
            PLO_road.pm10_status         != "Moderate" 	     &&    	 // Premise 4
            SAPInformer_road.is_on 	     == true)		             // Premise 5
        
        // ACTION
        {
            SAPInformer_road.pm10_alert("Moderate");             // Instigation 1
            PLO_road.change_status_pm10("Moderate");			 // Instigation 2
        }

        // Rule 28
        // CONDITION
        if ( 
            AQSensor_road.is_on          == true             &&      // Premise 1
            AQSensor_road.pm10_sensor    <= 50.0             &&   	 // Premise 2
            AQSensor_road.pm10_sensor    >  35.0             &&      // Premise 3
            PLO_road.pm10_status         != "Poor" 	         &&    	 // Premise 4
            SAPInformer_road.is_on 	     == true)		             // Premise 5
        
        // ACTION
        {
            SAPInformer_road.pm10_alert("Poor");             // Instigation 1
            PLO_road.change_status_pm10("Poor");			 // Instigation 2
        }

        // Rule 29
        // CONDITION
        if ( 
            AQSensor_road.is_on          == true             &&      // Premise 1
            AQSensor_road.pm10_sensor    <= 100.0            &&   	 // Premise 2
            AQSensor_road.pm10_sensor    >  50.0             &&      // Premise 3
            PLO_road.pm10_status         != "Very Poor" 	 &&    	 // Premise 4
            SAPInformer_road.is_on 	     == true)		             // Premise 5
        
        // ACTION
        {
            SAPInformer_road.pm10_alert("Very Poor");             // Instigation 1
            PLO_road.change_status_pm10("Very Poor");			  // Instigation 2
        }

        // Rule 30
        // CONDITION
        if ( 
            AQSensor_road.is_on          == true             &&      // Premise 1
            AQSensor_road.pm10_sensor    >  100.0            &&      // Premise 2
            PLO_road.pm10_status         != "Severe" 	     &&    	 // Premise 3
            SAPInformer_road.is_on 	     == true)		             // Premise 4
        
        // ACTION
        {
            SAPInformer_road.pm10_alert("Severe");               // Instigation 1
            PLO_road.change_status_pm10("Severe");			     // Instigation 2
        }

        // Rule 31 
        // CONDITION
        if ( 
            AQSensor_center.is_on          == true             &&       // Premise 1
            AQSensor_center.pm10_sensor    <= 10.0             &&   	// Premise 2
            PLO_center.pm10_status         != "Excellent" 	   &&    	// Premise 3
            SAPInformer_center.is_on 	   == true)		                // Premise 4
        
        // ACTION
        {
            SAPInformer_center.pm10_alert("Excellent");            // Instigation 1
            PLO_center.change_status_pm10("Excellent");			   // Instigation 2
        }

        // Rule 32
        // CONDITION
        if ( 
            AQSensor_center.is_on          == true             &&       // Premise 1
            AQSensor_center.pm10_sensor    <= 20.0             &&   	// Premise 2
            AQSensor_center.pm10_sensor    >  10.0             &&       // Premise 3
            PLO_center.pm10_status         != "Fine" 	       &&    	// Premise 4
            SAPInformer_center.is_on 	   == true)		                // Premise 5
        
        // ACTION
        {
            SAPInformer_center.pm10_alert("Fine");              // Instigation 1
            PLO_center.change_status_pm10("Fine");			    // Instigation 2
        }

        // Rule 33
        // CONDITION
        if ( 
            AQSensor_center.is_on          == true             &&       // Premise 1
            AQSensor_center.pm10_sensor    <= 35.0             &&   	// Premise 2
            AQSensor_center.pm10_sensor    >  20.0             &&       // Premise 3
            PLO_center.pm10_status         != "Moderate" 	   &&    	// Premise 4
            SAPInformer_center.is_on 	   == true)		                // Premise 5
        
        // ACTION
        {
            SAPInformer_center.pm10_alert("Moderate");              // Instigation 1
            PLO_center.change_status_pm10("Moderate");			    // Instigation 2
        }

        // Rule 34
        // CONDITION
        if ( 
            AQSensor_center.is_on          == true             &&       // Premise 1
            AQSensor_center.pm10_sensor    <= 50.0             &&   	// Premise 2
            AQSensor_center.pm10_sensor    >  35.0             &&       // Premise 3
            PLO_center.pm10_status         != "Poor" 	       &&    	// Premise 4
            SAPInformer_center.is_on 	   == true)		                // Premise 5
        
        // ACTION
        {
            SAPInformer_center.pm10_alert("Poor");              // Instigation 1
            PLO_center.change_status_pm10("Poor");			    // Instigation 2
        }

        // Rule 35
        // CONDITION
        if ( 
            AQSensor_center.is_on          == true             &&       // Premise 1
            AQSensor_center.pm10_sensor    <= 100.0            &&   	// Premise 2
            AQSensor_center.pm10_sensor    >  50.0             &&       // Premise 3
            PLO_center.pm10_status         != "Very Poor" 	   &&    	// Premise 4
            SAPInformer_center.is_on 	   == true)		                // Premise 5
        
        // ACTION
        {
            SAPInformer_center.pm10_alert("Very Poor");             // Instigation 1
            PLO_center.change_status_pm10("Very Poor");			    // Instigation 2
        }

        // Rule 36
        // CONDITION
        if ( 
            AQSensor_center.is_on          == true             &&       // Premise 1
            AQSensor_center.pm10_sensor    >  100.0            &&       // Premise 2
            PLO_center.pm10_status         != "Severe" 	       &&    	// Premise 3
            SAPInformer_center.is_on 	   == true)		                // Premise 4
        
        // ACTION
        {
            SAPInformer_center.pm10_alert("Severe");                // Instigation 1
            PLO_center.change_status_pm10("Severe");			    // Instigation 2
        }

        // Rules 37 - 42 notifies when pm2.5 status in all the spots are same
        // Rule 37
        // CONDITION
        if ( 
            CAPInformer_city.is_on          == true             &&       // Premise 1
            PLO_uni.pm25_status             == "Excellent"      &&       // Premise 2
            PLO_road.pm25_status 	        == "Excellent"		&&       // Premise 3
            PLO_center.pm25_status          == "Excellent")              // Premise 4
        
        // ACTION
        {
            CAPInformer_city.pm25_alert_wholeCity("Excellent");          // Instigation 1
        }

        // Rule 38
        // CONDITION
        if ( 
            CAPInformer_city.is_on          == true             &&       // Premise 1
            PLO_uni.pm25_status             == "Fine"           &&       // Premise 2
            PLO_road.pm25_status 	        == "Fine"		    &&       // Premise 3
            PLO_center.pm25_status          == "Fine")                   // Premise 4
        
        // ACTION
        {
            CAPInformer_city.pm25_alert_wholeCity("Fine");               // Instigation 1
        }

        // Rule 39
        // CONDITION
        if ( 
            CAPInformer_city.is_on          == true             &&       // Premise 1
            PLO_uni.pm25_status             == "Moderate"       &&       // Premise 2
            PLO_road.pm25_status 	        == "Moderate"		&&       // Premise 3
            PLO_center.pm25_status          == "Moderate")               // Premise 4
        
        // ACTION
        {
            CAPInformer_city.pm25_alert_wholeCity("Moderate");           // Instigation 1
        }

        // Rule 40
        // CONDITION
        if ( 
            CAPInformer_city.is_on          == true             &&       // Premise 1
            PLO_uni.pm25_status             == "Poor"           &&       // Premise 2
            PLO_road.pm25_status 	        == "Poor"		    &&       // Premise 3
            PLO_center.pm25_status          == "Poor")                   // Premise 4
        
        // ACTION
        {
            CAPInformer_city.pm25_alert_wholeCity("Poor");               // Instigation 1
        }

        // Rule 41
        // CONDITION
        if ( 
            CAPInformer_city.is_on          == true             &&       // Premise 1
            PLO_uni.pm25_status             == "Very Poor"      &&       // Premise 2
            PLO_road.pm25_status 	        == "Very Poor"		&&       // Premise 3
            PLO_center.pm25_status          == "Very Poor")              // Premise 4
        
        // ACTION
        {
            CAPInformer_city.pm25_alert_wholeCity("Very Poor");          // Instigation 1
        }

        // Rule 42
        // CONDITION
        if ( 
            CAPInformer_city.is_on          == true             &&       // Premise 1
            PLO_uni.pm25_status             == "Severe"         &&       // Premise 2
            PLO_road.pm25_status 	        == "Severe"		    &&       // Premise 3
            PLO_center.pm25_status          == "Severe")                 // Premise 4
        
        // ACTION
        {
            CAPInformer_city.pm25_alert_wholeCity("Severe");             // Instigation 1
        }

        // Rules 43 - 48 notifies when pm10 status in all the spots are same
        // Rule 43
        // CONDITION
        if ( 
            CAPInformer_city.is_on          == true             &&       // Premise 1
            PLO_uni.pm10_status             == "Excellent"      &&       // Premise 2
            PLO_road.pm10_status 	        == "Excellent"		&&       // Premise 3
            PLO_center.pm10_status          == "Excellent")              // Premise 4
        
        // ACTION
        {
            CAPInformer_city.pm10_alert_wholeCity("Excellent");          // Instigation 1
        }

        // Rule 44
        // CONDITION
        if ( 
            CAPInformer_city.is_on          == true             &&       // Premise 1
            PLO_uni.pm10_status             == "Fine"           &&       // Premise 2
            PLO_road.pm10_status 	        == "Fine"		    &&       // Premise 3
            PLO_center.pm10_status          == "Fine")                   // Premise 4
        
        // ACTION
        {
            CAPInformer_city.pm10_alert_wholeCity("Fine");               // Instigation 1
        }

        // Rule 45
        // CONDITION
        if ( 
            CAPInformer_city.is_on          == true             &&       // Premise 1
            PLO_uni.pm10_status             == "Moderate"       &&       // Premise 2
            PLO_road.pm10_status 	        == "Moderate"		&&       // Premise 3
            PLO_center.pm10_status          == "Moderate")               // Premise 4
        
        // ACTION
        {
            CAPInformer_city.pm10_alert_wholeCity("Moderate");           // Instigation 1
        }

        // Rule 46
        // CONDITION
        if ( 
            CAPInformer_city.is_on          == true             &&       // Premise 1
            PLO_uni.pm10_status             == "Poor"           &&       // Premise 2
            PLO_road.pm10_status 	        == "Poor"		    &&       // Premise 3
            PLO_center.pm10_status          == "Poor")                   // Premise 4
        
        // ACTION
        {
            CAPInformer_city.pm10_alert_wholeCity("Poor");               // Instigation 1
        }

        // Rule 47
        // CONDITION
        if ( 
            CAPInformer_city.is_on          == true             &&       // Premise 1
            PLO_uni.pm10_status             == "Very Poor"      &&       // Premise 2
            PLO_road.pm10_status 	        == "Very Poor"		&&       // Premise 3
            PLO_center.pm10_status          == "Very Poor")              // Premise 4
        
        // ACTION
        {
            CAPInformer_city.pm10_alert_wholeCity("Very Poor");          // Instigation 1
        }

        // Rule 48
        // CONDITION
        if ( 
            CAPInformer_city.is_on          == true             &&       // Premise 1
            PLO_uni.pm10_status             == "Severe"         &&       // Premise 2
            PLO_road.pm10_status 	        == "Severe"		    &&       // Premise 3
            PLO_center.pm10_status          == "Severe")                 // Premise 4
        
        // ACTION
        {
            CAPInformer_city.pm10_alert_wholeCity("Severe");             // Instigation 1
        }

        // Rules 49 - 66 notifies when both pm2.5 and pm10 status is same in a particular spot

        // Rule 49
        // CONDITION
        if ( 
            SAPInformer_uni.is_on           == true                 &&       // Premise 1
            PLO_uni.pm25_status             == "Excellent"          &&       // Premise 2
            PLO_uni.pm10_status 	        == "Excellent")		             // Premise 3
            
        // ACTION
        {
            SAPInformer_uni.pm_pollution_alert_onSpot("Excellent");          // Instigation 1
        }

        // Rule 50
        // CONDITION
        if ( 
            SAPInformer_uni.is_on           == true             &&       // Premise 1
            PLO_uni.pm25_status             == "Fine"           &&       // Premise 2
            PLO_uni.pm10_status 	        == "Fine")		             // Premise 3
            
        // ACTION
        {
            SAPInformer_uni.pm_pollution_alert_onSpot("Fine");          // Instigation 1
        }

        // Rule 51
        // CONDITION
        if ( 
            SAPInformer_uni.is_on           == true                 &&       // Premise 1
            PLO_uni.pm25_status             == "Moderate"           &&       // Premise 2
            PLO_uni.pm10_status 	        == "Moderate")		             // Premise 3
            
        // ACTION
        {
            SAPInformer_uni.pm_pollution_alert_onSpot("Moderate");          // Instigation 1
        }

        // Rule 52
        // CONDITION
        if ( 
            SAPInformer_uni.is_on           == true                 &&       // Premise 1
            PLO_uni.pm25_status             == "Poor"               &&       // Premise 2
            PLO_uni.pm10_status 	        == "Poor") 		                 // Premise 3
            
        // ACTION
        {
            SAPInformer_uni.pm_pollution_alert_onSpot("Poor");              // Instigation 1
        }

        // Rule 53
        // CONDITION
        if ( 
            SAPInformer_uni.is_on           == true                 &&       // Premise 1
            PLO_uni.pm25_status             == "Very Poor"          &&       // Premise 2
            PLO_uni.pm10_status 	        == "Very Poor")		             // Premise 3
            
        // ACTION
        {
            SAPInformer_uni.pm_pollution_alert_onSpot("Very Poor");          // Instigation 1
        }

        // Rule 54
        // CONDITION
        if ( 
            SAPInformer_uni.is_on           == true                 &&       // Premise 1
            PLO_uni.pm25_status             == "Severe"             &&       // Premise 2
            PLO_uni.pm10_status 	        == "Severe")		             // Premise 3
            
        // ACTION
        {
            SAPInformer_uni.pm_pollution_alert_onSpot("Severe");            // Instigation 1
        }

        // Rule 55
        // CONDITION
        if ( 
            SAPInformer_road.is_on           == true                 &&       // Premise 1
            PLO_road.pm25_status             == "Excellent"          &&       // Premise 2
            PLO_road.pm10_status 	         == "Excellent")		          // Premise 3
            
        // ACTION
        {
            SAPInformer_road.pm_pollution_alert_onSpot("Excellent");          // Instigation 1
        }

        // Rule 56
        // CONDITION
        if ( 
            SAPInformer_road.is_on           == true             &&       // Premise 1
            PLO_road.pm25_status             == "Fine"           &&       // Premise 2
            PLO_road.pm10_status 	         == "Fine")		              // Premise 3
            
        // ACTION
        {
            SAPInformer_road.pm_pollution_alert_onSpot("Fine");          // Instigation 1
        }

        // Rule 57
        // CONDITION
        if ( 
            SAPInformer_road.is_on           == true                 &&       // Premise 1
            PLO_road.pm25_status             == "Moderate"           &&       // Premise 2
            PLO_road.pm10_status 	         == "Moderate")		              // Premise 3
            
        // ACTION
        {
            SAPInformer_road.pm_pollution_alert_onSpot("Moderate");          // Instigation 1
        }

        // Rule 58
        // CONDITION
        if ( 
            SAPInformer_road.is_on           == true                 &&       // Premise 1
            PLO_road.pm25_status             == "Poor"               &&       // Premise 2
            PLO_road.pm10_status 	         == "Poor")		                  // Premise 3
            
        // ACTION
        {
            SAPInformer_road.pm_pollution_alert_onSpot("Poor");              // Instigation 1
        }

        // Rule 59
        // CONDITION
        if ( 
            SAPInformer_road.is_on           == true                 &&       // Premise 1
            PLO_road.pm25_status             == "Very Poor"          &&       // Premise 2
            PLO_road.pm10_status 	         == "Very Poor")		          // Premise 3
            
        // ACTION
        {
            SAPInformer_road.pm_pollution_alert_onSpot("Very Poor");          // Instigation 1
        }

        // Rule 60
        // CONDITION
        if ( 
            SAPInformer_road.is_on           == true                 &&       // Premise 1
            PLO_road.pm25_status             == "Severe"             &&       // Premise 2
            PLO_road.pm10_status 	         == "Severe")		              // Premise 3
            
        // ACTION
        {
            SAPInformer_road.pm_pollution_alert_onSpot("Severe");            // Instigation 1
        }

        // Rule 61
        // CONDITION
        if ( 
            SAPInformer_center.is_on           == true                 &&       // Premise 1
            PLO_center.pm25_status             == "Excellent"          &&       // Premise 2
            PLO_center.pm10_status 	           == "Excellent") 		            // Premise 3
            
        // ACTION
        {
            SAPInformer_center.pm_pollution_alert_onSpot("Excellent");          // Instigation 1
        }

        // Rule 62
        // CONDITION
        if ( 
            SAPInformer_center.is_on           == true             &&       // Premise 1
            PLO_center.pm25_status             == "Fine"           &&       // Premise 2
            PLO_center.pm10_status 	           == "Fine")		            // Premise 3
            
        // ACTION
        {
            SAPInformer_center.pm_pollution_alert_onSpot("Fine");          // Instigation 1
        }

        // Rule 63
        // CONDITION
        if ( 
            SAPInformer_center.is_on           == true                 &&       // Premise 1
            PLO_center.pm25_status             == "Moderate"           &&       // Premise 2
            PLO_center.pm10_status 	           == "Moderate")		            // Premise 3
            
        // ACTION
        {
            SAPInformer_center.pm_pollution_alert_onSpot("Moderate");          // Instigation 1
        }

        // Rule 64
        // CONDITION
        if ( 
            SAPInformer_center.is_on           == true                 &&       // Premise 1
            PLO_center.pm25_status             == "Poor"               &&       // Premise 2
            PLO_center.pm10_status 	           == "Poor")		                // Premise 3
            
        // ACTION
        {
            SAPInformer_center.pm_pollution_alert_onSpot("Poor");              // Instigation 1
        }

        // Rule 65
        // CONDITION
        if ( 
            SAPInformer_center.is_on           == true                 &&       // Premise 1
            PLO_center.pm25_status             == "Very Poor"          &&       // Premise 2
            PLO_center.pm10_status 	           == "Very Poor")		            // Premise 3
            
        // ACTION
        {
            SAPInformer_center.pm_pollution_alert_onSpot("Very Poor");          // Instigation 1
        }

        // Rule 66
        // CONDITION
        if ( 
            SAPInformer_center.is_on           == true                 &&       // Premise 1
            PLO_center.pm25_status             == "Severe"             &&       // Premise 2
            PLO_center.pm10_status 	           == "Severe")		                // Premise 3
            
        // ACTION
        {
            SAPInformer_center.pm_pollution_alert_onSpot("Severe");            // Instigation 1
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
  
        exec_time += duration.count();
        //cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
    }
    cout << "Total Time taken by CPP: "<< exec_time << " milliseconds" << endl;
    cout << "Counter = " << cnt << endl;
    fin_c.close();
    fin_r.close();
    fin_u.close();
    double mem = getMemoryUsage()/(1024.0 * 1024.0);
    cout << "Total Memory taken by CPP: "<< mem << " megabytes" << endl;
    return 0;
}