//
// Created by jonas on 4/4/18.
//
#include <vector>
#include "Agent.h"

using namespace std;

void Agent::test() {
    cout << "Hello World!" << endl;
}

void Agent::fit(int numberOfGames) {
    for (int i = 0; i < numberOfGames; i++) {
        environment = Environment();
        currentState = environment.initialState();
        playGame();
    }
}

Agent::Agent(double learningRate, double greedyRate) {
    qValues = vector<vector<double>>; //@todo get size of game for this
    this->learningRate = learningRate;
    this->greedyRate = greedyRate;
}

void Agent::playGame() {
    bool finished = false;
    int nextAction = 0;

    while (!finished) {
        Environment::Response response = environment.step(nextAction);
        updateQValues(response);
        nextAction = choseAction(response);
        currentState = response.state;
        finished = response.finished;
    }
}

void Agent::updateQValues(Environment::Response response) {
    double q = qValues[currentState];
    q += learningRate * (response.reward + greedyRate * maxExpected()) - q;
}

//@todo implement maxExpected()
double Agent::maxExpected() {
    return 0;
}
