//
// Created by Jonas on 16.04.2018.
//
#include <iostream>
#include "Agent.h"
#include <gtest/gtest.h>
#include <vector>

using namespace std;

/*Agent agent = Agent(0.1, 0.8, new ThresholdPolicy(0.8), new Environment());
pair<int, int> *initialState;
// up, right, down, left
vector<int> possibleActions {0, 1, 2, 3};*/

// Test Fixture
struct AgentTest : public testing::Test
{
    Agent *agent;
    ThresholdPolicy *agentPolicy;
    //pair<int, int> initState;
    Num2DTable valueFunction;
    Environment *environment;
    void SetUp()
    {
        agent = new Agent(0.1, 0.8, new ThresholdPolicy(0.8), new Environment());
        //initState = pair<int, int>{1, 1};
        agentPolicy = (ThresholdPolicy*) agent->policy;
        valueFunction = agent->valueFunction;
        environment = agent->environment;
        environment->agentPosition = pair<int, int>{1, 1};
    }
    void TearDown()
    {
        delete agent;
    }
};

// -----------------------------------------------------------------------------

// Policy::maxExpected

// -----------------------------------------------------------------------------


// Put all MaxExpected tests as FRIEND_TEST in Thresholdpolicy, otherwise cant test maxExpected
TEST_F(AgentTest, GetMaxValueOf4PossibleActions_4)
{
    // up, right, down, left
    vector<int> possibleActions {0, 1, 2, 3};
    vector<double> values {1, 2, 3, 4};
    //valueFunction.setQValues(initState, values);
    double expected = 4;
    double actual = agentPolicy->maxExpected(possibleActions, values)->first;
    EXPECT_EQ(expected, actual);
}

TEST_F(AgentTest, GetMaxValueOf4PossibleActions_5)
{
    // up, right, down, left
    vector<int> possibleActions {0, 1, 2, 3};
    vector<double> values {1, 5, 3, 4};
    //valueFunction.setQValues(initState, values);
    double expected = 5;
    double actual = agentPolicy->maxExpected(possibleActions, values)->first;
    EXPECT_EQ(expected, actual);
}

// There are only as many values as possible actions
TEST_F(AgentTest, GetMaxValueOf3PossibleActions_4)
{
    // up, right, down
    vector<int> possibleActions {0, 1, 2};
    vector<double> values {1, 4, 3};
    //valueFunction.setQValues(initState, values);
    double expected = 4;
    double actual = agentPolicy->maxExpected(possibleActions, values)->first;
    EXPECT_EQ(expected, actual);
}

TEST_F(AgentTest, GetMaxValueOf3PossibleActions_5)
{
    // up, left
    vector<int> possibleActions {0, 3};
    vector<double> values {5, 1, 3};
    //valueFunction.setQValues(initState, values);
    double expected = 5;
    double actual = agentPolicy->maxExpected(possibleActions, values)->first;
    EXPECT_EQ(expected, actual);
}

TEST_F(AgentTest, GetMaxValueOf1PossibleAction_0)
{
    // up
    vector<int> possibleActions {0};
    vector<double> values {0};
    //valueFunction.setQValues(initState, values);
    double expected = 0;
    double actual = agentPolicy->maxExpected(possibleActions, values)->first;
    EXPECT_EQ(expected, actual);
}

// -----------------------------------------------------------------------------

// Environment::getStateByAction

// -----------------------------------------------------------------------------

TEST_F(AgentTest, GetStateByValidAction_0)
{
    pair<int, int> *expected = new pair<int, int> {0, 1};
    pair<int, int> *actual = environment->getStateByAction(0);
    EXPECT_EQ(*expected, *actual);
}

TEST_F(AgentTest, GetStateByValidAction_1)
{
    pair<int, int> *expected = new pair<int, int> {1, 2};
    pair<int, int> *actual = environment->getStateByAction(1);
    EXPECT_EQ(*expected, *actual);
}

TEST_F(AgentTest, GetStateByValidAction_2)
{
    pair<int, int> *expected = new pair<int, int> {2, 1};
    pair<int, int> *actual = environment->getStateByAction(2);
    EXPECT_EQ(*expected, *actual);
}

TEST_F(AgentTest, GetStateByValidAction_3)
{
    pair<int, int> *expected = new pair<int, int> {1, 0};
    pair<int, int> *actual = environment->getStateByAction(3);
    EXPECT_EQ(*expected, *actual);
}

// -----------------------------------------------------------------------------

// Environment::step

// -----------------------------------------------------------------------------

TEST_F(AgentTest, StepUp)
{
    // {1, 3} because no more options after I went one up from (1,1)
    vector<int> *actions = new vector<int>{1, 3};
    pair<int, int> *agentPos = new pair<int, int> {0, 1};
    Environment::Response* expected = new Environment::Response(agentPos, *actions, 0, false);
    Environment::Response* actual = environment->step(0);
    // TODO overload operator ==
    //EXPECT_EQ(*expected, *actual);
    EXPECT_EQ(*expected->state, *actual->state);
    EXPECT_EQ(expected->options, actual->options);
    EXPECT_EQ(expected->reward, actual->reward);
    EXPECT_EQ(expected->finished, actual->finished);

}


// -----------------------------------------------------------------------------

// main

// -----------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    cout << "start tests" << endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
