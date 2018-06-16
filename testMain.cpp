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
    //Num2DTable valueFunction;
    Environment *environment;
    void SetUp()
    {
        agent = new Agent(0.1, 0.8, new ThresholdPolicy(0.8), new Environment());
        //initState = pair<int, int>{1, 1};
        agentPolicy = (ThresholdPolicy*) agent->policy;
        agent->valueFunction = Num2DTable{{3,4}, {0,0,3,0, 0,0,0,0, 0,0,1,0}};
        environment = agent->environment;
        environment->agentPosition = pair<int, int>{1, 2};
        agent->currentState = pair<int, int>{1, 2};
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
    double expected = 4;
    double actual = agentPolicy->maxExpected(possibleActions, values)->first;
    EXPECT_EQ(expected, actual);
}

TEST_F(AgentTest, GetMaxValueOf3PossibleActions_5)
{
    // up, left
    vector<int> possibleActions {0, 3};
    vector<double> values {5, 1, 3};
    double expected = 5;
    double actual = agentPolicy->maxExpected(possibleActions, values)->first;
    EXPECT_EQ(expected, actual);
}

TEST_F(AgentTest, GetMaxValueOf1PossibleAction_0)
{
    // up
    vector<int> possibleActions {0};
    vector<double> values {0};
    double expected = 0;
    double actual = agentPolicy->maxExpected(possibleActions, values)->first;
    EXPECT_EQ(expected, actual);
}

// -----------------------------------------------------------------------------

// Environment::getStateByAction

// -----------------------------------------------------------------------------

TEST_F(AgentTest, GetStateByValidAction_UP)
{
    pair<int, int> *expected = new pair<int, int> {0, 2};
    pair<int, int> *actual = environment->getStateByAction(0);
    EXPECT_EQ(*expected, *actual);
    delete expected;
    delete actual;
}

TEST_F(AgentTest, GetStateByValidAction_RIGHT)
{
    pair<int, int> *expected = new pair<int, int> {1, 3};
    pair<int, int> *actual = environment->getStateByAction(1);
    EXPECT_EQ(*expected, *actual);
    delete expected;
    delete actual;
}

TEST_F(AgentTest, GetStateByValidAction_DOWN)
{
    pair<int, int> *expected = new pair<int, int> {2, 2};
    pair<int, int> *actual = environment->getStateByAction(2);
    EXPECT_EQ(*expected, *actual);
    delete expected;
    delete actual;
}

// Blocked field
TEST_F(AgentTest, GetStateByInvalidAction_LEFT)
{
    //pair<int, int> *expected = new pair<int, int> {1, 1};
    ASSERT_ANY_THROW(environment->getStateByAction(3));
}

// -----------------------------------------------------------------------------

// Environment::step

// -----------------------------------------------------------------------------

TEST_F(AgentTest, StepIntoNormalField_UP)
{
    // up, right, down, left
    // options after agent moved
    vector<int> *actions = new vector<int>{1, 2, 3};
    pair<int, int> *agentPos = new pair<int, int> {0, 2};
    Environment::Response* expected = new Environment::Response(agentPos, *actions, 0, false);
    Environment::Response* actual = environment->step(0);
    EXPECT_EQ(*expected->state, *actual->state);
    EXPECT_EQ(expected->options, actual->options);
    EXPECT_EQ(expected->reward, actual->reward);
    EXPECT_EQ(expected->finished, actual->finished);
    delete expected;
    delete actual;
    delete actions;
    delete agentPos;
}

TEST_F(AgentTest, StepIntoNegativeField_RIGHT)
{
    vector<int> *actions = new vector<int>{0, 2, 3};
    pair<int, int> *agentPos = new pair<int, int> {1, 3};
    Environment::Response* expected = new Environment::Response(agentPos, *actions, -1, true);
    Environment::Response* actual = environment->step(1);
    EXPECT_EQ(*expected->state, *actual->state);
    EXPECT_EQ(expected->options, actual->options);
    EXPECT_EQ(expected->reward, actual->reward);
    EXPECT_EQ(expected->finished, actual->finished);
    delete expected;
    delete actual;
    delete actions;
    delete agentPos;
}

TEST_F(AgentTest, StepIntoNormalField_DOWN)
{
    vector<int> *actions = new vector<int>{0, 1, 3};
    pair<int, int> *agentPos = new pair<int, int> {2, 2};
    Environment::Response* expected = new Environment::Response(agentPos, *actions, 0, false);
    Environment::Response* actual = environment->step(2);
    EXPECT_EQ(*expected->state, *actual->state);
    EXPECT_EQ(expected->options, actual->options);
    EXPECT_EQ(expected->reward, actual->reward);
    EXPECT_EQ(expected->finished, actual->finished);
    delete expected;
    delete actual;
    delete actions;
    delete agentPos;
}

