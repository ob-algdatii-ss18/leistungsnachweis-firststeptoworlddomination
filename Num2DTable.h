//
// Created by Jonas on 07.04.2018.
//

#ifndef WORLDDOMINATION_QVALUES_H
#define WORLDDOMINATION_QVALUES_H

#include <vector>
#include <tuple>
#include <utility>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

class Num2DTable {

    int getIndex(pair<int,int> indexPair) {
        return indexPair.first * shape.second + indexPair.second;
    }

public:

    vector<double> values;
    pair<int,int> shape;

    Num2DTable(pair<int,int> * size) {
        shape = *size;
        values = vector<double> (size->first * size->second);
    }

    Num2DTable(pair<int,int> *size, vector<double> values) {
        shape = *size;
        this->values = values;
    }

    Num2DTable() {}

    double operator[](const pair<int,int> index) {
        return values[getIndex(index)];
    }

    void setQValue(pair<int, int> index, double value) {
        values[getIndex(index)] = value;
    }


    string toString() {
        cout << "shape: " << shape.first << " " << shape.second << endl;
        std::stringstream ss;
        /*for(int i = 0; i < shape->first; i++) {
            for(int j = 0; j < shape->second; j++) {
                ss << values[getIndex({i,j})] << "\t";
            }
            ss << endl;
        }*/
        std::string s = ss.str();
        return "";
    }
};


#endif //WORLDDOMINATION_QVALUES_H
