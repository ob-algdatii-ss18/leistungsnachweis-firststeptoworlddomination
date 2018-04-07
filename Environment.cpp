//
// Created by jonas on 4/4/18.
//

#include "Environment.h"

using namespace std;

/*
 * gives back the initial state of the game
 * This might be changed to a random one later on
 */
pair<int, int> Environment::initialState() {
    return {0,0};//fixed initial state
}

/*
 * changes the state of the game by taking a step.
 * @param action: action the agent choses
 */
Environment::Response Environment::step(int action) {
    //@todo move the agent
    //@todo look for reward
    //@todo feedback if finished
    gameRecord.push_back(playingGround);
    return Environment::Response();
}

void Environment::visualizeGame() {
    //@todo visualize gameRecord
}

