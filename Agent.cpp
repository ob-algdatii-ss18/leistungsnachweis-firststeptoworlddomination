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

        //get variable from heap stores on the stack
        pair<int,int>* initState = environment.initialState();
        currentState = pair<int,int>(*initState);                       //@todo check copy
        delete initState;                                               //@todo necessary?

        cout << "Start Game" << endl;
        playGame();
        cout << "finished game" << endl << endl;
    }
    cout << qValues->toString() << endl << endl;
}

Agent::Agent(double learningRate, double discountRate, double explRate) {
    pair<int, int> size = QValueSize;
    //cout << "init qValues - size: " << size.first << "," << size.second << endl;
    this->qValues = new Num2DTable(size); //@todo get size of game for this
    //cout << qValues.toString() << endl << endl;
    this->learningRate = learningRate;
    this->discountRate = discountRate;
    this->explRate = explRate;
}

void Agent::playGame() {
    bool finished = false;
    int counter = 0;
    //cout << "game: \n" << environment.toString_PG() << endl;
    //cout << "rewards: \n" << environment.toString_RW() << endl;
    while (!finished) {
        int a = choseAction();
        //cout << "\ncurrent state: " << currentState.first << "," << currentState.second << endl << "action: " << a << endl;
        Environment::Response* response = environment.step(a);
        updateQValues(response);
        currentState = pair<int,int>(*response->state); //{response.state.first, response.state.second};
        finished = response->finished;
        counter++;
        //delete response;//@todo this caused crashes
    }
    cout << "step counter:" << counter << endl;
    cout << qValues->toString() << endl << endl;
}


void Agent::updateQValues(Environment::Response *response) {
    //cout << response->toString() << endl;
    //cout << "state: " << currentState.first << " " << currentState.second << endl;
    double q = (*qValues)[currentState];
    pair<double, int>* maxExp = maxExpected(response->state);
    //cout << "maxExp: " << maxExp->first << "/" << maxExp->second << endl;

    q += learningRate * (response->reward + discountRate * maxExp->first) - q;
    cout << "resp actions: "<<endl;
    for(int i = 0; i < response->options.size(); i++) {
        cout << response->options[i] << " ";
    }
    cout << endl <<"state: " << response->state->first << "/"<< response->state->second << endl;
    //cout << "diff: " << learningRate * (response->reward + discountRate * maxExp->first) - q << endl;
    qValues->setQValue(currentState, q);
    delete maxExp;
}

pair<double, int>* Agent::maxExpected(pair<int, int> *state) {

    double maxVal = -100000.0; //@todo ugly thing, since hard coded lower bound
    //cout << "maxVal: " << maxVal << endl;
    int action = 0;

    pair<int, int> testAt = pair<int, int>{state->first, state->second - 1};
    if (qValues->keyExists(testAt) && (*qValues)[testAt] > maxVal) {
        maxVal = (*qValues)[testAt];
        action = 0;
    }

    testAt = pair<int, int>{state->first, state->second + 1};
    if (qValues->keyExists(testAt) && (*qValues)[testAt] > maxVal) {
        maxVal = (*qValues)[testAt];
        action = 1;
    }


    testAt = pair<int, int>{state->first + 1, state->second};
    if (qValues->keyExists(testAt) && (*qValues)[testAt] > maxVal) {
        maxVal = (*qValues)[testAt];
        action = 2;
    }

    testAt = pair<int, int>{state->first - 1, state->second};
    if (qValues->keyExists(testAt) && (*qValues)[testAt] > maxVal) {
        maxVal = (*qValues)[testAt];
        action = 3;
    }
    //cout << "maxVal: " << maxVal << "/" << action << endl;
    pair<double, int>* result = new pair<double, int>{maxVal, action};
    return result;
}

//this is the agents policy
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
