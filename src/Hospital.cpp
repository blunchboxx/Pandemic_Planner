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

WeeklyStats::WeeklyStats(string date, string month, double total, double occupied, double covid) {
    inpatientBeds = total;
    occupiedInpatientBeds = occupied;
    covidInpatientBeds = covid;
    percentCapacityUsed = occupiedInpatientBeds / inpatientBeds * 100;
    percentCapacityCovid = covidInpatientBeds / inpatientBeds * 100;
    collectionDate = date;
    collectionMonth = month;
}

bool WeeklyStats::operator==(const WeeklyStats rhs) const
{
    bool isSame = false;

    if ((this->inpatientBeds == rhs.getInpatientBeds())
        && (this->occupiedInpatientBeds == rhs.getOccupiedInpatientBeds())
        && (this->covidInpatientBeds == rhs.getCovidInpatientBeds()))
    {
        isSame = true;
    }
    return isSame;
}

double WeeklyStats::getInpatientBeds() const {
    return inpatientBeds;
}

double WeeklyStats::getOccupiedInpatientBeds() const {
    return occupiedInpatientBeds;
}

double WeeklyStats::getCovidInpatientBeds() const {
    return covidInpatientBeds;
}

double WeeklyStats::getPercentCapacityUsed() const
{
    return percentCapacityUsed;
}
double WeeklyStats::getCovidCapacityUsed() const
{
    return percentCapacityCovid;
}
    
//Hospital
Hospital::Hospital()
{
    hospital_pk = "pk";
    name = "Default";
    zip = "000000";
    subtype = "none";
    geoCoords = make_pair(-1,-1);
}

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

    // If all hospital attributes are equal, objects are equal
    if ((this->hospital_pk == rhs.getHospitalPK())&&(this->name == rhs.getName())&&(this->zip == rhs.getZip())
        &&(this->subtype == rhs.getSubtype())&&(this->geoCoords.first == rhs.getGeoCoords().first)
        &&((this->geoCoords.second == rhs.getGeoCoords().second))&&(this->ordered_monthly_data == rhs.ordered_monthly_data))
    {
        isSame = true;
    }
    return isSame;
}

bool Hospital::operator<(const Hospital& rhs) const
{
    // TODO implement method to compare weekly stats between hospitals
    return hospital_pk > rhs.hospital_pk;
}

void Hospital::addWeeklyStats(const string& date, const WeeklyStats& stats){
    ordered_monthly_data[date].push_back(stats);
    unordered_monthly_data[date].push_back(stats);
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

map<string, vector<WeeklyStats>>& Hospital::getOrderedStatsMap()
{
    return ordered_monthly_data;
}

unordered_map<string,vector<WeeklyStats>>& Hospital::getUnorderedStatsMap()
{
    return unordered_monthly_data;
}

map<string, vector<WeeklyStats>> const & Hospital::getOrderedStatsMap() const
{
    return ordered_monthly_data;
}
unordered_map<string, vector<WeeklyStats>> const & Hospital::getUnorderedStatsMap() const
{
    return unordered_monthly_data;
}

// TODO Update to return vector of weekly stats
// If date wasn't found, a default Weekly Stats object is created and returned.
WeeklyStats Hospital::getOrderedMonthlyStats(const string& date) const {
    auto it = ordered_monthly_data.find(date);
    return it->second[0]; // (it != ordered_monthly_data.end()) ? it->second : WeeklyStats();
}

WeeklyStats Hospital::getUnorderedMonthlyStats(const string& date) const {
    auto it = unordered_monthly_data.find(date);
    return it->second[0]; //(it != unordered_monthly_data.end()) ? it->second : WeeklyStats();
}
