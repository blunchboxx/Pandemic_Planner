//
// Created by Jason on 11/16/2024.
//

#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;


class Hospital {
    string hospital_pk;
    string name;
    string zip;
    string subtype;
    pair<int, int> geoCoords;
    map<string, vector<double>> ordered_weekly_data;
    unordered_map<string, vector<double>> unordered_weekly_data;

public:
    // Constructors
    Hospital();

};



#endif //HOSPITAL_H
