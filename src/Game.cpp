#include "../include/Game.hpp"
using namespace sb;

Game::Game(){

    finalRound = 9;
    runningScore = 0;
    currRound = 0;

    /**prepare rounds*/
    for(int i = 0; i < 11; ++i)
        allRounds[i].roundNumber = i;

    /**prepare scoreboard*/
    for(int currRound = 0; currRound < 10; ++currRound){
        for(int currSlot = 0; currSlot < 4; ++currSlot){
            scoreBoard[currRound][currSlot] = slotStatus::Vacant;
        }
    }
}

void Game::throwBall(int pinsKnocked){


    if(currRound > finalRound){
        cerr << "Game Over, no more bowls" << endl;
        return;
    }

    /**Throws exception for invalid pinsKnocked*/
    allRounds[currRound].knockPins(pinsKnocked);

    runningScore += pinsKnocked;

    /**Handle contracts for previous rounds*/
    handleContracts(pinsKnocked);


    if(allRounds[currRound].status == Round::STRIKE){
        roundContracts.push_back(Contract(&allRounds[currRound], 2));

        scoreBoard[currRound][slotID::SecondThrow] = slotStatus::Strike;
        if(currRound == 9){
            scoreBoard[currRound][slotID::FirstThrow] = slotStatus::Strike;
            scoreBoard[currRound][slotID::SecondThrow] = slotStatus::Vacant;
        }
        /**round 9 strike*/
        if(allRounds[9].status == Round::STRIKE && currRound == 10){

            if(allRounds[10].currThrow == 2)
                scoreBoard[9][slotID::SecondThrow] = slotStatus::Strike;
            else if(allRounds[10].currThrow == 3){
                scoreBoard[9][slotID::ThirdThrow] = 111;
            }
        }

        if(currRound == 9){
            ++finalRound;
        }
        if(currRound != 10)
            ++currRound;
    }else if(allRounds[currRound].status == Round::SPARE){
        roundContracts.push_back(Contract(&allRounds[currRound], 1));

        scoreBoard[currRound][slotID::SecondThrow] = slotStatus::Spare;

        /**round 9 strike*/
        if(allRounds[9].status == Round::STRIKE && currRound == 10){
            scoreBoard[9][slotID::ThirdThrow] = slotStatus::Spare;
            scoreBoard[currRound][slotID::RunningTotal] = getRunningScore(finalRound);
        }

        /**round 9 spare*/
        if(allRounds[9].status == Round::SPARE && currRound == 10){
            scoreBoard[9][slotID::ThirdThrow] = slotStatus::Strike;
            scoreBoard[9][slotID::RunningTotal] = getRunningScore(finalRound - 1);
        }

        if(currRound == 9){
            ++finalRound;
            allRounds[10].currThrow++;
        }
        ++currRound;
    }else if(allRounds[currRound].status == Round::OVER){
        scoreBoard[currRound][slotID::SecondThrow] = pinsKnocked;
        scoreBoard[currRound][slotID::RunningTotal] = getRunningScore(currRound);

        /**round 9 strike*/
        if(allRounds[9].status == Round::STRIKE && currRound == 10){

            scoreBoard[9][slotID::ThirdThrow] = pinsKnocked;
            if(pinsKnocked == 10){
                scoreBoard[9][slotID::ThirdThrow] = slotStatus::Strike;
            }
            scoreBoard[currRound][slotID::RunningTotal] = getRunningScore(finalRound);
        }

        /**round 9 spare*/
        if(allRounds[9].status == Round::SPARE && currRound == 10){
            scoreBoard[9][slotID::ThirdThrow] = pinsKnocked;
            scoreBoard[9][slotID::RunningTotal] = getRunningScore(finalRound - 1);
        }

        ++currRound;
    }else if(allRounds[currRound].status == Round::WORKING){
        scoreBoard[currRound][slotID::FirstThrow] = pinsKnocked;

        /**round 9 strike*/
        if(allRounds[9].status == Round::STRIKE && currRound == 10){
            scoreBoard[9][slotID::SecondThrow] = pinsKnocked;
        }
    }
}

