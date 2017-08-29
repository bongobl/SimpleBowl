#include <iostream>
#include <stdexcept>
#include "Game.hpp"
using namespace std;


int main(void){

    sb::Game bowlingGame;

    bowlingGame.displayScoreBoard();
    while(!bowlingGame.isGameOver()){
        int throwVal = 0;
        cout << "ThrowAmount: ";
        cin >> throwVal;
        try{
            bowlingGame.throwBall(throwVal);
        }catch(sb::SimpleBowlException a){

            cout << a.what() << "\nmain(): Call throwBall with a valid number of pins" << endl;
            continue;
        }
        bowlingGame.displayScoreBoard();

    }
    cout << "Scoreboard value: " << bowlingGame.scoreBoardValueAt(sb::roundID::R3, sb::slotID::RunningTotal) << endl;
    return 0;
}