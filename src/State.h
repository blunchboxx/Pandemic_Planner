//
// Created by Jason on 11/16/2024.
//

#ifndef STATE_H
#define STATE_H
#include <unordered_map>
#include "Hospital.h"
using namespace std;


class State {

    string _name;
    unordered_map<string, Hospital> _hospitals;

public:
    // Constructors
    State();
    State(string name);

    // Operator Overloading
    State& operator=(const State& other);
    bool operator==(const State& rhs) const;

    // Functions
    void addHospital(string pk, Hospital& newHospital);

    // Getters
    unordered_map<string, Hospital>& getMap();
    unordered_map<string, Hospital> const & getMap() const;
    string getName() const;

};



#endif //STATE_H
