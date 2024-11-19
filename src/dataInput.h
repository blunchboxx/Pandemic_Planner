//
// Created by Jason on 11/19/2024.
//

#ifndef DATAINPUT_H
#define DATAINPUT_H



struct dataInput {

    int validateData();
    void readFile(ifstream& file, string path, unordered_map<string, State>& dataMap);
    void printData(unordered_map<string, State>& dataMap);

};



#endif //DATAINPUT_H
