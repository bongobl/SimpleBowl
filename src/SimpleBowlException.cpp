#include "../include/SimpleBowlException.hpp"
using namespace sb;

SimpleBowlException::SimpleBowlException(int r, int i, string mes) : roundNumber(r), invalidPins(i), message(mes) {


}

SimpleBowlException::~SimpleBowlException() throw() {

}

const char* SimpleBowlException::what() const throw() {
    return message.c_str();
}
