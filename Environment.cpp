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

    if (action == 0 && agentPosition.first > 0)
        agentPosition = pair<int, int>{agentPosition.first - 1, agentPosition.second};

    else if (action == 2 && agentPosition.first < shape.first)
        agentPosition = pair<int, int>{agentPosition.first + 1, agentPosition.second};

    else if (action == 1 && agentPosition.second < shape.second)
        agentPosition = pair<int, int>{agentPosition.first, agentPosition.second + 1};

    else if (action == 3 && agentPosition.second > 0)
        agentPosition = pair<int, int>{agentPosition.first, agentPosition.second - 1};

    bool finished = false;
    if (playingGround[agentPosition] == -1)
        finished = true;
    gameRecord.push_back(playingGround);
    actionRecord.push_back(action);
    Response* result = new Environment::Response(&agentPosition, {0}, rewards[agentPosition], finished);
    return result;
}

void Environment::visualizeGame() {
    //@todo visualize gameRecord
}

