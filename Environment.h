//
// Created by jonas on 4/4/18.
//

#ifndef WORLDDOMINATION_ENVIRONMENT_H
#define WORLDDOMINATION_ENVIRONMENT_H

#include <vector>
#include "Num2DTable.h"


using namespace std;

static const pair<int, int> QValueSize = {3, 4};//@todo this is nasty crap

class Environment {


    vector<Num2DTable> gameRecord {}; //the game is stored here as a replay
    vector<int> actionRecord {};//actions taken by the agent are stored here
    Num2DTable playingGround{pair<int, int>{3, 4}, {1, 1, 1, -1, 1, 0, 1, -1, 1, 1, 1, 1}}; //current play ground
    Num2DTable rewards{pair<int, int>{3, 4},
                       {0, 0, 0, 1, 0, 0, 0, -1, 0, 0, 0, 0}}; //possible rewards are saved here
    pair<int, int> agentPosition = pair<int, int>{2, 0};

    pair<int, int> shape{3, 4};

public:

    class Response {
    public:
        pair<int, int> *state; //game state
        vector<int> options; //vector of all possible actions
        double reward; //reward earned
        bool finished = false; //indicates if game is over

        Response(pair<int, int> *state, vector<int> options, double reward, bool finished) {
            this->state = state;
            this->options = options;
            this->reward = reward;
            this->finished = finished;
        }
    };

    Environment() {
        cout << "env const" << endl;
        vector<Num2DTable> gameRecord {}; //the game is stored here as a replay
        vector<int> actionRecord {};//actions taken by the agent are stored here
        Num2DTable playingGround{pair<int, int>{3, 4}, {1, 1, 1, -1, 1, 0, 1, -1, 1, 1, 1, 1}}; //current play ground
        Num2DTable rewards{pair<int, int>{3, 4},
                           {0, 0, 0, 1, 0, 0, 0, -1, 0, 0, 0, 0}}; //possible rewards are saved here
        pair<int, int> agentPosition = pair<int, int>{2, 0};
        pair<int, int> shape{3, 4};
        cout << "end const" << endl;
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

    pair<int, int> *initialState();
};

#endif //WORLDDOMINATION_ENVIRONMENT_H