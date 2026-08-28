#include "fc_exceptions.hpp"

FeedbackControllerException::FeedbackControllerException(const char* msg) : msg(msg) {};

const char* FeedbackControllerException::what() const throw() {
    return this->msg;
};

VectorMathException::VectorMathException(const char* msg) : msg(msg) {};

const char* VectorMathException::what() const throw() {
    return this->msg;
};