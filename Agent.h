//
// Created by jonas on 4/4/18.
//

#ifndef WORLDDOMINATION_AGENT_H
#define WORLDDOMINATION_AGENT_H

#include <iostream>
#include <vector>
#include "Environment.h"

using namespace std;

class Agent {
private:
    //it has to be up here since the compiler will crash otherwise
    class QValues {
        vector<vector<double>> qValues;//@todo could be a simple list too

    public:
        double operator[](tuple<int, int> i) {
            //@todo schauen ob caro da nen Schmarrn geschrieben hat mit get<0>(i)...
            return qValues[get<0>(i)][get<1>(i)];
            //return qValues[i.first][i.second];
        }

    };

public:
    QValues qValues;
    Environment environment;
    std::tuple<int, int> currentState; //current state the agent is in
    double learningRate; //how fast he adopts to things he sees
    double discountRate; //how much value is given to future rewards
    int environmentType;//not needed for now but will be as soon as we have different environments

public:
    /*
     * constructor
     * @param learningRate
     * @param discountRate
     */
    Agent(double learningRate, double discountRate);

    /*
     * just a dummy test method, no value besides that
     */
    void test();

    /*
     * lets the agent learn from a given number of games
     */
    void fit(int numberOfGames);


private:

    void updateQValues(Environment::Response response);

    void playGame();

    int choseAction(Environment::Response response);

    double maxExpected();
};


#endif //WORLDDOMINATION_AGENT_H
