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

State& State::operator=(const State& other)
{
    if (this != &other)
    {
        //TODO finish copy assignment operator
    }
    return *this;
}

bool State::operator==(const State& rhs) const
{
    bool isSame = false;
    if ((this->getName() == rhs.getName()) && (this->getMap() == rhs.getMap()))
    {
        isSame = true;
    }
    return isSame;
}

void State::addHospital(string pk, Hospital& newHospital)
{
    if(_hospitals.find(pk) == _hospitals.end())
    {
        _hospitals.emplace(pk, newHospital);
    }
    else
        cout << "Hospital already in state list\n";
}

unordered_map<string, Hospital> State::getMap() const
{
    return _hospitals;
}
string State::getName() const
{
    return _name;
}