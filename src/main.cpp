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
#include <chrono>
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
                // Check if hospital has data in a given month
                if (hospital.second.getUnorderedMonthStatsMap().find(date) != hospital.second.getUnorderedMonthStatsMap().end())
                {
                    double capacity_used = hospital.second.getUnorderedMonthStatsMap()[date].getPercentCapacityUsed();
                    //double capacity_used_ordered = hospital.second.getOrderedMonthStatsMap()[date].getPercentCapacityUsed();
                    pair<double, string> nextHos = make_pair(capacity_used, hospital.first);
                    pq.push((nextHos)); // Add each capacity-hospital pair to queue
                }
            }
        }
        // Take top 10 hospitals only and add to return vector
        while (!pq.empty() && hospitalVector.size() < 10) {
            string hospitalPK = pq.top().second;
            hospitalVector.push_back(hospitalMap[state][hospitalPK]);

            pq.pop();
        }
    }
    return hospitalVector;
}
vector<Hospital> retrieveDataOrdered(unordered_map<string, unordered_map<string, Hospital>>& hospitalMap, vector<string> dates,
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
                // Check if hospital has data in a given month
                if (hospital.second.getOrderedMonthStatsMap().find(date) != hospital.second.getOrderedMonthStatsMap().end())
                {
                    double capacity_used = hospital.second.getOrderedMonthStatsMap()[date].getPercentCapacityUsed();

                    pair<double, string> nextHos = make_pair(capacity_used, hospital.first);
                    pq.push((nextHos)); // Add each capacity-hospital pair to queue
                }
            }
        }
        // Take top 10 hospitals only and add to return vector
        while (!pq.empty() && hospitalVector.size() < 10) {
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

    // Start timer for data import
    typedef chrono::high_resolution_clock Clock;
    typedef chrono::milliseconds milliseconds;
    Clock::time_point startTime = Clock::now();

    // Map of all imported data
    unordered_map<string, unordered_map<string, Hospital>> stateMap;

    dataInput data;
    ifstream dataFile;
    // Changed working directory to the parent of the executable
    //filesystem::current_path(filesystem::path(argv[0]).parent_path());
    string path = "../data/COVID-19_Data_scrubbed_no99999.csv";

    // Import all data
    data.readFile(dataFile, path, stateMap);

    // End timer for import and display elapsed time
    Clock::time_point endTime = Clock::now();
    milliseconds elapsedTime = chrono::duration_cast<milliseconds>(endTime - startTime);

    cout << "Elapsed time: " << elapsedTime.count() << " milliseconds.\n";
    cout << "Number of states imported: " << stateMap.size() << "\n";
    cout << "Number of hospitals in FL: " << stateMap["FL"].size() << "\n";

    //------------ TIME EXPERIMENT START ---------------
    // Experiment with timing ordered and unordered data retrieval
    vector<string> test_dates = {"Jul-2020", "Aug-2020", "Sep-2020", "Oct-2020", "Nov-2020", "Dec-2020"};
    vector<string> test_states = {"FL"};

    Clock::time_point unordered_t0 = Clock::now();

    vector<Hospital> retrievedData = retrieveData(stateMap, test_dates, test_states);

    for (int i = 1; i < 10; i++)
    {
        retrievedData = retrieveDataOrdered(stateMap, test_dates, test_states);
    }

    Clock::time_point unordered_t1 = Clock::now();
    milliseconds unorderedTime = chrono::duration_cast<milliseconds>(unordered_t1 - unordered_t0);

    cout << "Elapsed time for UNORDERED data retrieval: " << unorderedTime.count() << " milliseconds.\n";

    Clock::time_point ordered_t0 = Clock::now();

    for (int i = 0; i < 10; i++)
    {
        retrievedData = retrieveDataOrdered(stateMap, test_dates, test_states);
    }

    Clock::time_point ordered_t1 = Clock::now();
    milliseconds orderedTime = chrono::duration_cast<milliseconds>(ordered_t1 - ordered_t0);

    cout << "Elapsed time for ORDERED data retrieval: " << orderedTime.count() << " milliseconds.\n";


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

    CROW_ROUTE(app, "/home")
    ([](const crow::request& req) {
        // Read the HTML file
        ifstream file("visuals/home.html");
        if (!file) {
        return crow::response(404, "HTML file not found");
        }

        stringstream buffer;
        buffer << file.rdbuf();

        // Create response with HTML content type
        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/html");
        return res;
    }); 

    CROW_ROUTE(app, "/css/home.css")
    ([](const crow::request& req) {
      ifstream file("visuals/css/home.css");
      if (!file) {
        return crow::response(404, "CSS file not found");
      }

      stringstream buffer;
      buffer << file.rdbuf();

      crow::response res(buffer.str());
      res.set_header("Content-Type", "text/css");
      return res;
   });


    CROW_ROUTE(app, "/js/home.js")
    ([](const crow::request& req) {
      std::ifstream file("visuals/js/home.js");
      if (!file) {
          return crow::response(404, "JS file not found");
      }

      stringstream buffer;
      buffer << file.rdbuf();

      crow::response res(buffer.str());
      res.set_header("Content-Type", "text/js");
      return res;
    });

   // Images:
   CROW_ROUTE(app, "/img/background.jpg")
   ([](const crow::request& req) {

   ifstream file("visuals/img/background.jpg", std::ios::binary);

   if (!file) {
       return crow::response(404, "Image not found");
   }

   std::stringstream buffer;
   buffer << file.rdbuf();

   crow::response res;
   res.add_header("Content-Type", "image/jpeg");
   res.write(buffer.str());
   return res;
       });

      // Alabama:
    CROW_ROUTE(app, "/img/Alabama.png")
        ([](const crow::request& req) {

        ifstream file("visuals/img/Alabama.png", std::ios::binary);

        if (!file) {
            return crow::response(404, "Image not found");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        crow::response res;
        res.add_header("Content-Type", "image/png");
        res.write(buffer.str());
        return res;
            });

    // Florida:
    CROW_ROUTE(app, "/img/Florida.png")
        ([](const crow::request& req) {

        ifstream file("visuals/img/Florida.png", std::ios::binary);

        if (!file) {
            return crow::response(404, "Image not found");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        crow::response res;
        res.add_header("Content-Type", "image/png");
        res.write(buffer.str());
        return res;
            });

     // Fresh_States:
    CROW_ROUTE(app, "/img/fresh_states.png")
        ([](const crow::request& req) {

        ifstream file("visuals/img/fresh_states.png", std::ios::binary);

        if (!file) {
            return crow::response(404, "Image not found");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        crow::response res;
        res.add_header("Content-Type", "image/png");
        res.write(buffer.str());
        return res;
            });

        // Georgia:
    CROW_ROUTE(app, "/img/Georgia.png")
        ([](const crow::request& req) {

        ifstream file("visuals/img/Georgia.png", std::ios::binary);

        if (!file) {
            return crow::response(404, "Image not found");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        crow::response res;
        res.add_header("Content-Type", "image/png");
        res.write(buffer.str());
        return res;
            });
    
      // Mississippi:
    CROW_ROUTE(app, "/img/Mississippi.png")
        ([](const crow::request& req) {

        ifstream file("visuals/img/Mississippi.png", std::ios::binary);

        if (!file) {
            return crow::response(404, "Image not found");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        crow::response res;
        res.add_header("Content-Type", "image/png");
        res.write(buffer.str());
        return res;
            });


    // North Carolina:
    CROW_ROUTE(app, "/img/North_Carolina.png")
        ([](const crow::request& req) {

        ifstream file("visuals/img/North_Carolina.png", std::ios::binary);

        if (!file) {
            return crow::response(404, "Image not found");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        crow::response res;
        res.add_header("Content-Type", "image/png");
        res.write(buffer.str());
        return res;
            });

    // South Carolina:
    CROW_ROUTE(app, "/img/South_Carolina.png")
        ([](const crow::request& req) {

        ifstream file("visuals/img/South_Carolina.png", std::ios::binary);

        if (!file) {
            return crow::response(404, "Image not found");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        crow::response res;
        res.add_header("Content-Type", "image/png");
        res.write(buffer.str());
        return res;
            });

   // Tennessee:
    CROW_ROUTE(app, "/img/Tennessee.png")
        ([](const crow::request& req) {

        ifstream file("visuals/img/Tennessee.png", std::ios::binary);

        if (!file) {
            return crow::response(404, "Image not found");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        crow::response res;
        res.add_header("Content-Type", "image/png");
        res.write(buffer.str());
        return res;
            });
  
    // Start the server on port 8080
    app.port(8080).run();
    
    return 0;
}
