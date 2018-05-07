#include <iostream>
#include "Agent.h"
//#include "Policy.h"
#include "googletest/include/gtest/gtest.h"
#include <cmath>
//#include <armadillo/include/armadillo>


using namespace std;
//using namespace arma;

int main(int argc, char* argv[]) {
    //mat A = randu<mat>(4,5);
    Agent a = Agent(0.1, 0.8, 0.8, 0);
    a.fit(1000);
    cout << "main done" << endl;
    return 0;
}