//
// Created by jonas on 4/4/18.
//

#ifndef WORLDDOMINATION_AGENT_H
#define WORLDDOMINATION_AGENT_H

#include <iostream>
#include <vector>
#include "Environment.h"

class Agent {
    vector<double> qValues;
    Environment environment;
    std::tuple<int, int> currentState;
    double learningRate;
    double greedyRate;
    int environmentType;

public:

    Agent(double learningRate, double greedyRate);

    void test();

    void fit(int numberOfGames);


private:
    class QValues {
        vector<vector<double>> qValues;
    public:
        double operator [] (tuple<int,int> i) {
            return qValues[i.first][i.second];
        }

    };

    void updateQValues(Environment::Response response);

    int choseAction(Environment::Response response);

    void playGame();
};


#endif //WORLDDOMINATION_AGENT_H
