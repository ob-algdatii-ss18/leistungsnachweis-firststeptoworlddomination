//
// Created by Jonas on 23.04.2018.
//

#ifndef WORLDDOMINATION_POLICY_H
#define WORLDDOMINATION_POLICY_H

#include <vector>
#include <cstdlib>
#include <cmath>
#include <cfloat>


using namespace std;

class Policy {

public:

    Policy(){};

    virtual int chooseAction(vector<int> possibleActions, vector<double> numValues) {
        cout << "not supposed to be called" << endl;
    };

};

class SoftMaxPolicy : public Policy {

public:
    SoftMaxPolicy() = default;

    int chooseAction(vector<int> possibleActions, vector<double> numValues) {
        //cout << "chose action" << endl;
        vector<double > softValues {};
        double sum = 0;

        for (int a = 0; a < possibleActions.size(); a++) {
            double v = pow(M_E, numValues[a]);       //calculates the exponential softmax value
            softValues.push_back(v);                //stores the softmax values
            sum += v;                               //sum of all exponential functions to normalize the results
        }

        //this loop ensures that the probabilities of the softValues vector add up to one (normalization)
        for (double &softValue : softValues) {
            softValue /= sum;
        }

        double p = ((double) rand() / (RAND_MAX));
        int action = 0;//default value that will never be returned
        double summedP = 0; //this value gives the combined probability distribution for the actions
        //this loop chooses the action based on an random value p and the softmax distribution.
        for (int i = 0; i < softValues.size(); i++) {
            summedP += softValues[i];
            if (p < summedP) {
                action = possibleActions[i];
                break;
            }
        }
        return action;
    }
};

class ThresholdPolicy : public Policy {
    FRIEND_TEST(AgentTest, GetMaxValueOf4PossibleActions_4);
    FRIEND_TEST(AgentTest, GetMaxValueOf4PossibleActions_5);
    FRIEND_TEST(AgentTest, GetMaxValueOf3PossibleActions_4);
    FRIEND_TEST(AgentTest, GetMaxValueOf3PossibleActions_5);
    FRIEND_TEST(AgentTest, GetMaxValueOf1PossibleAction_0);


    double explRate; // = 0.8;

    /*
* gives back the maximal expected reward from a state given in a response
* @param response: position
*/

    pair<double, int>* maxExpected(vector<int> possibleActions, vector<double> values) {
        double maxVal = -DBL_MAX;
        int action = 0;

        for(int a = 0; a < possibleActions.size(); a++) {
            if(values[a] > maxVal) {
                maxVal = values[a];
                action = possibleActions[a];
            }
        }
        return new pair<double, int>{maxVal, action};
    }

public:

    ThresholdPolicy(double explRate) : explRate(explRate) {}

    // TODO Wie testen mit rand().. immer anders, Werte in Debug Modus strange
    int chooseAction(vector<int> possibleActions, vector<double> numValues) {

        double p = ((double) rand() / (RAND_MAX));
        // cout << p << endl;
        int result;
        if (p <= explRate) {
            result = maxExpected(possibleActions, numValues)->second;
        } else {
            result = possibleActions[rand() % possibleActions.size()];
        }
        return result;
    }

};

#endif //WORLDDOMINATION_POLICY_H
