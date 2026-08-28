#include "autooptpid.hpp"

AutoOptimizingPID::AutoOptimizingPID() {};

AutoOptimizingPID::AutoOptimizingPID(double setpoint) {
    DoubleVector randomParams = randomVector(3);
    this->pid = PIDController(randomParams, setpoint);
};

AutoOptimizingPID::AutoOptimizingPID(DoubleVector params, double setpoint) {
    this->pid = PIDController(params, setpoint);
};

AutoOptimizingPID::AutoOptimizingPID(PIDController pid) {
    this->pid = pid;
};

double AutoOptimizingPID::step(double input) {
    // perform a single PID step
    return this->pid.request_loop(input);
};

void AutoOptimizingPID::optimize(double new_input) {
    // determine the error between the setpoint and the new input
    double err = this->pid.getSetpoint() - new_input;
    double error = 0.5*std::pow(err, 2);

    // gradient
    DoubleVector grad;
    
    // prior point
    unsigned int prior_idx = (this->pid.last_input_index - 1) % PIDController::MAX_STORED;
    double prior_input = this->pid.last_points[prior_idx];

    // the derivatives wrt. to each parameter
    grad.push_back(prior_input);
    grad.push_back(this->pid.time_integral);
    grad.push_back(this->pid.derivative);

    grad *= err;

    // gradient descent
    this->pid.params -= this->lr * grad;
    
};

void AutoOptimizingPID::setLearningRate(double lr) {
    this->lr = lr;
};

double AutoOptimizingPID::getLearningRate() {
    return this->lr;
};

PIDController AutoOptimizingPID::getPIDController() {
    return this->pid;
};
