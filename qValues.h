//
// Created by Jonas on 16.04.2018.
//

#ifndef WORLDDOMINATION_QVALUES_H
#define WORLDDOMINATION_QVALUES_H

#include <utility>
#include <vector>

using namespace std;

class QValues {
    pair<int,int> shape;
    int actionSpace = 4;
    vector< vector < vector<double> > > qValues;

    QValues(pair<int,int> shape, int actionSpace) {
        this->actionSpace = actionSpace;
        this->shape = shape;

        //fills the qValues Tensor with zeros
        for(int i = 0; i < shape.first; i++) {
            vector<vector<int > > tmp_vec_1 {};
            for(int j; j < shape.second; j++) {
                vector<int> tmp_vec_2 {};
                for (int k = 0; k < actionSpace; k++) {
                    tmp_vec_2.push_back(0.0);
                }
                tmp_vec_1.push_back(tmp_vec_2);
            }
            qValues.push_back(tmp_vec_1);
        }
    }

    double operator[](const pair<int,int> index, int action) {
        return qValues[index.first][index.second][action];
    }

    void setValue(const pair<int,int> index, int action, double value) {
        qValues[index.first][index.second][action] = value;
    }

};


#endif //WORLDDOMINATION_QVALUES_H
