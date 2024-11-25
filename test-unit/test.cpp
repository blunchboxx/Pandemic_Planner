#include <valarray>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "State.h"
#include "Hospital.h"
#include "dataInput.h"
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

TEST_CASE("Test: CATCH 2 CONFIG CHECK", "[given]")
{
    int actualOutput = 0;
    int expectedOutput = 0;

    REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Test: ReadFile", "[given]")
{
    ifstream file;
    dataInput data;
    string path = "C:\\dev\\COP3530\\Projects\\Project 3\\Pandemic_Planner\\test-data\\testFile1.csv";

    Hospital hos1("010001", "SOUTHEAST HEALTH MEDICAL CENTER", "36301", "Short Term", 0.0, 0.0);
    Hospital hos2("100299", "LAKEWOOD RANCH MEDICAL CENTER", "34202", "Short Term", 0.0, 0.0);

    WeeklyStats week1(401, 324, 49);
    WeeklyStats week2(115, 113, 54);
    hos1.addWeeklyStats("7/19/2020", week1);
    hos2.addWeeklyStats("8/15/2021", week2);

    unordered_map<string, Hospital> ALhospitalMap, FLhospitalMap;

    ALhospitalMap.emplace(hos1.getHospitalPK(), hos1);
    FLhospitalMap.emplace(hos2.getHospitalPK(), hos2);

    unordered_map<string, unordered_map<string, Hospital>> actualOutput;
    map<string, unordered_map<string, Hospital>> expectedOutput;
    map<string, unordered_map<string, Hospital>> actualOutput2;

    expectedOutput.emplace("FL", FLhospitalMap);
    expectedOutput.emplace("AL", ALhospitalMap);

    data.readFileNew(file, path, actualOutput);

    for (auto object : actualOutput)
    {
        actualOutput2.emplace(object);
    }
    for(auto state : actualOutput)
    {
        cout << "State Name: " << state.first << endl;

        for (auto hospital : state.second)
        {
            cout << "Hospital Name: " << hospital.second.getName() << endl;

            /*for (auto week : hospital.second.getOrderedWeeklyStats())
            {

            }*/
        }
    }

    REQUIRE(actualOutput2 == expectedOutput);
}
