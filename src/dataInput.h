//
// Created by Jason on 11/19/2024.
//

#ifndef DATAINPUT_H
#define DATAINPUT_H
#include "Hospital.h"
#include <regex>


struct dataInput {

    string validateDate(string date);
    string calculateMonth(string date);
    void readFile(ifstream& file, string path, unordered_map<string, State>& dataMap);
    void readFileNew(ifstream& file, string path, unordered_map<string, unordered_map<string, Hospital>>& dataMap);
    //void readFileSet(ifstream& file, string path, unordered_map<string, unordered_set<pair<string, Hospital>, HospitalHash>>& dataSet);

    void printData(unordered_map<string, State>& dataMap);
    void printDataNew(unordered_map<string, unordered_map<string, Hospital>>& dataMap);

};



#endif //DATAINPUT_H
