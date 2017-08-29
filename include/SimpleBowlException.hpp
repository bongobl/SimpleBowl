#ifndef SIMPLE_BOWL_EXCEPTION
#define SIMPLE_BOWL_EXCEPTION

#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;

namespace sb{

    class SimpleBowlException : public std::exception{

        int roundNumber;
        int invalidPins;
        string message;

    public:
        SimpleBowlException(int r, int i) : roundNumber(r), invalidPins(i) {
            ostringstream error_message;

            error_message << "SimpleBowlException():" << endl;
            if(roundNumber == 10)
                error_message << "Round " << roundNumber << ": Pins Knocked = " << invalidPins << ", exceeds 10" << endl;
            else
                error_message << "Round " << roundNumber << ": Pins Down = " << invalidPins << ", exceeds 10" << endl;
            message = error_message.str();
        }

        virtual const char* what() const throw() {
            return message.c_str();
        }
    };
}
#endif // SIMPLE_BOWL_EXCEPTION
