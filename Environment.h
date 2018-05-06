//
// Created by jonas on 4/4/18.
//

#ifndef WORLDDOMINATION_ENVIRONMENT_H
#define WORLDDOMINATION_ENVIRONMENT_H

#include <vector>
#include "Num2DTable.h"


using namespace std;

static const pair<int, int> global_qValueSize = {3, 4};//@todo this is nasty crap

class Environment {


    vector<Num2DTable> gameRecord {}; //the game is stored here as a replay
    vector<int> actionRecord {};//actions taken by the agent are stored here
    Num2DTable playingGround{pair<int, int>{3, 4}, {1, 1, 1, -1, 1, 0, 1, -1, 1, 1, 1, 1}}; //current play ground
    Num2DTable rewards{pair<int, int>{3, 4},
                       {0, 0, 0, 1, 0, 0, 0, -1, 0, 0, 0, 0}}; //possible rewards are saved here
    pair<int, int> agentPosition = pair<int, int>{2, 0};

    bool validPosition(pair<int,int> index) {
        return playingGround.keyExists(index) && playingGround[index] != 0;
    }

public:

    pair<int, int> shape{3, 4};

    class Response {
    public:
        pair<int, int> *state; //game state
        vector<int> options; //vector of all possible actions //@todo use it
        double reward; //reward earned
        bool finished = false; //indicates if game is over

        //constructor
        Response(pair<int, int> *state, vector<int> options, double reward, bool finished) {
            this->state = state;
            this->options = options;
            this->reward = reward;
            this->finished = finished;
        }

        /*
         * generates formated string of the response object
         */
        string toString() {
            std::stringstream ss;
            ss << setprecision(3) << fixed;
            ss << "state: " << state->first << "/" << state->second << ", reward: " << reward;
            return ss.str();
        }
    };

    Environment() {
        vector<Num2DTable> gameRecord {}; //the game is stored here as a replay
        vector<int> actionRecord {};//actions taken by the agent are stored here
        Num2DTable playingGround{pair<int, int>{3, 4}, {1, 1, 1, -1, 1, 0, 1, -1, 1, 1, 1, 1}}; //current play ground
        Num2DTable rewards{pair<int, int>{3, 4},
                           {0, 0, 0, 1, 0, 0, 0, -1, 0, 0, 0, 0}}; //possible rewards are saved here
        pair<int, int> agentPosition = pair<int, int>{2, 0};
        pair<int, int> shape{3, 4};
    }

    /*
     * takes a step in a certain direction
     * @params action: chosen action by the agent
     * @return Response (state, options, reward, somethingsMissing)
     */
    Environment::Response* step(int action);

    /*
     * creates some kind of sequence of images out of the game record
     */
    void visualizeGame();

    /*
     * generates a formated string of numerical values of the play ground
     */
    string toString_PG() {
        return playingGround.toString();
    }

    /*
     * generates a formated string of numerical values of the reward map
     */
    string toString_RW() {
        return rewards.toString();
    }

    vector<int>* getActions();

    /*
     * gives the initial state of the agent in the environment
     */
    pair<int, int> *initialState();

    /*
     *
     */
    pair<int, int>* getStateByAction(int action);
};

#endif //WORLDDOMINATION_ENVIRONMENT_H