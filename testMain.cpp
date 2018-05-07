//
// Created by Jonas on 16.04.2018.
//
#include <iostream>
#include "Agent.h"
#include <gtest/gtest.h>
#include <vector>

using namespace std;

Agent agent = Agent(0.1, 0.8, new ThresholdPolicy(0.8), new Environment());
pair<int, int> *initialState;
// up, right, down, left
vector<int> possibleActions {0, 1, 2, 3};

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
TEST(AgentTest, ChooseActionOfMaxValue)
{
    initialState = new pair<int, int>{1, 1};
    /* <maxValue, action>
     pair<double, int> *expected = new pair<double, int> {4, 3}; */
    // action 3 because max Value is 4
    int expected = 3;
    vector<double> values {1,2,3,4};
    EXPECT_EQ(expected, agent.policy->chooseAction(possibleActions, values));
}

int main(int argc, char* argv[]) {
    cout << "start tests" << endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
