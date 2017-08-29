/**
 * This is the working version of the SimpleBowl API
 **/

#ifndef GAME
#define GAME

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "SimpleBowlException.hpp"
#include "Round.hpp"
#include "Contract.hpp"

using namespace std;

namespace sb{

    namespace roundID{

        const int R1 = 0;
        const int R2 = 1;
        const int R3 = 2;
        const int R4 = 3;
        const int R5 = 4;
        const int R6 = 5;
        const int R7 = 6;
        const int R8 = 7;
        const int R9 = 8;
        const int R10 = 9;
    }

    namespace slotID{

        const int FirstThrow = 0;
        const int SecondThrow = 1;
        const int RunningTotal = 2;
        const int ThirdThrow = 3;

    }
    namespace slotStatus{
        const int Vacant = -1;
        const int Spare = -2;
        const int Strike = -3;
    }

    class Round;

    class Game{

        int finalRound;
        int runningScore;
        int currRound;
        Round allRounds[11];

        vector<Contract> roundContracts;
        int scoreBoard[10][4];
    public:
        Game();
        void throwBall(int pinsKnocked);
        int getRunningScore(int upperLimit);
        int getRunningScore();
        void displayRawData();
        bool isGameOver();
        int scoreBoardValueAt(int roundID, int slotID);
        string scoreBoardSymbolAt(int roundID, int slotID);
        void displayScoreBoard();

    private:
        void handleContracts(int pinsKnocked);

        template<typename T>
        std::string to_string(const T &value);

    };

}
#endif // GAME
