//
// Created by jonas on 4/4/18.
//
#include <vector>
#include "Agent.h"
#include <cstdlib>

using namespace std;

void Agent::fit(int numberOfGames) {
    cout << "Number of Games: " << numberOfGames << endl;
    for (int i = 0; i < numberOfGames; i++) {
        cout << "epoch: " << i << endl;
        environment = Environment();

        pair<int,int>* initState = environment.initialState();
        currentState = pair<int,int>(*initState);
        delete initState;                                               //@todo necessary?

        cout << "Start Game" << endl;
        playGame();
        cout << "finished game" << endl << endl;
    }
    cout << valueFunction->toString() << endl << endl;
}

Agent::Agent(double learningRate, double discountRate, double explRate) {
    pair<int, int> size = global_qValueSize;
    this->valueFunction = new Num2DTable(size); //@todo get size of game for this
    this->learningRate = learningRate;
    this->discountRate = discountRate;
    this->explRate = explRate;
}

void Agent::playGame() {
    bool finished = false;
    int counter = 0;
    while (!finished) {
        int a = choseAction();
        Environment::Response* response = environment.step(a);
        updateValueFunction(response);
        currentState = pair<int,int>(*response->state);
        finished = response->finished;
        counter++;
        delete response;//@todo this caused crashes for a while
    }
    actionCounter.push_back(counter);
    //cout << qValues->toString() << endl << endl;
}


void Agent::updateValueFunction(Environment::Response *response) {
    double q = (*valueFunction)[currentState];
    pair<double, int>* maxExp = maxExpected(response->state);
    q += learningRate * (response->reward + discountRate * maxExp->first) - q;
    valueFunction->setQValue(currentState, q);
    delete maxExp;
}

pair<double, int>* Agent::maxExpected(pair<int, int> *state) {

    double maxVal = -100000.0; //@todo ugly thing, since hard coded lower bound
    int action = 0;

    pair<int, int> testAt = pair<int, int>{state->first, state->second - 1};
    if (valueFunction->keyExists(testAt) && (*valueFunction)[testAt] > maxVal) {
        maxVal = (*valueFunction)[testAt];
        action = 0;
    }

    testAt = pair<int, int>{state->first, state->second + 1};
    if (valueFunction->keyExists(testAt) && (*valueFunction)[testAt] > maxVal) {
        maxVal = (*valueFunction)[testAt];
        action = 1;
    }


    testAt = pair<int, int>{state->first + 1, state->second};
    if (valueFunction->keyExists(testAt) && (*valueFunction)[testAt] > maxVal) {
        maxVal = (*valueFunction)[testAt];
        action = 2;
    }

    testAt = pair<int, int>{state->first - 1, state->second};
    if (valueFunction->keyExists(testAt) && (*valueFunction)[testAt] > maxVal) {
        maxVal = (*valueFunction)[testAt];
        action = 3;
    }
    auto* result = new pair<double, int>{maxVal, action};
    return result;
}

int Agent::choseAction() {
    double p = ((double) rand() / (RAND_MAX));

    int result;
    if (p < explRate) {
        result = maxExpected(&currentState)->second;
    } else {
        result = rand() % 4;
    }
    return result;
}
