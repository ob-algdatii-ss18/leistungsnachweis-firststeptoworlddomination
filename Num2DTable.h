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
#include <iomanip>

using namespace std;

class Num2DTable {

    int getIndex(pair<int,int> indexPair) {
        if(indexPair.first > shape.first + 1|| indexPair.second > shape.second + 1) {
            cout << "crap " << indexPair.first << " " << indexPair.second << endl;
            throw 20;
        }
        return indexPair.first * shape.second + indexPair.second;
    }

public:

    vector<double> values;
    pair<int,int> shape;

    Num2DTable(pair<int,int> size) {
        shape = pair<int,int>(size);
        values = vector<double> (shape.first * shape.second);
    }

    Num2DTable(pair<int,int> size, vector<double> values) {
        shape = pair<int,int>(size);
        this->values = vector<double>(values);
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
        ss << setprecision(3) << fixed;
        for(int i = 0; i < shape.first; i++) {
            for(int j = 0; j < shape.second; j++) {
                ss << values[getIndex({i,j})] << "\t";
            }
            ss << endl;
        }
        //std::string s = ss.str();
        return ss.str();
    }
};


#endif //WORLDDOMINATION_QVALUES_H
