#include <iomanip>
#include <regex>
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
void retrieveData(unordered_map<string, unordered_map<string, Hospital>>& map, vector<string> dates, vector<string> states)
{
    string hospitalPK;

    for (auto state : states)
    {
        for (auto date : dates)
        {
            for (auto hospital : map[state])
            {
                // TODO implement method to retrieve and store weekly stats and compare to find largest
            }
        }
    }
}

bool validateState(string command)
{
    auto const validCommands = regex("\\bFL\\b|\\bGA\\b|\\bAL\\b|\\bMS\\b|\\bTN\\b|\\bSC\\b|\\bNC\\b");
    return regex_match(command, validCommands);
}

void printMenu()
{
    cout << "Select state(s) to analyze: \n";
    cout << "1. FL\n2. GA\n3. AL\n4. MS\n5. TN\n6. SC\n7. NC\n";
}

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
    cout << "Number of states imported: " << stateMap.size() << "\n";
    cout << "Number of hospitals in FL: " << stateMap["FL"].size() << "\n";

    //data.printData(dataMap);
    //data.printDataNew(stateMap);

    /*for (auto state : stateMap)
    {
        cout << state.first << ": " << state.second.size() << " hospitals.\n";
    }*/

    int selection = 0;
    cout << "Make program selections (enter -1 to exit): \n";
    cin >> selection;
    cout << endl;

    while (selection != -1)
    {
        string input;
        string date;
        vector<string> states, dates;
        printMenu();
        cin >> input;

        cout << endl << "Input month and year to view (e.g. May 2020)\n";
        cin >> date;
        cout << endl;

        states.push_back(input);

        dates.push_back(date);

        retrieveData(stateMap, dates, states);
    }


    return 0;
}
