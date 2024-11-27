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

// ToDo add additional stats to comparison
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

// Return true if week's percentage capacity used is greater than rhs
bool WeeklyStats::operator<(const WeeklyStats rhs) const
{
    return percentCapacityUsed > rhs.percentCapacityUsed;
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
string const & WeeklyStats::getMonth() const
{
    return collectionMonth;
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

// ToDo update to include comparison of weekly data
bool Hospital::operator==(const Hospital& rhs) const
{
    bool isSame = false;

    // If all hospital attributes are equal, objects are equal
    if ((this->hospital_pk == rhs.getHospitalPK())&&(this->name == rhs.getName())&&(this->zip == rhs.getZip())
        &&(this->subtype == rhs.getSubtype()))
        //&&(this->geoCoords.first == rhs.getGeoCoords().first)&&((this->geoCoords.second == rhs.getGeoCoords().second))&&(this->ordered_weekly_data == rhs.ordered_weekly_data))
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
    ordered_weekly_data[date] = stats;
    unordered_weekly_data[date] = stats;

    // If new week is greater than previous greatest week in month, replace with new week
    string month = stats.getMonth();
    if (stats.getPercentCapacityUsed() > unordered_monthly_data[month].getPercentCapacityUsed())
    {
        unordered_monthly_data[month] = stats;
    }
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

map<string, WeeklyStats>& Hospital::getOrderedStatsMap()
{
    return ordered_weekly_data;
}

unordered_map<string,WeeklyStats>& Hospital::getUnorderedStatsMap()
{
    return unordered_weekly_data;
}

map<string, WeeklyStats> const & Hospital::getOrderedStatsMap() const
{
    return ordered_weekly_data;
}
unordered_map<string, WeeklyStats> const & Hospital::getUnorderedStatsMap() const
{
    return unordered_weekly_data;
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
