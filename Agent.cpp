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
        currentState = environment.initialState();
        cout << "Start Game" << endl;
        playGame();
    }
}

Agent::Agent(double learningRate, double discountRate, double explRate) {
    pair<int, int> size = QValueSize;
    cout << "init qValues - size: " << size.first << "," << size.second << endl;
    this->qValues = new Num2DTable(&size); //@todo get size of game for this
    this->learningRate = learningRate;
    this->discountRate = discountRate;
    this->explRate = explRate;
}

void Agent::playGame() {
    bool finished = false;
    int counter = 0;

    while (!finished) {
        cout << "\ncurrent state: " << currentState->first << "," << currentState->second << endl;
        Environment::Response response = environment.step(choseAction());
        updateQValues(response);
        currentState = response.state; //{response.state.first, response.state.second};
        finished = response.finished;
        if (finished) {
            cout << "finished is true" << endl;
            break;
        }
        //cout << counter++ << " " << finished << endl;
    }
}

void Agent::updateQValues(Environment::Response response) {
    cout << "updateQValues" << endl;
    double q = (*qValues)[*currentState];
    q += learningRate * (response.reward + discountRate * (maxExpected(response.state))->first) - q;
    (*qValues).setQValue(*currentState, q);
}

//@todo implement maxExpected()
pair<double, int> *Agent::maxExpected(pair<int, int> *state) {

    pair<int, int> *testAt = new pair<int, int>{state->first - 1, state->second};
    double maxVal = (*qValues)[*testAt];
    int direction = 0;

    testAt = new pair<int, int>{state->first, state->second + 1};
    if ((*qValues)[*testAt] > maxVal) {
        maxVal = (*qValues)[*testAt];
        direction = 1;
    }


    testAt = new pair<int, int>{state->first + 1, state->second};
    if ((*qValues)[*testAt] > maxVal) {
        maxVal = (*qValues)[*testAt];
        direction = 2;
    }

    testAt = new pair<int, int>{state->first, state->second - 1};
    if ((*qValues)[*testAt] > maxVal) {
        maxVal = (*qValues)[*testAt];
        direction = 3;
    }


    pair<double, int> *result = new pair<double, int>{maxVal, direction};
    return result;
}

//this is the agents policy
int *Agent::choseAction() {

    double p = ((double) rand() / (RAND_MAX));
    cout << "random = " << p << " (explRate = " << explRate <<")"<< endl;

    int *result;//@todo do we really need a pointer here?
    if (p < explRate) {
        result = new int((*maxExpected(currentState)).second);
    } else {
        result = new int(rand() % 4);
        cout << "##### random direction #####"  << endl;
    }
    return result;
}
