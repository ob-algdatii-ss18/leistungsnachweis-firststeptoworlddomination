#include <iostream>
#include "Agent.h"


using namespace std;

int main() {
    Agent a = Agent(0.01, 0.9, 0.8);
    a.fit(10);
    cout << "main done" << endl;
    return 0;
}