int Game::getRunningScore(int upperLimit){
    runningScore = 0;
    for(int i = 0; i <= upperLimit; ++i){
        runningScore += allRounds[i].pinsDown;
    }
    return runningScore;
}
int Game::getRunningScore(){
    int index = 0;

    if(isGameOver())
        return scoreBoard[roundID::R10][slotID::RunningTotal];
    if(scoreBoard[roundID::R1][slotID::RunningTotal] == slotStatus::Vacant)
        return 0;
    while(scoreBoard[index][slotID::RunningTotal] != slotStatus::Vacant){
        ++index;
    }
    --index;
    return scoreBoard[index][slotID::RunningTotal];
}
void Game::displayRawData(){

    cout << endl <<
            "-----------------------------------RAW DATA-----------------------------------\n" << endl;

    cout << "   ROUND INDEX      FIRST THROW     SECOND THROW   TOTAL PINS DOWN      STATUS" << endl;
    cout << "   -----------      -----------     ------------   ---------------      ------" << endl;

    for(int i = 0; i <= finalRound; ++i){

        if(i == currRound){
            cout << "\t" << i << "\t\t" << allRounds[i].firstThrow << "\t\t" << allRounds[i].secondThrow << "\t\t" << allRounds[i].pinsDown << "\t\t<----Throw # " << allRounds[i].currThrow << endl;
        }else{
            cout << "\t" << i << "\t\t" << allRounds[i].firstThrow << "\t\t" << allRounds[i].secondThrow << "\t\t" << allRounds[i].pinsDown << "\t\t" << allRounds[i].statusStrings[allRounds[i].status] << endl;
        }
    }
    cout << "Current Score: " << getRunningScore(finalRound) << endl;
}

bool Game::isGameOver(){
    return currRound > finalRound;
}

void Game::handleContracts(int pinsKnocked){

    for(vector<Contract>::iterator iter = roundContracts.begin(); iter < roundContracts.end(); ++iter){
        iter->round->pinsDown += pinsKnocked;
        --(iter->times);
        if(iter->times == 0){
            int boardIndex = iter->round->roundNumber;

            scoreBoard[boardIndex][slotID::RunningTotal] = getRunningScore(iter->round->roundNumber);

            roundContracts.erase(iter);
            --iter;
        }
    }
}

int Game::scoreBoardValueAt(int roundID, int slotID){

    return scoreBoard[roundID][slotID];
}
string Game::scoreBoardSymbolAt(int roundID, int slotID){
    if(scoreBoard[roundID][slotID] == slotStatus::Vacant)
        return string("");
    else if(scoreBoard[roundID][slotID] == slotStatus::Spare)
        return "/";
    else if(scoreBoard[roundID][slotID] == slotStatus::Strike)
        return "X";
    else
        return to_string(scoreBoard[roundID][slotID]);
}
void Game::displayScoreBoard(){

    cout << endl <<
            "-----------------------------------SCORE BOARD-----------------------------------\n" << endl;

    cout << "      ROUND    FIRST  SECOND   TOTAL  THIRD" << endl;
    cout << "      -----    -----  ------   -----  -----" << endl;
    for(int currRound = 0; currRound < 10; ++currRound){
        cout << "\t" << currRound + 1;
        for(int currSlot = 0; currSlot < 4; ++currSlot){

            if(scoreBoard[currRound][currSlot] == slotStatus::Vacant)
                cout << "\t" << "_";
            else if(scoreBoard[currRound][currSlot] == slotStatus::Strike)
                cout << "\t" << "X";
            else if(scoreBoard[currRound][currSlot] == slotStatus::Spare)
                cout << "\t" << "/";
            else
                cout << "\t" << scoreBoard[currRound][currSlot];
        }
        if(currRound == this->currRound){
            cout << "  <----Throw # " << allRounds[currRound].currThrow << endl;
        }else{
            cout << endl;
        }
    }
}

template<typename T>
string Game::to_string(const T &value){
    std::ostringstream stm;
    stm << value;
    return stm.str();
}

