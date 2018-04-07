//
// Created by jonas on 4/4/18.
//

#include "Environment.h"

using namespace std;

pair<int, int> Environment::initialState() {
    //tuple <int,int> result = {0,0};
    //return result;
    return {0,0};//make_tuple(0,0);
}

Environment::Response Environment::step(int action) {
    return Environment::Response();
}

void Environment::visualizeGame() {

}

