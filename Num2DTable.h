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
    pair<int,int> shape;

    int getIndex(pair<int,int> indexPair) {
        return indexPair.second*shape.first+indexPair.first;
    }

public:

    Num2DTable(pair<int,int> size) {
        shape = size;
        int indexLength = size.first * size.second;
        values = vector<double> (indexLength);
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
