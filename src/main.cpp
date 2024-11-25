#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <ctime>
#include "MemoryMapped.h"
#include "State.h"
#include "Hospital.h"
#include "dataInput.h"
#include <filesystem>
using namespace std;
//namespace fs = std::filesystem;

// Try an unordered set of objects - good for searching for specific object
// Try mapping hospitals to their stats - eliminate weekly stats and make it attribute of hospital
// Each row could be singular object?
// Can create a database after data is parsed to reference

int main()
{

    time_t startTime = time(0);

    unordered_map<string, State> dataMap;
    unordered_map<string, unordered_map<string, Hospital>> stateMap;

    dataInput data;
    ifstream dataFile;
    string path = "C:\\dev\\COP3530\\Projects\\Project 3\\Pandemic_Planner\\data\\COVID-19_Data_scrubbed_no99999.csv";
        // Full path to test data file
        //"C:\\dev\\COP3530\\Projects\\Project 3\\Pandemic_Planner\\test-data\\testFile1.csv";
        //"data\\COVID-19_Data.csv";

    //data.readFile(dataFile, path, dataMap);
    data.readFileNew(dataFile, path, stateMap);
    //data.printData(dataMap);

    time_t endTime = time(0);
    double elapsedTime = difftime(endTime, startTime);

    cout << "Elapsed time: " << elapsedTime << " seconds.\n";

    //data.printData(dataMap);
    //data.printDataNew(stateMap);

    /*for (auto state : stateMap)
    {
        cout << state.first << ": " << state.second.size() << " hospitals.\n";
    }*/

    return 0;
}
