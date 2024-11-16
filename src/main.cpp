#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

void readFile(int sampleNum, string path, vector<TestSample>& testObjectList)
{
    ifstream csvFile;
    vector<float> xValues;
    vector<float> yValues;
    map<float, float> dataValuesMap;

    csvFile.open(path);

    if (!csvFile.is_open())
        cout << "File could not be opened to read." << endl;
    else
    {
        cout << "Reading data from file " << path << "..." << endl;
        string newLine, token;
        string tempArray[17];

        getline(csvFile, newLine);  // Get and discard header row

        int count = 0;

        while (getline(csvFile, newLine))
        {
            count = 0;

            istringstream ss(newLine); // Send next line to stream

            while (getline(ss, token, ','))  // Loop through entire stream
            {
                /*if (count < 4)
                {
                    cout << " Count: " << count << " token: " << token << endl;
                }*/

                if (count == 4) // Load (force) data
                {
                    yValues.push_back(stof(token));
                }

                /*else if (count > 4 && count < 8)
                {
                    continue;
                }*/

                else if (count == 8)
                {
                    xValues.push_back(stof(token));
                }

                count++;
            }

            for (int i = 0; i < xValues.size(); i++)
            {
                dataValuesMap.emplace(xValues[i], yValues[i]);
            }

        }

        TestSample nextSample(sampleNum, dataValuesMap, xValues, yValues);// // Instantiate new Test Sample object

        testObjectList.push_back(nextSample); // Add object to vector

    }
}

int main()
{
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
