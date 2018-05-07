//
// Created by Jonas on 16.04.2018.
//
#include <iostream>
#include "Agent.h"
#include <gtest/gtest.h>

using namespace std;

Agent agent = Agent(0.1, 0.8, 1, nullptr);
pair<int, int> *initialState;
// up, right, down, left
double values[4] = {0,1,2,3};


/*// Test Fixture
struct AgentTest : testing::Test
{
    Agent agent = Agent(0.1, 0.8, 0.8, 1);;
    AgentTest() {
    }

    ~AgentTest()
    {
        delete agent;
    }
};*/
// TODO grössere Werte aussen rum
TEST(AgentTest, FirstMaxValueMustBeZero)
{
    initialState = new pair<int, int>{1, 1};
    agent.valueFunction.setQValues(initialState, values);
    /*pair<int, int> testAtUp = pair<int, int>{initialState->first-1, initialState->second};
    agent.valueFunction.setQValue(testAtUp, 1);
    pair<int, int> testAtRight = pair<int, int>{initialState->first, initialState->second+1};
    agent.valueFunction.setQValue(testAtRight, 2);
    pair<int, int> testAtDown = pair<int, int>{initialState->first+1, initialState->second};
    agent.valueFunction.setQValue(testAtDown, 3);
    pair<int, int> testAtLeft = pair<int, int>{initialState->first, initialState->second-1};
    agent.valueFunction.setQValue(testAtLeft, 4);*/
    // <maxValue, action>
    pair<double, int> *expected = new pair<double, int>{3, 3};
    EXPECT_EQ(*expected, *(agent.maxExpected(initialState, nullptr)));
}
/*TEST(AgentTest, HigherMaxValueOnRightSide)
{
    //pair<int, int> *initialState = new pair<int, int>{2, 0};


//    pair<double, int> *expected = new pair<double, int>{0.3, 1};
//    EXPECT_EQ(*expected, *(agent.maxExpected(initialState)));
}*/

int main(int argc, char* argv[]) {
    cout << "start tests" << endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
