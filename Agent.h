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
#include "Policy.h"


using namespace std;

class Agent {

    friend class Policy;

    Num2DTable valueFunction; //values of the Agent (actually right now it's just a value function)
    Environment* environment; //environment the agent lives in
    pair<int, int> currentState; //current state the agent is in
    double learningRate; //how fast he adopts to things he sees
    double discountRate; //how much value is given to future rewards
    vector<int> actionCounter {}; //stores the number of iterations it took the agent to finish the game
    Policy* policy;

public:
    /*
     * constructor
     * @param learningRate: alpha
     * @param discountRate: gamma
     * @param explRate: probability of choosing a random action
     * @param policy: strategy for choosing next action
     */
    Agent(double learningRate, double discountRate, Policy *policy, Environment *env);

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
     * @param: response of the environment
     */
    //void updateQValueFunction(Environment::Response *response);

    /*
     * update value function
     * @param: response of the environment
     */
    void updateValueFunction(Environment::Response *response);

    /*
     * plays a single game
     */
    void playGame();

    vector<double> *getValuesByActions(vector<int> *possibleActions);

    void saveAgent(){
        //@todo
    }

    Agent* loadAgent() {
        //@todo
    }
};

class ValueAgent : Agent {

public:
    ValueAgent (double learningRate, double discountRate, Policy* policy, Environment* env) :
            Agent(learningRate, discountRate, policy, env) {

    }

};


#endif //WORLDDOMINATION_AGENT_H
