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
        cout << "finished game" << endl;
    }
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
        //cout << "\ncurrent state: " << currentState->first << "," << currentState->second << endl;
        int a = choseAction();
        Environment::Response* response = environment.step(a);
        updateQValues(response);
        currentState = pair<int,int>(*response->state); //{response.state.first, response.state.second};
        finished = response->finished;
        counter++;
        delete response;
    }
    cout << counter<< " " << finished << endl;
    cout << qValues->toString() << endl << endl;
}


void Agent::updateQValues(Environment::Response *response) {
    //cout << response->toString() << endl;
    double q = (*qValues)[currentState];
    //cout << "state: " << currentState.first << " " << currentState.second << endl;
    //cout << "q1:" << q << endl;
    pair<double, int>* maxExp = maxExpected(response->state);
    //cout << "maxExp: " << maxExp->first << "/" << maxExp->second << endl;
    q += learningRate * (response->reward + discountRate * maxExp->first) - q;
    //cout << "q2:" << q << endl;
    qValues->setQValue(currentState, q);
}

pair<double, int>* Agent::maxExpected(pair<int, int> *state) {

    double maxVal = -100000; //@todo ugly thing, since hard coded lower bound
    //cout << "maxVal: " << maxVal << endl;
    int direction = 0;

    pair<int, int> testAt = pair<int, int>{state->first, state->second - 1};
    //cout << "testAt: " << testAt.first << "/" << testAt.second << endl;
    if ((*qValues)[testAt] > maxVal && testAt.second >= 0) {
        maxVal = (*qValues)[testAt];
        //cout << "z: " << (*qValues)[testAt]<< endl;
        direction = 0;
    }

    testAt = pair<int, int>{state->first, state->second + 1};
    if ((*qValues)[testAt] > maxVal && environment.shape.second >  testAt.second) {
        maxVal = (*qValues)[testAt];
        direction = 1;
    }


    testAt = pair<int, int>{state->first + 1, state->second};

    if ((*qValues)[testAt] > maxVal  && environment.shape.first >  testAt.first) {
        maxVal = (*qValues)[testAt];
        //cout << "z: " << (*qValues)[testAt]<< endl;
        direction = 2;
    }

    testAt = pair<int, int>{state->first - 1, state->second};
    if ((*qValues)[testAt] > maxVal && testAt.first >= 0) {
        maxVal = (*qValues)[testAt];
        //cout << "z: " << (*qValues)[testAt]<< endl;
        direction = 3;
    }
    //cout << "maxVal: " << maxVal << "/" << direction << endl;
    pair<double, int>* result = new pair<double, int>{maxVal, direction};
    return result;
}

//this is the agents policy
int Agent::choseAction() {
    double p = ((double) rand() / (RAND_MAX));
    //cout << "random = " << p << " (explRate = " << explRate <<")"<< endl;

    int result;
    if (p < explRate) {
        result = maxExpected(&currentState)->second;
    } else {
        result = rand() % 4;
        //cout << "##### random direction #####"  << endl;
    }
    return result;
}
