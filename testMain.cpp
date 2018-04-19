//
// Created by Jonas on 16.04.2018.
//
#include <iostream>
#include "Agent.h"
#include <gtest/gtest.h>

using namespace std;

int main(int argc, char* argv[]) {
    cout << "start tests" << endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
