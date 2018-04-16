//
// Created by jonas on 4/4/18.
//

#include <iostream>
#include "Environment.h"

using namespace std;

pair<int, int> *Environment::initialState() {
    pair<int, int> *result = new pair<int, int>{2, 0};//change it to random later on
    return result;//fixed initial state
}

Environment::Response* Environment::step(int action) {
    //move the agent
    //up
    pair<int, int> tmp {agentPosition.first - 1, agentPosition.second};
    if (action == 0 && validPosition(tmp)) {
        agentPosition = tmp;
    }
    //down
    tmp = {agentPosition.first + 1, agentPosition.second};
    if (action == 2 && validPosition(tmp)){
        agentPosition = tmp;
    }
    //right
    tmp = {agentPosition.first, agentPosition.second + 1};
    if (action == 1 && validPosition(tmp)) {
        agentPosition = tmp;
    }
    //left
    tmp = {agentPosition.first, agentPosition.second - 1};
    if (action == 3 && validPosition(tmp)) {
        agentPosition = tmp;
    }

    //setting actions for response
    vector<int> actions {};
    if(validPosition({agentPosition.first - 1, agentPosition.second})){
        actions.push_back(0);
    }
    if(validPosition({agentPosition.first + 1, agentPosition.second})){
        actions.push_back(2);
    }
    if(validPosition({agentPosition.first, agentPosition.second + 1})){
        actions.push_back(1);
    }
    if(validPosition({agentPosition.first, agentPosition.second - 1})){
        actions.push_back(3);
    }

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

