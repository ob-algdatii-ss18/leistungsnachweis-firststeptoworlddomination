#include <iostream>
#include "Agent.h"
#include "Policy.h"
#include "googletest/include/gtest/gtest.h"
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    Policy* policy = new SoftMaxPolicy();
    Agent a = Agent(0.1, 0.8, 0.8, policy);
    a.fit(1000);
    cout << "main done" << endl;
    return 0;
}