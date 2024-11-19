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
    WeeklyStats();

    // Parameterized constructor
    WeeklyStats(int total, int occupied, int covid);

    // Equality operator overload
    bool operator==(const WeeklyStats rhs) const;

    // Getters
    int getInpatientBeds() const;
    int getOccupiedInpatientBeds() const;
    int getCovidInpatientBeds() const;

};

class Hospital {
private:
    string hospital_pk;
    string name;
    string zip;
    string subtype;
    pair<double, double> geoCoords;
    map<string, WeeklyStats> ordered_weekly_data;
    unordered_map<string, WeeklyStats> unordered_weekly_data;

public:
    // Constructors
    Hospital();
    Hospital(const string& pk, const string& hospitalName, const string& zipCode, const string& hospitalSubtype, double x, double y);

    // Equality operator overload
    bool operator==(const Hospital& rhs) const;

    // Adding weekly data
    void addWeeklyStats(const string& date, const WeeklyStats&);

    // Getter for hospital_pk to check if it's the same hospital
    string getHospitalPK() const;

    // Getters that we'll need for visualization and data display
    string getName() const;
    string getZip() const;
    string getSubtype() const;
    pair<double, double> getGeoCoords() const;
    // Weekly stats Getters
    map<string, WeeklyStats>& getOrderedStatsMap();
    unordered_map<string, WeeklyStats>& getUnorderedStatsMap();

    // Weekly stats CONST Getters
    map<string, WeeklyStats> const & getOrderedStatsMap() const;
    unordered_map<string, WeeklyStats> const & getUnorderedStatsMap() const;
    WeeklyStats getOrderedWeeklyStats(const string& date) const;
    WeeklyStats getUnorderedWeeklyStats(const string& date) const;
};



#endif //HOSPITAL_H
