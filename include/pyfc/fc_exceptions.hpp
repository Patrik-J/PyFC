#ifndef FC_EXCEPTIONS_HPP
#define FC_EXCEPTIONS_HPP

#include <exception>

class FeedbackControllerException : std::exception {
    public:
        FeedbackControllerException(const char* msg);
        virtual const char* what() const throw();

    private:
        const char* msg;
};

#endif