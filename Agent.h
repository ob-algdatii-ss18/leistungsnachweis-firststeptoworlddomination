//
// Created by jonas on 4/4/18.
//

#ifndef WORLDDOMINATION_AGENT_H
#define WORLDDOMINATION_AGENT_H

#include <iostream>
#include <vector>
#include "Environment.h"
#include "Num2DTable.h"
#include "gtest/gtest.h"
//#include "Policy.h"


using namespace std;

class Agent {

    friend class Policy;

    Num2DTable valueFunction; //values of the Agent (actually right now it's just a value function)
    Environment environment; //environment the agent lives in
    pair<int, int> currentState; //current state the agent is in
    double learningRate; //how fast he adopts to things he sees
    double discountRate; //how much value is given to future rewards
    int environmentType;//not needed for now but will be as soon as we have different environments
    vector<int> actionCounter {}; //stores the number of iterations it took the agent to finish the game
    double explRate; //exploiting rate
    int policyType = 0; //policy for chosing actions
    //Policy policy;

public:
    /*
     * constructor
     * @param learningRate
     * @param discountRate
     */
    Agent(double learningRate, double discountRate, double explRate, int policy);

    /*
     * lets the agent learn from a given number of games
     * @param numberOfGames: number of games he is supposed to play
     */
    void fit(int numberOfGames);

    void debug();

private:
    FRIEND_TEST(AgentTest, FirstMaxValueMustBeZero);
    FRIEND_TEST(AgentTest, HigherMaxValueOnRightSide);


    /*
     * updates q-values
     */
    void updateQValueFunction(Environment::Response *response);

    /*
     * update value function
     */
    void updateValueFunction(Environment::Response *response);

    /*
     * plays a single game
     */
    void playGame();

    /*
     * strategy by which the agent choses his next action
     */
    int choseAction(vector<int> *possibleActions);

    /*
     * gives back the maximal expected reward from a state given in a response
     */
    pair<double, int>* maxExpected(pair<int, int> *response, vector<int> *possibleActions);

    /*
     * Chooses an action with fixed probablility for random action
     */
    int randomThreshold(vector<int> *possibleActions);

    /*
     * implementation of a softmax evaluation of the actions
     */
    int softMax(vector<int> *possibleActions);
};

class ValueAgent : Agent {

public:
    ValueAgent (double learningRate, double discountRate, double explRate, int policy) : Agent (learningRate, discountRate, explRate, policy) {

    }



};


#endif //WORLDDOMINATION_AGENT_H
