#include "feedbackcontroller.hpp"

FeedbackController::FeedbackController() : type(FCType::NotDefined) {};

FeedbackController::FeedbackController(FCType type) : type(type) {};

FeedbackController::FeedbackController(FCType type) : type(type), setpoint(setpoint) {};

void FeedbackController::setSetpoint(double setpoint) {
    this->setpoint = setpoint;
};

double FeedbackController::getSetpoint() const {
    return this->setpoint;
};

FCType FeedbackController::getType() const {
    return this->type;
};

std::ostream& operator<<(std::ostream& strm, const FeedbackController& fc) {
    strm << "Feedback controller of type ";
    switch (fc.getType()) {
        case FCType::PID:
            strm << "'PID'";
            break;
        case FCType::NotDefined:
            strm << "'Undefined'";
            break;
        default:
            strm << "'Unknown'";
            break;
    }
    strm << " with setpoint " << fc.getSetpoint() << std::endl;
};