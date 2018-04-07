//
// Created by jonas on 4/4/18.
//

#ifndef WORLDDOMINATION_ENVIRONMENT_H
#define WORLDDOMINATION_ENVIRONMENT_H

#include <vector>
//#include <tuple>


using namespace std;

static const vector<int> QValueSize = {4,3};

class Environment {

    vector<vector<vector<int>>> gameRecord; //the game is stored here as a replay
    vector<vector<int>> playingGround; //current play ground
    vector<vector<int>> rewards; //possible rewards are saved here

public:
    //static const vector<int> QValueSize;

    class Response {
    public:
        pair<int, int> state; //game state
        vector<int> options; //vector of all possible actions
        int reward; //reward earned
        bool finished = false; //indicates if game is over
    };


    /*
     * takes a step in a certain direction
     * @params action: chosen action by the agent
     * @return Response (state, options, reward, somethingsMissing)
     */
    Environment::Response step(int action);

    /*
     * creates some kind of sequence of images out of the game record
     */
    void visualizeGame();

    pair<int, int> initialState();
};

//looks ugly as fuck but apparently a static variable has to be set up as that
//const vector<int> Environment::QValueSize = {4,3};


#endif //WORLDDOMINATION_ENVIRONMENT_H
