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
    vector<int> shape;

public:

    QValues(vector<int> size) {
        shape = size;
        int indexLength = 1;
        for(int i = 0; i < size.size(); i++)
            indexLength *= size[i];
        //qValues = vector<double> (size);
        qValues = {4,3};
    }

    QValues() {}

    double operator[](const pair<int,int> index) {
        int address = 0;//access the actual index by using the shape
        return qValues[address];
        //return qValues[i.first][i.second];
    }

    void setValue(pair<int, int> index, double value) {
        qValues[index.first+index.second] = value;//@todo index calculation is still wrong
    }
};


#endif //WORLDDOMINATION_QVALUES_H
