#include <iostream>
#include "Agent.h"
#include "Policy.h"
#include "googletest/include/gtest/gtest.h"
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    Agent a = Agent(0.1, 0.8, new SoftMaxPolicy(), new Environment());
    a.fit(1000);
    cout << "main done" << endl;
    return 0;
}