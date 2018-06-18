#ifndef WORLDDOMINATION_AGENT_H
#define WORLDDOMINATION_AGENT_H

#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "Environment.h"
#include "Num2DTable.h"
#include "Policy.h"


using namespace std;

class Agent {
    friend class AgentTest;

    friend class Policy;

    /**
     * values of the Agent (actually right now it's just a value function)
     */
    Num2DTable valueFunction;
    /**
     * environment the agent lives in
     */
    Environment* environment;
    /**
     * current state the agent is in
     */
    pair<int, int> currentState;
    /**
     * how fast he adopts to things he sees
     */
    double learningRate;
    /**
     * how much value is given to future rewards
     */
    double discountRate;
    /**
     * stores the number of iterations it took the agent to finish the game
     */
    vector<int> actionCounter {};
    /**
     * the policy the agent uses to decide his next step
     */
    Policy* policy;

public:
    /**
     * constructor
     * @param learningRate: alpha
     * @param discountRate: gamma
     * @param explRate: probability of choosing a random action
     * @param policy: strategy for choosing next action
     */
    Agent(double learningRate, double discountRate, Policy *policy, Environment *env);

    /**
     * lets the agent learn from a given number of games
     * @param numberOfGames: number of games he is supposed to play
     */
    void fit(int numberOfGames);

    void debug();

private:

    /*
     * updates q-values
     * @param: response of the environment
     */
    //void updateQValueFunction(Environment::Response *response);

    FRIEND_TEST(AgentTest, UpdateValueFunction);

    /**
     * update value function
     * @param: response of the environment
     */
    void updateValueFunction(Environment::Response *response);

    /**
     * plays a single game
     */
    void playGame();

    FRIEND_TEST(AgentTest, GetValuesByPossibleActions);

    /**
     * get values by given actions
     * @param possibleActions
     * @return values in order of possible action
     */
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