TEST_F(AgentTest, StepIntoBlockedField_LEFT)
{
    vector<int> *actions = new vector<int>{0, 1, 2};
    pair<int, int> *agentPos = new pair<int, int> {1, 2};
    Environment::Response* expected = new Environment::Response(agentPos, *actions, 0, false);
    Environment::Response* actual = environment->step(3);
    EXPECT_EQ(*expected->state, *actual->state);
    EXPECT_EQ(expected->options, actual->options);
    EXPECT_EQ(expected->reward, actual->reward);
    EXPECT_EQ(expected->finished, actual->finished);
    delete expected;
    delete actual;
    delete actions;
    delete agentPos;
}

TEST_F(AgentTest, Go2StepsIntoPositiveField_UP_RIGHT)
{
    vector<int> *actions = new vector<int>{2, 3};
    pair<int, int> *agentPos = new pair<int, int> {0, 3};
    Environment::Response* expected = new Environment::Response(agentPos, *actions, 1, true);
    environment->step(0);
    Environment::Response* actual = environment->step(1);
    EXPECT_EQ(*expected->state, *actual->state);
    EXPECT_EQ(expected->options, actual->options);
    EXPECT_EQ(expected->reward, actual->reward);
    EXPECT_EQ(expected->finished, actual->finished);
    delete expected;
    delete actual;
    delete actions;
    delete agentPos;
}

TEST_F(AgentTest, Go2StepsIntoWall_UP_UP)
{
    vector<int> *actions = new vector<int>{1, 2, 3};
    pair<int, int> *agentPos = new pair<int, int> {0, 2};
    Environment::Response* expected = new Environment::Response(agentPos, *actions, 0, false);
    environment->step(0);
    Environment::Response* actual = environment->step(0);
    EXPECT_EQ(*expected->state, *actual->state);
    EXPECT_EQ(expected->options, actual->options);
    EXPECT_EQ(expected->reward, actual->reward);
    EXPECT_EQ(expected->finished, actual->finished);
    delete expected;
    delete actual;
    delete actions;
    delete agentPos;
}

// -----------------------------------------------------------------------------

// Agent::getValuesByActions

// -----------------------------------------------------------------------------

// Friend_Test in Agent private
TEST_F(AgentTest, GetValuesByPossibleActions){
    vector<double> *expected = new vector<double>{3, 0, 1};
    vector<int> *possibleActions = new vector<int>{0, 1, 2};
    vector<double> *actual = agent->getValuesByActions(possibleActions);
    EXPECT_EQ(*expected, *actual);

    environment->step(0);
    expected = new vector<double>{0, 0, 0};
    possibleActions = new vector<int>{1, 2, 3};
    actual = agent->getValuesByActions(possibleActions);
    EXPECT_EQ(*expected, *actual);

    environment->step(3);
    expected = new vector<double>{3, 0};
    possibleActions = new vector<int>{1, 3};
    actual = agent->getValuesByActions(possibleActions);
    EXPECT_EQ(*expected, *actual);

    delete expected;
    delete actual;
    delete possibleActions;
}

// -----------------------------------------------------------------------------

// Agent::updateValueFunction

// -----------------------------------------------------------------------------

// Friend_Test in Agent private
TEST_F(AgentTest, UpdateValueFunction) {

    // move up
    Environment::Response* response = environment->step(0);
    agent->updateValueFunction(response);
    double value_12 = 0 + 0.1 * (0 + 0.8 * 3 - 0);
    agent->currentState = pair<int,int>(*response->state);
    Num2DTable expected = Num2DTable{{3,4}, {0,0,3,0, 0,0,value_12,0, 0,0,1,0}};
    EXPECT_EQ(agent->valueFunction, expected);

    // move right
    response = environment->step(1);
    agent->updateValueFunction(response);
    double value_02 = 3 + 0.1 * (1 + 0.8 * 0 - 3);
    expected = Num2DTable{{3,4}, {0,0,value_02,1, 0,0,value_12,0, 0,0,1,0}};
    EXPECT_EQ(agent->valueFunction, expected);

    delete response;
}

// -----------------------------------------------------------------------------

// main

// -----------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    cout << "start tests" << endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
