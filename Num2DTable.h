//
// Created by Jonas on 07.04.2018.
//

#ifndef WORLDDOMINATION_QVALUES_H
#define WORLDDOMINATION_QVALUES_H

#include <vector>
#include <tuple>
#include <utility>

using namespace std;

class Num2DTable {

    vector<double> values;
    pair<int,int> * shape;

    int getIndex(pair<int,int> indexPair) {
        return indexPair.first * shape->second + indexPair.second;
    }

public:

    Num2DTable(pair<int,int> * size) {
        shape = size;
        values = vector<double> (size->first * size->second);
    }

    Num2DTable(pair<int,int> *size, vector<double> values) {
        shape = size;
        this->values = values;
    }

    Num2DTable() {}

    double operator[](const pair<int,int> index) {
        return values[getIndex(index)];
    }

    void setQValue(pair<int, int> index, double value) {
        values[getIndex(index)] = value;
    }



};


#endif //WORLDDOMINATION_QVALUES_H
