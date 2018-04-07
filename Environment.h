//
// Created by jonas on 4/4/18.
//

#ifndef WORLDDOMINATION_ENVIRONMENT_H
#define WORLDDOMINATION_ENVIRONMENT_H

#include <vector>
#include <tuple>

using namespace std;

class Environment {
    vector<vector<vector<int>>> gameRecord; //the game is stored here as a replay
    vector<vector<int>> playingGround; //current play ground
    vector<vector<int>> rewards; //possible rewards are saved here


public:
    static tuple<int, int> gameSize;// = {4,3};

    class Response {
    public:
        tuple<int, int> state; //game state
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

    tuple<int, int> initialState();
};


#endif //WORLDDOMINATION_ENVIRONMENT_H
