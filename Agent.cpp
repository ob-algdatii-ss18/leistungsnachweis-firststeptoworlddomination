//
// Created by jonas on 4/4/18.
//
#include <vector>
#include "Agent.h"
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include "gtest/gtest.h"

using namespace std;

bool debugFlag = false;

void Agent::fit(int numberOfGames) {
    cout << "Number of Games: " << numberOfGames << endl;
    for (int i = 0; i < numberOfGames; i++) {
        environment->reset();

        pair<int,int>* initState = environment->initialState();
        currentState = pair<int,int>(*initState);
        delete initState;

        playGame();
    }
    cout << valueFunction.toString() << endl << endl;
}

Agent::Agent(double learningRate, double discountRate, Policy *policy, Environment *env) {
    pair<int, int> size = global_qValueSize;
    this->valueFunction = Num2DTable(size); //@todo get size of game for this
    this->learningRate = learningRate;
    this->discountRate = discountRate;
    this->policy = policy;
    this->environment = env;
}

void Agent::playGame() {
    bool finished = false;
    int counter = 0;
    vector<int>* possibleActions = environment->getActions();

    while (!finished) {
        int a = policy->chooseAction(*possibleActions, *getValuesByActions(possibleActions));
        delete possibleActions;
        Environment::Response* response = environment->step(a);
        updateValueFunction(response);
        currentState = pair<int,int>(*response->state);
        finished = response->finished;
        possibleActions = new vector<int> {response->options};
        counter++;
        delete response;
        if(debugFlag)
            cout << valueFunction.toString() << endl << endl;
    }
    actionCounter.push_back(counter);
}

/*
void Agent::updateQValueFunction(Environment::Response *response) {
    double q = valueFunction[currentState];
    pair<double, int>* maxExp = maxExpected(response->state, nullptr);
    q += learningRate * (response->reward + discountRate * maxExp->first - q);
    valueFunction.setQValue(currentState, q);
    if (response->finished)
        valueFunction.setQValue(*response->state, response->reward);
    delete maxExp;
}*/


void Agent::updateValueFunction(Environment::Response *response) {
    double q = valueFunction[currentState];
    q += learningRate * (response->reward + discountRate * valueFunction[*response->state] - q);
    valueFunction.setQValue(currentState, q);
    if (response->finished)
        valueFunction.setQValue(*response->state, response->reward);
}

void Agent::debug() {
    debugFlag = !debugFlag;
}

vector<double> *Agent::getValuesByActions(vector<int> *possibleActions) {
    auto result = new vector<double>{};
    for(auto a : *possibleActions) {
        result->push_back(valueFunction[*environment->getStateByAction(a)]);
    }
    return result;
}
