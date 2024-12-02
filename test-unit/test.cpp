#include <valarray>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
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
vector<Hospital> retrieveData(unordered_map<string, unordered_map<string, Hospital>>& hospitalMap, vector<string> dates,
    vector<string> states)
{
    //vector<string> hospitals;
    vector<Hospital> hospitalVector;
    priority_queue<pair<double, string>> pq;

    for (auto state : states)
    {
        for (auto date : dates)
        {
            for (auto hospital : hospitalMap[state])
            {
                // TODO implement method to retrieve and store weekly stats and compare to find largest
                WeeklyStats newMonth = hospital.second.getUnorderedMonthStatsMap()[date];
                pair<double, string> nextHos = make_pair(hospital.second.getUnorderedMonthStatsMap()[date].getPercentCapacityUsed(),
                    hospital.first);
                pq.push((nextHos));
            }
        }
        for (int i = 0; i < 10; i++)
        {
            while (!pq.empty() && hospitalVector.size() < 10) {
                string hospitalPK = pq.top().second;
                hospitalVector.push_back(hospitalMap[state][hospitalPK]);
                pq.pop();
            }
        }
    }
    return hospitalVector;
}

TEST_CASE("Test: CATCH 2 CONFIG CHECK", "[given]")
{
    int actualOutput = 0;
    int expectedOutput = 0;

    REQUIRE(actualOutput == expectedOutput);
}

// ToDo check that weekly and monthly data is being stored correctly
TEST_CASE("Test: ReadFile", "[given]")
{
    ifstream file;
    dataInput data;
    string path = "C:\\dev\\COP3530\\Projects\\Project 3\\Pandemic_Planner\\test-data\\testFile1.csv";

    Hospital hos1("010001", "SOUTHEAST HEALTH MEDICAL CENTER", "36301", "Short Term", 0.0, 0.0);
    Hospital hos2("100299", "LAKEWOOD RANCH MEDICAL CENTER", "34202", "Short Term", 0.0, 0.0);

    WeeklyStats week1("19-Jul-2020", "Jul-2020",401.4, 324.4, 49);
    WeeklyStats week2("15-Aug-2021", "Aug-2021",115.7, 113.6, 54);
    hos1.addWeeklyStats("Jul-2020", week1);
    hos2.addWeeklyStats("Aug-2021", week2);

    unordered_map<string, Hospital> ALhospitalMap, FLhospitalMap;

    ALhospitalMap.emplace(hos1.getHospitalPK(), hos1);
    FLhospitalMap.emplace(hos2.getHospitalPK(), hos2);

    unordered_map<string, unordered_map<string, Hospital>> actualOutput;
    map<string, unordered_map<string, Hospital>> expectedOutput;
    map<string, unordered_map<string, Hospital>> actualOutput2;

    expectedOutput.emplace("FL", FLhospitalMap);
    expectedOutput.emplace("AL", ALhospitalMap);

    data.readFile(file, path, actualOutput);

    for (auto object : actualOutput)
    {
        cout << "Storing state " << object.first << "\n";
        actualOutput2.emplace(object);
    }
    /*for(auto state : actualOutput)
    {
        cout << "State Name: " << state.first << endl;

        for (auto hospital : state.second)
        {
            cout << "Hospital Name: " << hospital.second.getName() << endl;

            for (auto week : hospital.second.getOrderedWeeklyStats())
            {

            }#1#
        }
    }*/

    cout << "MONTHLY STATS TEST - ExpectedOutput: \n";

    for (auto output : expectedOutput)
    {
        cout << output.first << "\n";
        for (auto hos : output.second)
        {
            cout << "Size of monthly data stored " << hos.second.getOrderedMonthStatsMap().size() << "\n";
            cout << hos.second.getName() << " ";
            for (auto month_data : hos.second.getOrderedMonthStatsMap())
            {
                cout << month_data.first << " " << month_data.second.getPercentCapacityUsed() << "\n";
            }
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "MONTHLY STATS TEST - ActualOutput: \n";
    for (auto output : actualOutput2)
    {
        cout << output.first << "\n";
        for (auto hos : output.second)
        {
            cout << hos.second.getName() << " ";
            for (auto month_data : hos.second.getOrderedMonthStatsMap())
            {
                cout << month_data.first << " " << month_data.second.getPercentCapacityUsed() << "\n";
            }
        }
        cout << "\n";
    }

    REQUIRE(actualOutput2 == expectedOutput);
}

TEST_CASE("Test: Month Calculator", "[given]")
{
    dataInput data;
    string dateInput = "27-Sep-2020";
    string actualOutput = data.calculateMonth(dateInput);
    string expectedOutput = "Sep-2020";

    REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Test: retrieveData", "[given]")
{
    // Map of all imported data
    unordered_map<string, unordered_map<string, Hospital>> stateMap;

    dataInput data;
    ifstream dataFile;
    // Changed working directory to the parent of the executable

    string path ="C:\\dev\\COP3530\\Projects\\Project 3\\Pandemic_Planner\\data\\COVID-19_Data_scrubbed_no99999.csv";

    // Import all data
    data.readFile(dataFile, path, stateMap);

    vector<string> dates = {"Sep-2020"};
    vector<string> states = {"AL"};
    vector<Hospital> testOutput = retrieveData(stateMap, dates, states);

    vector<string> actualOutput;
    vector<string> expectedOutput =
    { {"012009"},
    {"012012"},
    {"010087"},
    {"012007"},
    {"012011"},
    {"012014"},
    {"010078"},
    {"010001"},
    {"010033"},
    {"010040"}
    };
    /*vector<pair<string, double>> actualOutput;
    vector<pair<string, double>> expectedOutput =
        { {"012009", 92.5},
        {"012012", 89.5238},
        {"010087", 88.4862},
        {"012007", 87.1428},
        {"012011", 85},
        {"012014", 83.5},
        {"010078", 82.3004},
        {"010001", 81.9684},
        {"010033", 81.10219445},
        {"010040", 80.85728203}
        };*/

    for (auto hospital : testOutput)
    {
        actualOutput.push_back(hospital.getHospitalPK());
    }

    cout << "Size of hospital vector: " << testOutput.size() << endl;
    cout << "Size of output vector: " << actualOutput.size() << endl;

    /*for (auto item : actualOutput)
    {
        cout << item.first << " " << item.second << "%\n";
    }*/
    REQUIRE(actualOutput == expectedOutput);
}
