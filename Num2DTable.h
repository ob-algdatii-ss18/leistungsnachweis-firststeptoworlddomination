#ifndef WORLDDOMINATION_QVALUES_H
#define WORLDDOMINATION_QVALUES_H

#include <vector>
#include <tuple>
#include <utility>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class Num2DTable {

    /**
     * calculates the int index for the value vector from a given pair<row, column>
     * @param indexPair
     * @return int index
     */
    int getIndex(pair<int,int> indexPair) {
        if(!keyExists(indexPair)) {
            cout << "key does not exist " << indexPair.first << " " << indexPair.second << endl;
            throw 20;
        }
        return indexPair.first * shape.second + indexPair.second;
    }
/**
 * stores all values
 */
    vector<double> values;

public:

    /**
     * the shape<row, column>
     */
    pair<int,int> shape;

    /**
     * constructor initializing table with a given size
     * @param size
     */
    explicit Num2DTable(pair<int,int> size) {
        shape = pair<int,int>(size);
        int length = shape.first * shape.second;
        values = vector<double> (length);
        for (int i = 0; i < length; i++) {
            values[i] = 0;
        }
    }

    /**
     * constructor initializing table with a given size and values
     * @param size
     * @param values
     */
    Num2DTable(pair<int,int> size, vector<double> values) {
        shape = pair<int,int>(size);
        this->values = vector<double> (values);
    }

    /**
     * default constructor
     */
    Num2DTable() = default;

    /**
     * defines operator [] to be able to get values from vector with given pair indices
     * @param index pair
     * @return wanted value
     */
    double operator[](const pair<int,int> index) {
        return values[getIndex(index)];
    }

    /**
     * defines operater == for testing purposes
     * @param rhs
     * @return true or false
     */
    bool operator==(const Num2DTable& rhs) const {
       // return shape == rhs.shape && values == rhs.values;

        if (values.size() != rhs.values.size()){
            cout << "\nSize does not match" <<endl;
            return false;
        }
        if (shape.first != rhs.shape.first || shape.second != rhs.shape.second){
            return false;
        }
        for (int i = 0; i < values.size(); i++){
            if( fabs(values[i] - rhs.values[i]) > 0.00000001 ){
                cout.precision(17);
                cout << "First wrong value at index " << i << ": " << fixed << values[i] << " and " << rhs.values[i] <<"\n" << endl;
                return false;
            }
        }
        return true;
        }

/*    bool operator!=(const Num2DTable& rhs) const {
        return !(*this == rhs);
    }*/

    /*void operator(const pair<int,int> index, values) {
        values[getIndex(index)] = value;
    }*/

    /**
     * stores a given value into the value vector at given pair index
     * @param index pair
     * @param value
     */
    void setQValue(pair<int, int> index, double value) {
        values[getIndex(index)] = value;
    }

    /**
     * checks if the given index pair is within the table
     * @param indexPair
     * @return true or false
     */
    bool keyExists(pair<int, int> indexPair) {
        return indexPair.first < shape.first && indexPair.second < shape.second
               && indexPair.first >= 0 && indexPair.second >= 0;
    }

/**
 * Num2DTable as string
 * @return Num2DTable as string
 */
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
