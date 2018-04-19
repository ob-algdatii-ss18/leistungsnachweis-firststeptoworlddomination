#include <iostream>
#include "Agent.h"
#include "googletest/include/gtest/gtest.h"
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    Agent a = Agent(0.1, 0.9, 0.8, 0);
    a.fit(100);
    cout << "main done" << endl;
    return 0;
}