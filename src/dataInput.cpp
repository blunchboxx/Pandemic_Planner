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
#include "MemoryMapped.h"
#include "State.h"
#include "Hospital.h"
#include "dataInput.h"

string dataInput::validateDate(string date)
{
    // TODO: implement function to parse data and confirm it is valid
    string monthDate = "";
    return monthDate;
}

/*void dataInput::readFileSet(ifstream& file, string path, unordered_map<string, unordered_set<pair<string, Hospital>, HospitalHash>>& dataSet)
{
    file.open(path);

    if (!file.is_open())
        cout << "File could not be opened to read." << endl;
    else
    {
        cout << "Reading data from file..." << endl;
        //char buffer[256000];
        //file.rdbuf()->pubsetbuf(buffer, sizeof(buffer));
        vector<string> tempVector(20, "");
        string newLine;
        int count = 0;

        getline(file, newLine);  // Get and discard header row

        while (getline(file, newLine)) // Read in all lines of file
        {

            string token = "";
            stringstream ss(newLine); // Send next line to stream

            while (getline(ss, token, ','))  // Loop through entire line
            {
                tempVector[count] = token;
                //cout << count << " ";
                count++;
                //tempVector.push_back(token); // Add each data value to vector
            }

            count = 0;

            string stateName = tempVector[2]; // Get state of current line

            // Check if State already exists
            if (dataSet.find(stateName) == dataSet.end()) // If not, create state object and add to state map
            {
                unordered_set<pair<string, Hospital>> newSet; // Instantiate new Hospital set
                dataSet.insert(stateName);
            }

            string currPK = tempVector[0]; // Get hospital ID of current line

            // Check if hospital already exists
            // TODO try set of pairs <pk, Hospital>
            if (dataSet[stateName].find() == dataSet[stateName].getMap().end()) // If not, create hospital object
            {
                // TODO parse geocoords = tempVector[96]
                Hospital newHospital(currPK, tempVector[4],
                    tempVector[7], tempVector[8], 0.0, 0.0);

                dataSet[stateName].getMap().emplace(currPK, newHospital);
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
            dataSet[stateName].getMap()[currPK].addWeeklyStats(currDate, newWeek);

            // Clear vector for next line
            //tempVector.clear();
            //ss.clear();
        }
        file.close();
    }
}*/

void dataInput::readFileNew(ifstream& file, string path, unordered_map<string, unordered_map<string, Hospital>>& dataMap)
{
    file.open(path);

    if (!file.is_open())
        cout << "File could not be opened to read." << endl;
    else
    {
        cout << "Reading data from file..." << endl;
        //char buffer[256000];
        //file.rdbuf()->pubsetbuf(buffer, sizeof(buffer));
        vector<string> tempVector(20, "");
        string newLine;
        int count = 0;

        getline(file, newLine);  // Get and discard header row

        while (getline(file, newLine)) // Read in all lines of file
        {
            //cout << "Reading new line...\n";

            string token = "";
            stringstream ss(newLine); // Send next line to stream

            while (getline(ss, token, ','))  // Loop through entire line
            {
                tempVector[count] = token;
                //cout << token << " ";
                //cout << count << " ";
                count++;
                //tempVector.push_back(token); // Add each data value to vector
            }

            count = 0;

            string stateName = tempVector[2]; // Get state of current line

            if (dataMap.find(stateName) == dataMap.end()) // If state not in map, add it
            {

                string currPK = tempVector[0];
                //cout << "Adding state " << stateName << " and hospital " << currPK << "\n";

                // TODO parse geocoords = tempVector[96]
                Hospital newHospital(currPK, tempVector[4],
                    tempVector[7], tempVector[8], 0.0, 0.0);

                unordered_map<string, Hospital> newMap;
                newMap.emplace(currPK, newHospital); // Create new hospital submap for state

                dataMap.emplace(stateName, newMap); // Insert new state and hospital map
            }

            string currPK = tempVector[0]; // Get hospital ID of current line

            // Check if hospital already exists
            if (dataMap[stateName].find(currPK) == dataMap[stateName].end()) // If not, create hospital object
            {
                // TODO parse geocoords = tempVector[96]
                Hospital newHospital(currPK, tempVector[4],
                    tempVector[7], tempVector[8], 0.0, 0.0);

                //cout << "Creating new hospital " << tempVector[4] << "\n";
                dataMap[stateName].emplace(currPK, newHospital);
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
            dataMap[stateName][currPK].addWeeklyStats(currDate, newWeek);

            // Clear vector for next line
            //tempVector.clear();
            //ss.clear();
        }
        file.close();
    }
}

void dataInput::readFile(ifstream& file, string path, unordered_map<string, State>& dataMap)
{

    file.open(path);

    if (!file.is_open())
        cout << "File could not be opened to read." << endl;
    else
    {
        cout << "Reading data from file..." << endl;
        //char buffer[256000];
        //file.rdbuf()->pubsetbuf(buffer, sizeof(buffer));
        vector<string> tempVector(20, "");
        string newLine;
        int count = 0;

        getline(file, newLine);  // Get and discard header row

        while (getline(file, newLine)) // Read in all lines of file
        {

            string token = "";
            stringstream ss(newLine); // Send next line to stream

            while (getline(ss, token, ','))  // Loop through entire line
            {
                tempVector[count] = token;
                //cout << count << " ";
                count++;
                //tempVector.push_back(token); // Add each data value to vector
            }

            count = 0;

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

            // Clear vector for next line
            //tempVector.clear();
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
        cout << "State Name: " << state.first << "\n";

        for (auto hospital : state.second.getMap())
        {
            cout << "Hospital Name: " << hospital.second.getName() << "\n";

            for (auto week : hospital.second.getOrderedStatsMap())
            {
                cout << "Data for week of " << week.first << "\n";
                cout << "Total number of bed: " << week.second.getInpatientBeds() << "\n";
                cout << "Total number of occupied beds: " << week.second.getOccupiedInpatientBeds() << "\n";
                cout << "Total number of COVID occupied beds: " << week.second.getCovidInpatientBeds() << "\n";
            }
        }
    }
}

void dataInput::printDataNew(unordered_map<string, unordered_map<string, Hospital>>& dataMap)
{
    cout << "Outputting Data: \n";

    for(auto state : dataMap)
    {
        cout << "State Name: " << state.first << "\n";

        for (auto hospital : state.second)
        {
            cout << "Hospital Name: " << hospital.second.getName() << "\n";

            for (auto week : hospital.second.getOrderedStatsMap())
            {
                cout << "Data for week of " << week.first << "\n";
                cout << "Total number of bed: " << week.second.getInpatientBeds() << "\n";
                cout << "Total number of occupied beds: " << week.second.getOccupiedInpatientBeds() << "\n";
                cout << "Total number of COVID occupied beds: " << week.second.getCovidInpatientBeds() << "\n";
            }
        }
    }
}