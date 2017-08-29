#ifndef SIMPLE_BOWL_EXCEPTION
#define SIMPLE_BOWL_EXCEPTION

#include <stdexcept>
#include <string>

using namespace std;

namespace sb{

    class SimpleBowlException : public std::exception{

        int roundNumber;
        int invalidPins;
        string message;

    public:
        SimpleBowlException(int r, int i, string mes) : roundNumber(r), invalidPins(i), message(mes) {

        }

        ~SimpleBowlException() throw() {};

        virtual const char* what() const throw() {
            return message.c_str();
        }
    };
} //END SB
#endif // SIMPLE_BOWL_EXCEPTION
