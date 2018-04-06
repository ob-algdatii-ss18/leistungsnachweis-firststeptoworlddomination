#include <iostream>
#include "Agent.h"
#include "Environment.h"

using namespace std;

int main() {
    cout << "Hello, World!" << std::endl;
    Agent a = Agent(0.1,0.1);
    a.test();
    return 0;
}