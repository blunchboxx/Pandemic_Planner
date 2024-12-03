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
//commenting the line below out since the header file is not actually included in git; i'm assuming this is no longer necessary -st 11/29
#include "Hospital.h"
#include "dataInput.h"

string dataInput::validateDate(string date)
{

    // List all selectable months in a vector
    vector<string> validMonths = 
    {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Split the string into month and year
    istringstream iss(date);
    string month, year;

    // If string is not processed in the proper order
    if (!(iss >> month >> year)) 
       { return "Invalid date format or string processed incorrectly"; }

    // Validate the month by checking if it exists in the validMonths list
    if (std::find(validMonths.begin(), validMonths.end(), month) == validMonths.end()) 
       { return "Invalid month selected."; }

    // Convert year string to integer and ensure it is a date that can be reflected in the COVID data
    try 
    {
        int yearInt = stoi(year);
        if (yearInt < 2019 || yearInt > 2100) { return "Invalid year, must be after 2019"; }
    }
    catch (...) 
      { return "Invalid year format."; }

    string monthDate = "";
    return monthDate;
}
string dataInput::calculateMonth(string date)
{
    string::size_type end = date.length() - 1;//date[-1];
    string::size_type start = date.length() - 8;
    string monthDate = date.substr(start, end);

    return monthDate;
}

void dataInput::readFile(ifstream& file, string path, unordered_map<string, unordered_map<string, Hospital>>& dataMap)
{
    file.open(path);

    if (!file.is_open())
        cout << "File could not be opened to read." << endl;
    else
    {
        cout << "Reading data from file..." << endl;

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
                count++;
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
            double currTotalBeds = stod(tempVector[10]);
            double currTotalBedsUsed = stod(tempVector[11]);
            double currTotalCovidBeds = stod(tempVector[12]);
            string date = tempVector[1];
            string month = calculateMonth(date);

            if (currTotalCovidBeds < 0) { currTotalCovidBeds = 0; }

            // Create new weekly stats object
            WeeklyStats newWeek(date, month, currTotalBeds, currTotalBedsUsed, currTotalCovidBeds);

            // Add weekly stats to hospital object
            dataMap[stateName][currPK].addWeeklyStats(month, newWeek);

            // Clear vector for next line
            //tempVector.clear();
            //ss.clear();
        }
        file.close();
    }
}

void dataInput::printData(unordered_map<string, unordered_map<string, Hospital>>& dataMap)
{
    cout << "Outputting Data: \n";

    for(auto state : dataMap)
    {
        cout << "State Name: " << state.first << "\n";

        for (auto hospital : state.second)
        {
            cout << "Hospital Name: " << hospital.second.getName() << "\n";

            for (auto month : hospital.second.getOrderedStatsMap())
            {
                cout << "Data for month of " << month.first << "\n";
                cout << "Capacity used: " << month.second.getPercentCapacityUsed() << "\n";

                /*- - - - REMOVING THE BELOW - - - - - */
                /*for (auto week : month.second)
                {
                    cout << "Total number of bed: " << week.getInpatientBeds() << "\n";
                    cout << "Total number of occupied beds: " << week.getOccupiedInpatientBeds() << "\n";
                    cout << "Total number of COVID occupied beds: " << week.getCovidInpatientBeds() << "\n";
                }*/
            }
        }
    }
}
