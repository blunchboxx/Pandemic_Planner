#ifndef HOSPITAL_H
#define HOSPITAL_H
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class WeeklyStats {
private:
    double inpatientBeds;
    double occupiedInpatientBeds;
    double covidInpatientBeds;
    double percentCapacityUsed;
    double percentCapacityCovid;
    string collectionDate, collectionMonth;

public:
    // Default constructor
    WeeklyStats();

    // Parameterized constructor
    WeeklyStats(string date, string month, double total, double occupied, double covid);

    // Equality operator overload
    bool operator==(const WeeklyStats rhs) const;

    // Comparison operator overload
    bool operator<(const WeeklyStats rhs) const;

    // Getters
    double getInpatientBeds() const;
    double getOccupiedInpatientBeds() const;
    double getCovidInpatientBeds() const;
    double getPercentCapacityUsed() const;
    double getCovidCapacityUsed() const;
    string const & getMonth() const;

};


class Hospital {
private:
    string hospital_pk;
    string name;
    string zip;
    string subtype;
    int numWeeksOverThreshold = 0;
    pair<double, double> geoCoords;
    map<string, WeeklyStats> ordered_weekly_data;
    unordered_map<string, WeeklyStats> unordered_weekly_data;
    map<string, WeeklyStats> ordered_monthly_data;
    unordered_map<string, WeeklyStats> unordered_monthly_data;

public:
    // Constructors
    Hospital();
    Hospital(const string& pk, const string& hospitalName, const string& zipCode, const string& hospitalSubtype, double x, double y);

    // Equality operator overload
    bool operator==(const Hospital& rhs) const;

// Commenting this out for now since I don't think it does anything.
    // // Comparison operator overload
    // bool operator<(const Hospital& rhs) const;

    // Adding weekly data
    void addWeeklyStats(const string& date, const WeeklyStats&);

    // Getter for hospital_pk to check if it's the same hospital
    string getHospitalPK() const;

    // Getters that we'll need for visualization and data display
    string getName() const;
    string getZip() const;
    string getSubtype() const;
    pair<double, double> getGeoCoords() const;

    // Weekly stats Write Access Getters
    map<string, WeeklyStats>& getOrderedStatsMap();
    unordered_map<string, WeeklyStats>& getUnorderedStatsMap();
    map<string, WeeklyStats>& getOrderedMonthStatsMap();
    unordered_map<string, WeeklyStats>& getUnorderedMonthStatsMap();

    // Weekly stats CONST Getters
    map<string, WeeklyStats> const & getOrderedStatsMap() const;
    unordered_map<string, WeeklyStats> const & getUnorderedStatsMap() const;
    WeeklyStats getOrderedWeeklyStats(const string& date) const;
    WeeklyStats getUnorderedWeeklyStats(const string& date) const;
    map<string, WeeklyStats> const & getOrderedMonthStatsMap() const;
    unordered_map<string, WeeklyStats> const & getUnorderedMonthStatsMap() const;
};

// Hash function for Hospital objects
struct HospitalHash
{
    size_t operator()(const Hospital& hospital) const
    {
        size_t h1 = hash<string>{}(hospital.getName());
        size_t h2 = hash<string>{}(hospital.getHospitalPK());

        return h1 ^ (h2 << 1); // combine hashes
    }
};


#endif //HOSPITAL_H
