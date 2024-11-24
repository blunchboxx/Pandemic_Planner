//
// Created by Jason on 11/19/2024.
//

#ifndef DATAINPUT_H
#define DATAINPUT_H
#include "Hospital.h"


struct dataInput {

    string validateDate(string date);
    void readFile(ifstream& file, string path, unordered_map<string, State>& dataMap);
    void readFileSet(ifstream& file, string path, unordered_map<string, unordered_set<Hospital, HospitalHash>>& dataSet);

    void printData(unordered_map<string, State>& dataMap);

};



#endif //DATAINPUT_H
