//
// Created by jonas on 4/4/18.
//
#include <vector>
#include "Agent.h"
#include <cstdlib>
#include <cmath>
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
    while (!finished) {
        int a = choseAction();
        //int a = policy.choseAction();
        Environment::Response* response = environment.step(a);
        updateValueFunction(response);
        currentState = pair<int,int>(*response->state);
        finished = response->finished;
        counter++;
        delete response;//@todo this caused crashes for a while
        if(debugFlag)
            cout << valueFunction.toString() << endl << endl;
    }
    actionCounter.push_back(counter);
}


void Agent::updateQValueFunction(Environment::Response *response) {
    double q = valueFunction[currentState];
    pair<double, int>* maxExp = maxExpected(response->state);
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

pair<double, int>* Agent::maxExpected(pair<int, int> *state) {

    double maxVal = -100000.0; //@todo ugly thing, since hard coded lower bound
    int action = 0;

    pair<int, int> testAt = pair<int, int>{state->first - 1, state->second};
    if (valueFunction.keyExists(testAt) && (valueFunction)[testAt] > maxVal) {
        maxVal = (valueFunction)[testAt];
        action = 0;
    }

    testAt = pair<int, int>{state->first, state->second + 1};
    if (valueFunction.keyExists(testAt) && (valueFunction)[testAt] > maxVal) {
        maxVal = (valueFunction)[testAt];
        action = 1;
    }


    testAt = pair<int, int>{state->first + 1, state->second};
    if (valueFunction.keyExists(testAt) && (valueFunction)[testAt] > maxVal) {
        maxVal = (valueFunction)[testAt];
        action = 2;
    }

    testAt = pair<int, int>{state->first, state->second - 1};
    if (valueFunction.keyExists(testAt) && (valueFunction)[testAt] > maxVal) {
        maxVal = (valueFunction)[testAt];
        action = 3;
    }
    auto* result = new pair<double, int>{maxVal, action};
    return result;
}

int Agent::choseAction() {
    if(policyType == 0)
        return randomThreshold();
    if(policyType == 1)
        return softMax();
    return -1;
}

int Agent::randomThreshold() {
    double p = ((double) rand() / (RAND_MAX));

    int result;
    if (p < explRate) {
        result = maxExpected(&currentState)->second;
    } else {
        result = rand() % 4;
    }
}

int Agent::softMax() {
    vector<int> actions {};             //stores actions
    vector<double > softValues {};      //stores weighted softmax values
    double sum = 0;                     //stores the sum of the softmax values to normalize
    double v;                           //stores the single value, just a temporal variable

    //up
    pair<int, int> testAt = pair<int, int>{currentState.first - 1, currentState.second};
    if (valueFunction.keyExists(testAt)) {
        actions.push_back(0);                   //stores action
        v = pow(M_E, valueFunction[testAt]);    //calculates the exponential softmax value
        softValues.push_back(v);                //stores the softmax values
        sum += v;                               //sum of all exponential functions to normalize the results
    }
    //down
    testAt = pair<int, int>{currentState.first + 1, currentState.second};
    if (valueFunction.keyExists(testAt)) {
        actions.push_back(2);
        v = pow(M_E, valueFunction[testAt]);
        softValues.push_back(v);
        sum += v;
    }

    //right
    testAt = pair<int, int>{currentState.first, currentState.second + 1};
    if (valueFunction.keyExists(testAt)) {
        actions.push_back(1);
        v = pow(M_E, valueFunction[testAt]);
        softValues.push_back(v);
        sum += v;
    }

    //left
    testAt = pair<int, int>{currentState.first, currentState.second - 1};
    if (valueFunction.keyExists(testAt)) {
        actions.push_back(3);
        v = pow(M_E, valueFunction[testAt]);
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

void Agent::debug() {
    debugFlag = !debugFlag;
}
