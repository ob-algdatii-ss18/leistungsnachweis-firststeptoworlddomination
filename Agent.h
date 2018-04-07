//
// Created by jonas on 4/4/18.
//

#ifndef WORLDDOMINATION_AGENT_H
#define WORLDDOMINATION_AGENT_H

#include <iostream>
#include <vector>
#include "Environment.h"
#include "Num2DTable.h"


using namespace std;

class Agent {
private:
    //it has to be up here since the compiler will crash otherwise


public:
    Num2DTable qValues;
    Environment environment;
    pair<int, int> * currentState; //current state the agent is in
    double learningRate; //how fast he adopts to things he sees
    double discountRate; //how much value is given to future rewards
    int environmentType;//not needed for now but will be as soon as we have different environments

public:
    /*
     * constructor
     * @param learningRate
     * @param discountRate
     */
    Agent(double learningRate, double discountRate, double explRate);

    /*
     * just a dummy test method, no value besides that
     */
    void test();

    /*
     * lets the agent learn from a given number of games
     * @param numberOfGames: number of games he is supposed to play
     */
    void fit(int numberOfGames);


private:

    void updateQValues(Environment::Response response);

    void playGame();

    int choseAction();

    pair<double, int> * maxExpected(pair<int, int> *response);

    double explRate;
};


#endif //WORLDDOMINATION_AGENT_H
