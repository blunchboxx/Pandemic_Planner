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

    // Getters
    double getInpatientBeds() const;
    double getOccupiedInpatientBeds() const;
    double getCovidInpatientBeds() const;
    double getPercentCapacityUsed() const;
    double getCovidCapacityUsed() const;

};


class Hospital {
private:
    string hospital_pk;
    string name;
    string zip;
    string subtype;
    pair<double, double> geoCoords;
    map<string, vector<WeeklyStats>> ordered_monthly_data;
    unordered_map<string, vector<WeeklyStats>> unordered_monthly_data;

public:
    // Constructors
    Hospital();
    Hospital(const string& pk, const string& hospitalName, const string& zipCode, const string& hospitalSubtype, double x, double y);

    // Equality operator overload
    bool operator==(const Hospital& rhs) const;

    // Comparison operator overload
    bool operator<(const Hospital& rhs) const;

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
    map<string, vector<WeeklyStats>>& getOrderedStatsMap();
    unordered_map<string, vector<WeeklyStats>>& getUnorderedStatsMap();

    // Weekly stats CONST Getters
    map<string, vector<WeeklyStats>> const & getOrderedStatsMap() const;
    unordered_map<string, vector<WeeklyStats>> const & getUnorderedStatsMap() const;
    WeeklyStats getOrderedMonthlyStats(const string& date) const;
    WeeklyStats getUnorderedMonthlyStats(const string& date) const;
};

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
