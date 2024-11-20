//
// Created by Jason on 11/19/2024.
//
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <stdexcept>
#include "State.h"
#include "Hospital.h"
#include "dataInput.h"

int dataInput::validateData()
{
    // TODO: implement function to parse data and confirm it is valid
    return 0;
}

void dataInput::readFile(ifstream& file, string path, unordered_map<string, State>& dataMap)
{

    file.open(path);

    if (!file.is_open())
        cout << "File could not be opened to read." << endl;
    else
    {
        cout << "Reading data from file..." << endl;
        string newLine;

        getline(file, newLine);  // Get and discard header row

        while (getline(file, newLine)) // Read in all lines of file
        {

            vector<string> tempVector;
            string token = "";
            stringstream ss(newLine); // Send next line to stream

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
            if (dataMap[stateName].getMap().find(currPK) == dataMap[stateName].getMap().end()) // If not, create hospital object
            {
                // TODO parse geocoords = tempVector[96]
                Hospital newHospital(currPK, tempVector[4],
                    tempVector[7], tempVector[8], 0.0, 0.0);

                dataMap[stateName].getMap().emplace(currPK, newHospital);
            }
            // Todo Add stats to hospital weekly stats map
            // Get collection date and weekly data
            string currDate = tempVector[1];

            double currTotalBeds = stod(tempVector[10]);
            double currTotalBedsUsed = stod(tempVector[11]);
            double currTotalCovidBeds = stod(tempVector[12]);

            if (currTotalCovidBeds < 0)
                currTotalCovidBeds = 0;

            // Create new weekly stats object
            WeeklyStats newWeek(currTotalBeds, currTotalBedsUsed, currTotalCovidBeds);

            // Add weekly stats to hospital object
            dataMap[stateName].getMap()[currPK].addWeeklyStats(currDate, newWeek);

            // TODO: add exception handling for string to int
            /*string currTotalBeds = tempVector[11];
            cout << currTotalBeds << endl;*/
            /*try
            {
            int currTotalBeds = stoi(tempVector[10]);
            int currTotalBedsUsed = stoi(tempVector[11]);
            int currTotalCovidBeds = stoi(tempVector[12]);

                int currTotalBeds = stoi(tempVector[11]);
                int currTotalBedsUsed = stoi(tempVector[14]);
                int currTotalCovidBeds = stoi(tempVector[16]);

                // Create new weekly stats object
                WeeklyStats newWeek(currTotalBeds, currTotalBedsUsed, currTotalCovidBeds);

                // Add weekly stats to hospital object
                dataMap[stateName].getMap()[currPK].addWeeklyStats(currDate, newWeek);
            }
            catch (const exception& e)
            {
                cout << "Exception: " << e.what() << endl;
            }*/
            // Clear vector for next line
            tempVector.clear();
            //ss.clear();
        }
        file.close();
    }
}

void dataInput::printData(unordered_map<string, State>& dataMap)
{
    cout << "Outputting Data: \n";

    for(auto state : dataMap)
    {
        cout << "State Name: " << state.first << endl;

        for (auto hospital : state.second.getMap())
        {
            cout << "Hospital Name: " << hospital.second.getName() << endl;

            for (auto week : hospital.second.getOrderedStatsMap())
            {
                cout << "Data for week of " << week.first << endl;
                cout << "Total number of bed: " << week.second.getInpatientBeds() << endl;
                cout << "Total number of occupied beds: " << week.second.getOccupiedInpatientBeds() << endl;
                cout << "Total number of COVID occupied beds: " << week.second.getCovidInpatientBeds() << endl;
            }
        }
    }
}