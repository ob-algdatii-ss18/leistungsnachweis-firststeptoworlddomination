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
        if(!keyExists(indexPair)) {
            cout << "crap " << indexPair.first << " " << indexPair.second << endl;
            throw 20;
        }
        return indexPair.first * shape.second + indexPair.second;
    }

    vector<double> values;

public:

    pair<int,int> shape;

    Num2DTable(pair<int,int> size) {
        shape = pair<int,int>(size);
        int length = shape.first * shape.second;
        values = vector<double> (length);
        for (int i = 0; i < length; i++) {
            values[i] = 0;
        }
    }

    Num2DTable(pair<int,int> size, vector<double> values) {
        shape = pair<int,int>(size);
        this->values = vector<double> (values);
    }

    Num2DTable() {}

    double operator[](const pair<int,int> index) {
        return values[getIndex(index)];
    }

    /*void operator(const pair<int,int> index, values) {
        values[getIndex(index)] = value;
    }*/

    void setQValue(pair<int, int> index, double value) {
        values[getIndex(index)] = value;
    }

    // needed for google tests
    void setQValues(pair<int, int> *agentIndex, double values[]){
        //up
        setQValue({agentIndex->first-1, agentIndex->second},values[0]);
        //right
        setQValue({agentIndex->first, agentIndex->second+1},values[1]);
        //down
        setQValue({agentIndex->first+1, agentIndex->second},values[2]);
        //left
        setQValue({agentIndex->first, agentIndex->second-1},values[3]);
    }

    bool keyExists(pair<int, int> indexPair) {
        return indexPair.first < shape.first && indexPair.second < shape.second
               && indexPair.first >= 0 && indexPair.second >= 0;
    }


    string toString() {
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
