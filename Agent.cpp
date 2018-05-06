//
// Created by jonas on 4/4/18.
//
#include <vector>
#include "Agent.h"
#include <cstdlib>
#include <cmath>
#include "gtest/gtest.h"
//#include <rpcdcep.h>

using namespace std;

bool debugFlag = false;

void Agent::fit(int numberOfGames) {
    cout << "Number of Games: " << numberOfGames << endl;
    for (int i = 0; i < numberOfGames; i++) {
        //cout << "epoch: " << i << endl;
        environment = Environment();

        pair<int,int>* initState = environment.initialState();
        currentState = pair<int,int>(*initState);
        delete initState;

        //cout << "Start Game" << endl;
        playGame();
        //cout << "finished game" << endl << endl;
    }
    cout << valueFunction.toString() << endl << endl;
}

Agent::Agent(double learningRate, double discountRate, double explRate, int policy) {
    pair<int, int> size = global_qValueSize;
    this->valueFunction = Num2DTable(size); //@todo get size of game for this
    this->learningRate = learningRate;
    this->discountRate = discountRate;
    this->explRate = explRate;
    this->policyType = policy;
    //this->policy = Policy(policyType, this);
}

void Agent::playGame() {
    bool finished = false;
    int counter = 0;
    vector<int>* possibleActions = environment.getActions();

    // @todo actions = environment.getActions();
    while (!finished) {
        //@todo add possible actions to "choseAction", rearrange code for that
        //int a = choseAction(response->actions);
        int a = choseAction(possibleActions);
        //delete possibleActions;
        //int a = policy.choseAction();
        Environment::Response* response = environment.step(a);
        updateValueFunction(response);
        currentState = pair<int,int>(*response->state);
        finished = response->finished;
        possibleActions = new vector<int> {response->options};
        counter++;
        delete response;//@todo this caused crashes for a while
        if(debugFlag)
            cout << valueFunction.toString() << endl << endl;
    }
    actionCounter.push_back(counter);
}


void Agent::updateQValueFunction(Environment::Response *response) {
    double q = valueFunction[currentState];
    pair<double, int>* maxExp = maxExpected(response->state, nullptr);
    q += learningRate * (response->reward + discountRate * maxExp->first - q);
    valueFunction.setQValue(currentState, q);
    if (response->finished)
        valueFunction.setQValue(*response->state, response->reward);
    delete maxExp;
}


void Agent::updateValueFunction(Environment::Response *response) {
    double q = valueFunction[currentState];
    //pair<double, int>* maxExp = maxExpected(response->state);
    q += learningRate * (response->reward + discountRate * valueFunction[*response->state] - q);
    valueFunction.setQValue(currentState, q);
    if (response->finished)
        valueFunction.setQValue(*response->state, response->reward);
    //delete maxExp;
}

//@todo add "possible actions"
pair<double, int> * Agent::maxExpected(pair<int, int> *state, vector<int> *possibleActions) {
    double maxVal = -100000.0; //@todo ugly thing, since hard coded lower bound
    int action = 0;

    for(int a : *possibleActions) {
        try {
            auto testAt = environment.getStateByAction(a);
            if((valueFunction)[*testAt] > maxVal) {
                maxVal = (valueFunction)[*testAt];
                action = a;
            }
            delete testAt;
        } catch (int e) {
            //ignoring 21 errors, throwing all others
            if(e != 21)  //error 21: invalid action
                throw e;
        }
    }

    auto result = new pair<double, int>{maxVal, action};
    return result;
}

int Agent::choseAction(vector<int> *possibleActions) {
    if(policyType == 0)
        return randomThreshold(possibleActions);
    if(policyType == 1)
        return softMax(possibleActions);
    throw 20;
}

int Agent::randomThreshold(vector<int> *possibleActions) {
    double p = ((double) rand() / (RAND_MAX));

    int result;
    if (p < explRate) {
        result = maxExpected(&currentState, possibleActions)->second;
    } else {
        result = (*possibleActions)[rand() % possibleActions->size()];
    }
    return result;
}

int Agent::softMax(vector<int> *possibleActions) {
    vector<int> actions {};
    vector<double > softValues {};
    double sum = 0;
    double v;

    for (int a : *possibleActions) {
        try {
            auto testAt = environment.getStateByAction(a);
            actions.push_back(a);                   //stores action
            v = pow(M_E, valueFunction[*testAt]);    //calculates the exponential softmax value
            softValues.push_back(v);                //stores the softmax values
            sum += v;                               //sum of all exponential functions to normalize the results
            delete testAt;
        } catch (int e) {
            //ignoring 21 errors, throwing all others
            if(e != 21)  //error 21: invalid action
                throw e;
        }
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

void Agent::debug() {
    debugFlag = !debugFlag;
}
