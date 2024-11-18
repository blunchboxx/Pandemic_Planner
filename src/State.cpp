//
// Created by Jason on 11/16/2024.
//

#include "State.h"

#include <iostream>

// Constructors
State::State()
{
    _name = "Placeholder";
}
State::State(string name)
{
    _name = name;
}

void State::addHospital(string pk, Hospital newHospital)
{
    if(_hospitals.find(pk) == _hospitals.end())
    {
        _hospitals.try_emplace(pk, newHospital);
    }
    else
        cout << "Hospital already in state list\n";
}