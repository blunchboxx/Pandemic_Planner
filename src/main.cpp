#include <iomanip>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <queue>
#include <ctime>
//commenting the line below out since the header file is not actually included in git; i'm assuming this is no longer necessary -st 11/29
// #include "MemoryMapped.h"
#include "Hospital.h"
#include "dataInput.h"
#include <filesystem>
#include "crow_all.h"

#define ASIO_STANDALONE

using namespace std;
//namespace fs = std::filesystem;

// Try an unordered set of objects - good for searching for specific object
// Try mapping hospitals to their stats - eliminate weekly stats and make it attribute of hospital
// Each row could be singular object?
// Can create a database after data is parsed to reference
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
            string hospitalPK = pq.top().second;
            hospitalVector.push_back(hospitalMap[state][hospitalPK]);
            pq.pop();
        }
    }

    return hospitalVector;
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

// Helper function that formats the hospital list for the endpoint
string formatHospitalList(const vector<Hospital>& hospitals, const string& date) {
    stringstream response;
    for (const auto& hospital : hospitals) {
        const auto& monthStats = hospital.getUnorderedMonthStatsMap();
        // Check if the date is in the map before accessing it
        if (monthStats.find(date) != monthStats.end()) {
            response << hospital.getName() << " " 
                    << hospital.getZip() << ": " 
                << monthStats.at(date).getPercentCapacityUsed() 
                << "%\n";
        }
    }
    return response.str();
}

// I had to add argc and argv to main to get the current path to the data file
int main(int argc, char* argv[])
{
    crow::SimpleApp app;

    // Test endpoint
    // CROW_ROUTE(app, "/api/test")
    // ([]() {
    //     return "Hello World!";
    // });

    time_t startTime = time(0);

    // Map of all imported data
    unordered_map<string, unordered_map<string, Hospital>> stateMap;

    dataInput data;
    ifstream dataFile;
    // Changed working directory to the parent of the executable
    filesystem::current_path(filesystem::path(argv[0]).parent_path());
    string path = "../data/COVID-19_Data_scrubbed_no99999.csv";

    //string path = "../data/COVID-19_Data_scrubbed_no99999.csv";
    //cout << "Current path: " << filesystem::current_path() << endl;
    // string path = "C:\\dev\\COP3530\\Projects\\Project 3\\Pandemic_Planner\\data\\COVID-19_Data_scrubbed_no99999.csv";

    // Import all data
    data.readFile(dataFile, path, stateMap);

    time_t endTime = time(0);
    double elapsedTime = difftime(endTime, startTime);

    cout << "Elapsed time: " << elapsedTime << " seconds.\n";
    cout << "Number of states imported: " << stateMap.size() << "\n";
    cout << "Number of hospitals in FL: " << stateMap["FL"].size() << "\n";

    CROW_ROUTE(app, "/api/hospitals/capacity")
    .methods("GET"_method)
    ([&stateMap](const crow::request& req) {
        auto state = req.url_params.get("state");
        auto date = req.url_params.get("date");
    
        if (!state || !date || !validateState(string(state))) {
            return crow::response(400, "Invalid state or date parameter");
        }

        vector<string> states{state};
        vector<string> dates{date};
        vector<Hospital> hospitals = retrieveData(stateMap, dates, states);

        // Check if we got any results
        if (hospitals.empty()) {
            return crow::response(404, 
                "No data available for " + string(state) + " during " + string(date));
        }

        string response = formatHospitalList(hospitals, date);
        if (response.empty()) {
            return crow::response(404, 
                "No capacity data available for " + string(state) + " during " + string(date));
        }
    
        return crow::response(200, response);
    });

    // // Loop for menu and app selections
    // string selection = "0";
    // cout << "Make program selections (enter -1 to exit): \n";
    // cin >> selection;
    // cout << endl;

    // while (selection != "-1")
    // {
    //     string state;
    //     string date;
    //     vector<string> states, dates;
    //     vector<Hospital> hospitals;
    //     printMenu();
    //     cin >> state;
    //     while (!validateState(state))
    //     {
    //         cout << "Invalid selection. Try again: \n";
    //         cin >> state;
    //         cout << "\n";
    //     }

    //     cout << endl << "Input month and year to view (e.g. May-2020)\n";
    //     cin >> date;
    //     cout << endl;

    //     states.push_back(state);

    //     dates.push_back(date);

    //     hospitals = retrieveData(stateMap, dates, states);

    //     cout << "Hospitals with highest capacity used in " << state << " in " << date << ": \n";
    //     for (auto hospital : hospitals)
    //     {
    //         cout << hospital.getName() << " " << hospital.getZip() << ": " << hospital.getUnorderedMonthStatsMap()[date].getPercentCapacityUsed() << "%\n";
    //     }

    //     selection.clear();
    //     cout << "Do you wish to continue? (Enter -1 to exit)\n";
    //     cin >> selection;
    //     cout << '\n';
    // }


    // Start the server on port 8080
    app.port(8080).run();
    
    return 0;
}
