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
    try {
        pair<int, int>* tmp = getStateByAction(action);
        if (validPosition(*tmp))
            agentPosition = (*tmp);
    } catch (int e) {
        if(e != 21)
            throw e;
    }

    bool finished = false;
    if (playingGround[agentPosition] == -1)
        finished = true;
    gameRecord.push_back(playingGround);
    actionRecord.push_back(action);
    Response* result = new Environment::Response(&agentPosition, *getActions(), rewards[agentPosition], finished);
    return result;
}

void Environment::visualizeGame() {
    //@todo visualize gameRecord
}

vector<int>* Environment::getActions() {
    vector<int>* actions = new vector<int> {};
    for(int a = 0; a < 4; a++) {
        try {
            getStateByAction(a);//variable not needed just call it so it raises an exception if not valid
            actions->push_back(a);
        } catch (int e) {
            if(e != 21)
                throw e;
        }
    }
    return actions;
}

pair<int, int> *Environment::getStateByAction(int action) {
    if(action < 0 || action > 3)
        throw 20;
    pair<int,int>* result;
    if(action == 0){
        result = new pair<int,int> {agentPosition.first - 1, agentPosition.second};
    }
    else if(action == 1){
        result = new pair<int,int> {agentPosition.first, agentPosition.second + 1};
    }
    else if(action == 2){
        result = new pair<int,int> {agentPosition.first + 1, agentPosition.second};
    }
    else if(action == 3){
        result = new pair<int,int> {agentPosition.first, agentPosition.second - 1};
    }
    if (!validPosition( *result)) {
        //throw invalid action exception
        throw 21;
    }
    return result;
}

