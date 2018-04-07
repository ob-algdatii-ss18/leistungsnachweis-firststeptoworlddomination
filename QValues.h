//
// Created by Jonas on 07.04.2018.
//

#ifndef WORLDDOMINATION_QVALUES_H
#define WORLDDOMINATION_QVALUES_H

#include <vector>
#include <tuple>
#include <utility>

using namespace std;

class QValues {

    vector<double> qValues;//@todo could be a simple list too
    pair<int,int> shape;

    int getIndex(pair<int,int> indexPair) {
        return indexPair.second*shape.first+indexPair.first;
    }

public:

    QValues(pair<int,int> size) {
        shape = size;
        int indexLength = size.first * size.second;
        qValues = vector<double> (indexLength);
    }

    //@todo shouldn't be necessary
    QValues() {}

    double operator[](const pair<int,int> index) {
        return qValues[getIndex(index)];
    }

    void setQValue(pair<int, int> index, double value) {
        qValues[getIndex(index)] = value;
    }

};


#endif //WORLDDOMINATION_QVALUES_H
