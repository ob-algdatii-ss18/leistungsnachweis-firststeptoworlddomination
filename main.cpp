#include <iostream>
#include "Agent.h"
#include <gtest.h>

using namespace std;

int main() {
    Agent a = Agent(0.40, 0.9, 0.8);
    a.fit(110);
    cout << "main done" << endl;
    return 0;
}