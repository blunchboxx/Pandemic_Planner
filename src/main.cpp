#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <State.h>
#include <Hospital.h>
#include <filesystem>

#include "Hospital.h"
using namespace std;
//namespace fs = std::filesystem;

void readFile(ifstream& file, string path, unordered_map<string, State>& dataMap)
{
    map<float, float> dataValuesMap;

    file.open(path);

    if (!file.is_open())
        cout << "File could not be opened to read." << endl;
    else
    {
        cout << "Reading data from file..." << endl;
        string newLine, token;
        vector<string> tempVector;

        getline(file, newLine);  // Get and discard header row

        while (getline(file, newLine)) // Read in all lines of file
        {
            istringstream ss(newLine); // Send next line to stream

            while (getline(ss, token, ','))  // Loop through entire line
            {
                tempVector.push_back(token); // Add each data value to vector
            }

            string stateName = tempVector[2]; // Get state of current line

            // Check if State already exists
            if (dataMap.find(stateName) == dataMap.end()) // If not, create state object and add to state map
            {
                State newState(stateName); // Instantiate new state object
                dataMap.emplace(stateName, newState);
            }

            State currState = dataMap[stateName]; // Get current State object
            string currPK = tempVector[0]; // Get hospital ID of current line

            // Check if hospital already exists
            if (currState.getMap().find(currPK) == currState.getMap().end()) // If not, create hospital object
            {
                // TODO parse geocoords = tempVector[96]
                Hospital newHospital(currPK, tempVector[4],
                    tempVector[7], tempVector[8], 0.0, 0.0);

                currState.getMap()[currPK] = newHospital;
            }
            // Todo Add stats to hospital weekly stats map
            // Get collection date and weekly data
            string currDate = tempVector[1];
            int currTotalBeds = stoi(tempVector[11]);
            int currTotalBedsUsed = stoi(tempVector[14]);
            int currTotalCovidBeds = stoi(tempVector[16]);

            // Create new weekly stats object
            WeeklyStats newWeek(currTotalBeds, currTotalBedsUsed, currTotalCovidBeds);

            // Add weekly stats to hospital object
            currState.getMap()[currPK].addWeeklyStats(currDate, newWeek);

            // Clear vector for next line
            tempVector.clear();
        }
        file.close();
    }
}

int main()
{
    unordered_map<string, State> dataMap;
    ifstream dataFile;
    string path ="test-data\\testFile1.csv";
        //"data\\COVID-19_Data.csv";

    readFile(dataFile, path, dataMap);

    return 0;
}
