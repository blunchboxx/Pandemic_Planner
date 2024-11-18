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
#include <WeeklyStats.h>
#include <filesystem>

#include "Hospital.h"
using namespace std;
namespace fs = std::filesystem;

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

            // Check if State already exists
            if (dataMap.find(tempVector[2]) == dataMap.end()) // If state DNE, add it
            {
                State newState; // Instantiate new state object: TODO add params
                dataMap.try_emplace(tempVector[2], newState);
            }
            // If not, create state object and add to state ordered and unordered maps
            // Check if hospital already exists
            // If not, create hospital object
            // Add stats to hospital weekly stats map

        }

        /*TestSample nextSample(sampleNum, dataValuesMap, xValues, yValues);// // Instantiate new Test Sample object

        testObjectList.push_back(nextSample); // Add object to vector*/

    }
}

int main()
{
    unordered_map<string, State> dataMap;
    ifstream dataFile;
    string path = "data\\COVID-19_Data.csv";

    readFile(dataFile, path, dataMap);

    return 0;
}
