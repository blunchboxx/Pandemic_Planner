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

class WeeklyStats {
private:
    int inpatientBeds;
    int occupiedInpatientBeds;
    int covidInpatientBeds;

public:
    // Default constructor
    WeeklyStats(){
        inpatientBeds = 0;
        occupiedInpatientBeds = 0;
        covidInpatientBeds = 0;

    // Parameterized constructor
    WeeklyStats(int total, int occupied, int covid){
        inpatientBeds = total;
        occupiedInpatientBeds = occupied;
        covidInpatientBeds = covid;

    // Getters
    int getInpatientBeds() const (return inpatientBeds);
    int getOccupiedInpatientBeds() const (return occupiedInpatientBeds);
    int getCovidInpatientBeds() const (return covidInpatientBeds);
    }
}

class Hospital {
private:
    string hospital_pk;
    string name;
    string zip;
    string subtype;
    pair<int, int> geoCoords;
    map<string, WeeklyStats> ordered_weekly_data;
    unordered_map<string, WeeklyStats> unordered_weekly_data;

public:
    // Constructors
    // Going to come back to this part.
    Hospital(string hospitalID, string hospitalName, string hospitalZipcode, string hospitalSubtype, pair<int, int> HospitalGeoCoords);

    // Adding weekly data
    void addWeeklyStats(const string& date, const WeeklyStats&)

    // I am still working on this. :) 
};



#endif //HOSPITAL_H
