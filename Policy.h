//
// Created by Jonas on 23.04.2018.
//

#ifndef WORLDDOMINATION_POLICY_H
#define WORLDDOMINATION_POLICY_H

#include <vector>
#include <cstdlib>
#include <cmath>
//#include <agtctl.h> //crap
//#include "Agent.h"

using namespace std;


class Policy {
    double explRate = 0.8;
    Agent* agent;
    int type;

    pair<double, int>* maxExpected(pair<int, int> *state) {

        double maxVal = -100000.0; //@todo ugly thing, since hard coded lower bound
        int action = 0;

        pair<int, int> testAt = pair<int, int>{state->first - 1, state->second};
        if (agent->valueFunction.keyExists(testAt) && (agent->valueFunction)[testAt] > maxVal) {
            maxVal = (agent->valueFunction)[testAt];
            action = 0;
        }

        testAt = pair<int, int>{state->first, state->second + 1};
        if (agent->valueFunction.keyExists(testAt) && (agent->valueFunction)[testAt] > maxVal) {
            maxVal = (agent->valueFunction)[testAt];
            action = 1;
        }


        testAt = pair<int, int>{state->first + 1, state->second};
        if (agent->valueFunction.keyExists(testAt) && (agent->valueFunction)[testAt] > maxVal) {
            maxVal = (agent->valueFunction)[testAt];
            action = 2;
        }

        testAt = pair<int, int>{state->first, state->second - 1};
        if (agent->valueFunction.keyExists(testAt) && (agent->valueFunction)[testAt] > maxVal) {
            maxVal = (agent->valueFunction)[testAt];
            action = 3;
        }
        auto* result = new pair<double, int>{maxVal, action};
        return result;
    }

public:

    Policy(int type, Agent* agent) : type(type), agent(agent) {};

    Policy(int type, Agent* agent, double explRate) : type(type), agent(agent), explRate(explRate) {};

    int choseAction() {
        if(type == 0)
            return randomThreshold();
        if(type == 1)
            return softMax();
        return -1;
    }

    int randomThreshold() {
        double p = ((double) rand() / (RAND_MAX));

        int result;
        if (p < explRate) {
            result = maxExpected(&agent->currentState)->second;
        } else {
            result = rand() % 4;
        }
    }

    int softMax() {
        vector<int> actions {};             //stores actions
        vector<double > softValues {};      //stores weighted softmax values
        double sum = 0;                     //stores the sum of the softmax values to normalize
        double v;                           //stores the single value, just a temporal variable

        //up
        pair<int, int> testAt = pair<int, int>{agent->currentState.first - 1, agent->currentState.second};
        if (agent->valueFunction.keyExists(testAt)) {
            actions.push_back(0);                   //stores action
            v = pow(M_E, agent->valueFunction[testAt]);    //calculates the exponential softmax value
            softValues.push_back(v);                //stores the softmax values
            sum += v;                               //sum of all exponential functions to normalize the results
        }
        //down
        testAt = pair<int, int>{agent->currentState.first + 1, agent->currentState.second};
        if (agent->valueFunction.keyExists(testAt)) {
            actions.push_back(2);
            v = pow(M_E, agent->valueFunction[testAt]);
            softValues.push_back(v);
            sum += v;
        }

        //right
        testAt = pair<int, int>{agent->currentState.first, agent->currentState.second + 1};
        if (agent->valueFunction.keyExists(testAt)) {
            actions.push_back(1);
            v = pow(M_E, agent->valueFunction[testAt]);
            softValues.push_back(v);
            sum += v;
        }

        //left
        testAt = pair<int, int>{agent->currentState.first, agent->currentState.second - 1};
        if (agent->valueFunction.keyExists(testAt)) {
            actions.push_back(3);
            v = pow(M_E, agent->valueFunction[testAt]);
            softValues.push_back(v);
            sum += v;
        }

        //this loop ensures that the probabilities of the softValues vector add up to one (normalization)
        for (double &softValue : softValues) {
            softValue /= sum;
        }

        double p = ((double) rand() / (RAND_MAX));
        int action = 0;//default value that will never be returned
        double summedP = 0; //this values gieves the combined probability distribution for the actions
        //this loop choses the action based on an random value p and the softmax distribution.
        for (int i = 0; i < softValues.size(); i++) {
            summedP += softValues[i];
            if (p < summedP) {
                action = actions[i];
                break;
            }
        }
        return action;

    }


};


#endif //WORLDDOMINATION_POLICY_H
