#ifndef ROUND
#define ROUND

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
using namespace std;

namespace sb{

    class Game;

    class Round{

        int roundNumber;
        int status;
        int currThrow;

        int firstThrow;
        int secondThrow;
        int pinsDown;

        string statusStrings[4];

    public:

        Round();
        friend class Game;
        enum endResultStatus{WORKING, SPARE, STRIKE, OVER};

        void knockPins(int pinsKnocked);

    };

}//END SB
#endif // ROUND
