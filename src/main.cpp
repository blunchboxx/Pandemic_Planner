#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include "State.h"
#include "Hospital.h"
#include "dataInput.h"
#include <filesystem>
using namespace std;
//namespace fs = std::filesystem;


int main()
{
    unordered_map<string, State> dataMap;
    dataInput data;
    ifstream dataFile;
    string path = "C:\\dev\\COP3530\\Projects\\Project 3\\Pandemic_Planner\\data\\COVIDTEST.csv";
        // Full path to test data file
        //"C:\\dev\\COP3530\\Projects\\Project 3\\Pandemic_Planner\\test-data\\testFile1.csv";
        //"data\\COVID-19_Data.csv";

    data.readFile(dataFile, path, dataMap);
    data.printData(dataMap);

    return 0;
}
