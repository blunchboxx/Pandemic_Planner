//
// Created by Jason on 11/16/2024.
//

#include "Hospital.h"
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

//Weekly Stats

WeeklyStats::WeeklyStats() {
        inpatientBeds = 0;
        occupiedInpatientBeds = 0;
        covidInpatientBeds = 0;
}

WeeklyStats::WeeklyStats(int total, int occupied, int covid) {
        inpatientBeds = total;
        occupiedInpatientBeds = occupied;
        covidInpatientBeds = covid;
}

int WeeklyStats::getInpatientBeds() const {
    return inpatientBeds;
}

int WeeklyStats::getOccupiedInpatientBeds() const {
    return occupiedInpatientBeds;
}

int WeeklyStats::getCovidInpatientBeds() const {
    return covidInpatientBeds;
}
    
//Hospital

Hospital::Hospital(const string& pk, const string& hospitalName, const string& zipCode,
    const string& hospitalSubtype, double x, double y) {
    hospital_pk = pk;
    name = hospitalName;
    zip = zipCode;
    subtype = hospitalSubtype;
    geoCoords = make_pair(x,y);
}

bool Hospital::operator==(const Hospital& rhs) const
{
    bool isSame = false;

    if ((this->hospital_pk == rhs.getHospitalPK())&&(this->name == rhs.getName())&&(this->zip == rhs.getZip())
        &&(this->subtype == rhs.getSubtype())&&(this->geoCoords.first == rhs.getGeoCoords().first)
        &&((this->geoCoords.second == rhs.getGeoCoords().second)))
    {
        isSame = true;
    }
    return isSame;
}

void Hospital::addWeeklyStats(const string& date, const WeeklyStats& stats){
    ordered_weekly_data[date] = stats;
    unordered_weekly_data[date] = stats;
}

string Hospital::getHospitalPK() const {
    return hospital_pk;
}

string Hospital::getName() const {
    return name;
}

string Hospital::getZip() const {
    return zip;
}

string Hospital::getSubtype() const {
    return subtype;
}

pair<double, double> Hospital::getGeoCoords() const {
    return geoCoords;
}

// If date wasn't found, a default Weekly Stats object is created and returned.
WeeklyStats Hospital::getOrderedWeeklyStats(const string& date) const {
    auto it = ordered_weekly_data.find(date);
    return (it != ordered_weekly_data.end()) ? it->second : WeeklyStats();
}

WeeklyStats Hospital::getUnorderedWeeklyStats(const string& date) const {
    auto it = unordered_weekly_data.find(date);
    return (it != unordered_weekly_data.end()) ? it->second : WeeklyStats();
}
