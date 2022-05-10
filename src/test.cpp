#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;


int main()
{

    // File pointer
    fstream fin_u, fin_c, fin_r;
  
    // Open an existing file
    fin_c.open("CityCenter.csv");
    fin_r.open("RoadSide.csv");
    fin_u.open("University.csv");
    // Read the Data from the file
    // as String Vector
    vector<string> row_c, row_r, row_u;
    string line_c, line_u, line_r, word_c, word_r, word_u, temp_c, temp_u, temp_r;
    getline(fin_c, line_c);
    getline(fin_u, line_u);
    getline(fin_r, line_r);
    //cout << line_c << endl;
    //cout << line << endl;
    while (fin_c >> temp_c && fin_r >> temp_r && fin_u >> temp_u) {
  
        row_c.clear();
        row_r.clear();
        row_u.clear();
        
        stringstream c(temp_c), r(temp_r), u(temp_u);
        
        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(c, word_c, ';')) {
            getline(r, word_r, ';');
            getline(u, word_u, ';');
  
            // add all the column data
            // of a row to a vector
            row_c.push_back(word_c);
            row_r.push_back(word_r);
            row_u.push_back(word_u);
        }
        string p10 = row_c.at(6), p25 = row_c.at(7);
        float pm10 = stof(p10), pm25 = stof(p25);

        p10 = row_r.at(6), p25 = row_r.at(7);
        float pm10_1 = stof(p10), pm25_1 = stof(p25);

        p10 = row_u.at(6), p25 = row_u.at(7);
        float pm10_2 = stof(p10), pm25_2 = stof(p25);
        cout << "CityCenter" << endl;
        cout << pm10 << pm25 << endl;
        cout << "RoadSide" << endl;
        cout << pm10_1 << pm25_1 << endl;
        cout << "University" << endl;
        cout << pm10_2 << pm25_2 << endl;
    }
}