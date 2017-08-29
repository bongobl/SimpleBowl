#include "../include/Round.hpp"
#include "../include/SimpleBowlException.hpp"
using namespace sb;

Round::Round(){

    status = WORKING;
    currThrow = 1;

    firstThrow = -1;
    secondThrow = -1;

    pinsDown = 0;

    statusStrings[0] = "working";
    statusStrings[1] = "SPARE";
    statusStrings[2] = "STRIKE";
    statusStrings[3] = "over";
}

void Round::knockPins(int pinsKnocked){

    pinsDown += pinsKnocked;

    /**Error Handling*/
    if(roundNumber == 10){
        if(pinsKnocked > 10){

            pinsDown -= pinsKnocked;
            throw SimpleBowlException(roundNumber, pinsKnocked);
        }
        if(status != STRIKE && pinsDown > 10){
            pinsDown -= pinsKnocked;

            throw SimpleBowlException(roundNumber, pinsKnocked + pinsDown);
        }
    }
    else if(pinsDown > 10){
        pinsDown -= pinsKnocked;
        throw SimpleBowlException(roundNumber, pinsKnocked + pinsDown);
    }

    /**logic*/
    if(currThrow == 1){
        firstThrow = pinsKnocked;
        if(pinsDown == 10){
            status = STRIKE;
            secondThrow = 0;
        }
    }if(currThrow == 2){
        secondThrow = pinsKnocked;
        if(pinsDown == 10)
            status = SPARE;
        else
            status = OVER;
    }

    ++currThrow;
}
