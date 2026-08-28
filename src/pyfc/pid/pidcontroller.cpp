#include "pidcontroller.hpp"

PIDController::PIDController() : FeedbackController(FCType::PID) {};

PIDController::PIDController(DoubleVector params, double setpoint) : FeedbackController(FCType::PID, setpoint) {
    this->params = params;
};

double PIDController::requestLoop(double input) {
    if (this->params.size() != 3)
        throw FeedbackControllerException("PID params were not set!");
    
    // get the difference to use in the PID loop
    double diff = input - this->setpoint;

    // get the next index
    unsigned int lii = (this->last_input_index + 1) % PIDController::MAX_STORED;
    
    // store the new point
    this->last_points[lii] = diff;
    this->last_times[lii] = this->timer.currentMicros();
    this->last_input_index = lii;

    // sum of all three parts
    double sum = 0.0;

    // proportional
    sum += this->params[0] * diff;

    // integral
    this->integrate();
    sum += this->params[1] * this->time_integral;

    // derivative
    this->differentiate();
    sum += this->params[2] * this->derivative;

    // return the sum
    return sum;
};

void PIDController::init() {
    this->timer = Timer();
    this->timer.start();
    this->last_points = new double[PIDController::MAX_STORED] {0.0};
    this->last_times = new double[PIDController::MAX_STORED] {0.0};
    this->last_input_index = 0;

    if (this->params.size() == 0)
        this->params = randomVector(3);
};

void PIDController::setCaps(double time_integral, double derivative) {
    this->ti_cap = time_integral;
    this->dv_cap = derivative;
};

DoubleVector PIDController::getCaps() {
    return {this->ti_cap, this->dv_cap};
};

void PIDController::setGains(DoubleVector gains) {
    this->params = gains;
};

DoubleVector PIDController::getGains() {
    return this->params;
};

void PIDController::integrate() {
    double dt = this->last_times[this->last_input_index] - this->last_times[(this->last_input_index - 1) % PIDController::MAX_STORED];
    double dI = this->last_points[this->last_input_index] - this->last_points[(this->last_input_index - 1) % PIDController::MAX_STORED];

    this->time_integral += dt * dI;

    if (abs(this->time_integral) > this->ti_cap) 
        this->time_integral = sign(this->time_integral) * this->ti_cap;
};

void PIDController::differentiate() {
    // three-point central difference formula
    unsigned int lii = this->last_input_index;
    unsigned int li = (lii - 1) % PIDController::MAX_STORED;
    unsigned int l = (li - 1) % PIDController::MAX_STORED;
    
    // t_i+1 - t-i
    double h1 = this->last_times[lii] - this->last_times[li];  
    
    // t_i - t_i-1
    double h2 = this->last_times[li] - this->last_times[l];

    // simple fail-safe, if dt = 0 
    if (h1 == 0) 
        h1 = 1e-20;
    if (h2 == 0)
        h2 = 1e-20;
    
    // y_i
    double I0 = this->last_points[lii];
    
    // y_i-1
    double I1 = this->last_points[li];
    
    // y_i-2
    double I2 = this->last_points[l];

    double coeff0 = (2 * h1 + h2)/(h1 * (h1 + h2));
    double coeff1 = (h1 + h2)/(h1 * h2);
    double coeff2 = h1/(h2 * (h1 + h2));

    this->derivative = coeff0 * I0 + coeff1 * I1 + coeff2 * I2;
    
    if (abs(this->derivative) > this->dv_cap) 
        this->derivative = sign(this->derivative) * this->dv_cap;
};