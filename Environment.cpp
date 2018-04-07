//
// Created by jonas on 4/4/18.
//

#include "Environment.h"
#include <tuple>

using namespace std;

tuple<int, int> Environment::initialState() {
    //tuple <int,int> result = {0,0};
    //return result;
    return make_tuple(0,0);
}

Environment::Response Environment::step(int action) {
    return Environment::Response();
}

