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
    //@todo actions = *getActions();

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

vector<int>* Environment::getActions() {
    //@todo use it somewhere
    vector<int>* actions = new vector<int> {};
    //cout << "reached getActions"<<endl;
    for(int a = 0; a < 4; a++) {
        try {
            //cout<<"try "<<a<<endl;
            getStateByAction(a);//variable not needed just call it so it raises an exception if not valid
            actions->push_back(a);
        } catch (int e) {
            //cout<<"catch"<<endl;
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
        throw 21;
    }
    return result;
}

