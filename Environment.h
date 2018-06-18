#ifndef WORLDDOMINATION_ENVIRONMENT_H
#define WORLDDOMINATION_ENVIRONMENT_H

#include <vector>
#include "Num2DTable.h"
#include "gtest/gtest.h"



using namespace std;

static const pair<int, int> global_qValueSize = {3, 4};

class Environment {
friend class AgentTest;

    vector<Num2DTable> gameRecord {}; //the game is stored here as a replay
    vector<int> actionRecord {};//actions taken by the agent are stored here
    Num2DTable playingGround{pair<int, int>{3, 4}, {1, 1, 1, -1, 1, 0, 1, -1, 1, 1, 1, 1}}; //current play ground
    Num2DTable rewards{pair<int, int>{3, 4},
                       {0, 0, 0, 1, 0, 0, 0, -1, 0, 0, 0, 0}}; //possible rewards are saved here
    pair<int, int> agentPosition = pair<int, int>{2, 0};
/**
 * checks if a given position is valid
 * @param the position to be checked
 * @return whether position is valid or not
 */
    bool validPosition(pair<int,int> index) {
        return playingGround.keyExists(index) && playingGround[index] != 0;
    }

public:

    //pair<int, int> shape{3, 4};

    class Response {
    public:
        /**
         * game state
         */
        pair<int, int> *state;
        /**
         * vector of all possible actions
         */
        vector<int> options;
        /**
         * reward earned
         */
        double reward;
        /**
         * indicates if game is over
         */
        bool finished = false;

        /**
         * constructor
         * @param state after the agent chose a step
         * @param options of his new possible actions
         * @param reward after moving a step
         * @param finished whether the step has led to a game finish or not
         */
        Response(pair<int, int> *state, vector<int> options, double reward, bool finished) {
            this->state = state;
            this->options = options;
            this->reward = reward;
            this->finished = finished;
        }

/*        bool MyClass::operator!=(const Environment::Response &other) const {
            return !(*this == other);
        }*/

/*        friend bool operator==(const Response &lhs, const Response &rhs) {
            return (lhs.state == rhs.state) && (lhs.options == rhs.options) && (lhs.reward == rhs.reward) && (lhs.finished == rhs.finished);
        }

        friend bool operator!=(const Response &lhs, const Response &rhs) {
            return !(lhs == rhs);
        }*/

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
        /**
         * the game is stored here as a replay
         */
        vector<Num2DTable> gameRecord {};
        /**
         * actions taken by the agent are stored here
         */
        vector<int> actionRecord {};
        /**
         * current play ground
         */
        Num2DTable playingGround{pair<int, int>{3, 4}, {1, 1, 1, -1, 1, 0, 1, -1, 1, 1, 1, 1}};
        /**
         * possible rewards are saved here
         */
        Num2DTable rewards{pair<int, int>{3, 4},
                           {0, 0, 0, 1, 0, 0, 0, -1, 0, 0, 0, 0}};
        /**
         * the agents current position
         */
        pair<int, int> agentPosition = pair<int, int>{2, 0};
        /**
         * the playgrouds shape {rows,columns}
         */
        pair<int, int> shape{3, 4};
    }

    /**
     * takes a step in a certain direction
     * @params action: chosen action by the agent
     * @return Response (state, options, reward, finished)
     */
    Environment::Response* step(int action);

    /*
     * creates some kind of sequence of images out of the game record
     */
    //void visualizeGame();

    /**
     * generates a formated string of numerical values of the play ground
     * @return plazground as string
     */
    string toString_PG() {
        return playingGround.toString();
    }

    /**
     * generates a formated string of numerical values of the reward map
     * @return rewards as string
     */
    string toString_RW() {
        return rewards.toString();
    }

    /**
     * gives all possible actions from current state
     * @return possible actions
     */
    vector<int>* getActions();

    /**
     * gives the initial state of the agent in the environment
     * @return the initial state
     */
    pair<int, int> *initialState();

    /**
     * gives back the state corresponding to the result of an action taken from the current agent state
     * @param action to be taken
     * @return the state of given action
     */
    pair<int, int>* getStateByAction(int action);

    /**
     * resets the game
     */
    void reset();
};

#endif //WORLDDOMINATION_ENVIRONMENT_H