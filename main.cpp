#include <iostream>
#include "Agent.h"


using namespace std;

int main() {
    Agent a = Agent(0.1, 0.9, 0.8);
    a.fit(1);

    return 0;
}