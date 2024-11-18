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

    void addHospital(string pk, Hospital newHospital);

};



#endif //STATE_H
