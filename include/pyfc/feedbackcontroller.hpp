#ifndef FEEDBACKCONTROLLER_HPP
#define FEEDBACKCONTROLLER_HPP

#include <sstream>

#include "fc_exceptions.hpp"

enum FCType {
    NotDefined,
    PID
};  

class FeedbackController {
    public:
        FeedbackController();
        FeedbackController(FCType type);
        FeedbackController(FCType type, double setpoint);

        virtual double request_loop(double input) = 0;
        virtual void init() = 0;

        void setSetpoint(double setpoint);
        double getSetpoint() const;
        FCType getType() const;

        friend std::ostream& operator<<(std::ostream& strm, const FeedbackController& fc);

    protected:
        FCType type;
        double setpoint = 0.0;
};

#endif 