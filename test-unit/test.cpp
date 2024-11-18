#include <valarray>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "State.h"
#include "Hospital.h"
#include <catch2/internal/catch_preprocessor_internal_stringify.hpp>
#include "catch2/catch_test_macros.hpp"
#include "catch2/internal/catch_compiler_capabilities.hpp"
#include "catch2/internal/catch_decomposer.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/internal/catch_test_macro_impl.hpp"
#include "catch2/internal/catch_test_registry.hpp"
using namespace std;
#define CATCH_CONFIG_MAIN

/*
    To check output (At the maze_escape directory):
        g++ -std=c++14 -Werror -Wuninitialized -o test test-unit/test.cpp && ./test
*/

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

            string stateName = tempVector[2];

            // Check if State already exists
            if (dataMap.find(stateName) == dataMap.end()) // If not, create state object and add to state map
            {
                State newState(stateName); // Instantiate new state object
                dataMap.emplace(stateName, newState);
            }

            State currState = dataMap[stateName];
            string currPK = tempVector[0];
            // Check if hospital already exists
            if (currState.getMap().find(currPK) == currState.getMap().end()) // If not, create hospital object
            {
                // TODO parse geocoords = tempVector[96]
                Hospital newHospital(currPK, tempVector[4], tempVector[7], tempVector[8], 0.0, 0.0);
            }
            // Todo Add stats to hospital weekly stats map

        }
    }
}

TEST_CASE("Test: CATCH 2 CONFIG CHECK", "[given]")
{
    int actualOutput = 0;
    int expectedOutput = 0;

    REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Test: ReadFile", "[given]")
{
    ifstream file;
    string path = "test-data/testFile1.csv";

    State Florida("FL");
    State Alabama("AL");

    unordered_map<string, State> actualOutput;
    unordered_map<string, State> expectedOutput = {{"FL", Florida}, {"AL", Alabama}};

    readFile(file, path, actualOutput);

    REQUIRE(actualOutput == expectedOutput);
}
