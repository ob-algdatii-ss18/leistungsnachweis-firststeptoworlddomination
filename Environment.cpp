//
// Created by jonas on 4/4/18.
//

#include <iostream>
#include "Environment.h"

using namespace std;

/*
 * gives back the initial state of the game
 * This might be changed to a random one later on
 */
pair<int, int> *Environment::initialState() {
    pair<int, int> *result = new pair<int, int>{2, 0};
    return result;//fixed initial state
}

/*
 * changes the state of the game by taking a step.
 * @param action: action the agent choses
 */
Environment::Response* Environment::step(int action) {

    //move the agent
    pair<int, int> tmp {agentPosition.first - 1, agentPosition.second};
    if (action == 0 && playingGround.keyExists(tmp) && playingGround[tmp] != 0) {
        agentPosition = tmp;
    }

    tmp = {agentPosition.first + 1, agentPosition.second};
    if (action == 2 && playingGround.keyExists(tmp) && playingGround[tmp] != 0){
        agentPosition = tmp;
    }

    tmp = {agentPosition.first, agentPosition.second + 1};
    if (action == 1 && playingGround.keyExists(tmp) && playingGround[tmp] != 0) {
        agentPosition = tmp;
    }

    tmp = {agentPosition.first, agentPosition.second - 1};
    if (action == 3 && playingGround.keyExists(tmp) && playingGround[tmp] != 0) {
        agentPosition = tmp;
    }
    //cout << "agent pos: " << agentPosition.first <<","<<agentPosition.second<<endl;

    //setting actions for response
    vector<int> actions {};
    if(playingGround.keyExists({agentPosition.first - 1, agentPosition.second}))
        actions.push_back(0);
    if(playingGround.keyExists({agentPosition.first + 1, agentPosition.second}))
        actions.push_back(2);
    if(playingGround.keyExists({agentPosition.first, agentPosition.second + 1}))
        actions.push_back(1);
    if(playingGround.keyExists({agentPosition.first, agentPosition.second - 1}))
        actions.push_back(3);

    bool finished = false;
    if (playingGround[agentPosition] == -1)
        finished = true;
    gameRecord.push_back(playingGround);
    actionRecord.push_back(action);
    Response* result = new Environment::Response(&agentPosition, actions, rewards[agentPosition], finished);
    return result;
}

void Environment::visualizeGame() {
    //@todo visualize gameRecord
}

