#include <iostream>
#include "Agent.h"
//#include "gtest/gtest.h"

using namespace std;

int main() {
    Agent a = Agent(0.003, 0.9, 0.8);
    a.fit(14);
    cout << "main done" << endl;
    return 0;
}