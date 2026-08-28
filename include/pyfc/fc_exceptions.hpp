#ifndef FC_EXCEPTIONS_HPP
#define FC_EXCEPTIONS_HPP

#include <exception>

class FeedbackControllerException : public std::exception {
    public:
        FeedbackControllerException(const char* msg);
        virtual const char* what() const throw();

    private:
        const char* msg;
};

class VectorMathException : public std::exception {
    public:
        VectorMathException(const char* msg);
        virtual const char* what() const throw();

    private:
        const char* msg;
};

#endif