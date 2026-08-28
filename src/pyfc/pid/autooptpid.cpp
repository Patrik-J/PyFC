#include "autooptpid.hpp"

AutoOptimizingPID::AutoOptimizingPID() : FeedbackController(FCType::AutoOptPID) {};

AutoOptimizingPID::AutoOptimizingPID(DoubleVector initialParams, double setpoint, double lr) : FeedbackController(FCType::AutoOptPID, setpoint) {
    this->params = initialParams;
    this->lr = lr;
};

AutoOptimizingPID::AutoOptimizingPID(double setpoint, double lr) : FeedbackController(FCType::AutoOptPID, setpoint) {
    this->lr = lr;
};

AutoOptimizingPID::~AutoOptimizingPID() {
    delete[] this->last_points;
    delete[] this->last_times;
};

double AutoOptimizingPID::requestLoop(double input) {   
    if (!this->intialized) 
        throw FeedbackControllerException("Feedback controller was not initialized! Use .init()");
    
    // get the difference to use in the PID loop
    double diff = input - this->setpoint;

    // get the next index
    unsigned int lii = (this->last_input_index + 1) % AutoOptimizingPID::MAX_STORED;
    
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

    // prior to the next step, optimize the params
    this->optimize();

    // return the sum
    return sum;
};

void AutoOptimizingPID::init() {
    this->timer = Timer();
    this->timer.start();
    this->last_points = new double[AutoOptimizingPID::MAX_STORED] {0.0};
    this->last_times = new double[AutoOptimizingPID::MAX_STORED] {0.0};
    this->last_input_index = 0;

    if (this->params.size() == 0)
        this->params = randomVector(3);
    this->intialized = true;
};

void AutoOptimizingPID::setLearningRate(double lr) {
    this->lr = lr;
};

double AutoOptimizingPID::getLearningRate() {
    return this->lr;
};

void AutoOptimizingPID::setCaps(double time_integral, double derivative) {
    this->ti_cap = time_integral;
    this->dv_cap = derivative;
};

DoubleVector AutoOptimizingPID::getCaps() {
    return {this->ti_cap, this->dv_cap};
};

PIDController AutoOptimizingPID::getAsPIDController() {
    PIDController pid(this->params, this->setpoint);
    return pid;
};

void AutoOptimizingPID::integrate() {
    double dt = this->last_times[this->last_input_index] - this->last_times[(AutoOptimizingPID::MAX_STORED + this->last_input_index - 1) % AutoOptimizingPID::MAX_STORED];
    double dI = (this->last_points[this->last_input_index] + this->last_points[(AutoOptimizingPID::MAX_STORED + this->last_input_index - 1) % AutoOptimizingPID::MAX_STORED]) / 2.0;

    this->time_integral += dt * dI;

    if (std::abs(this->time_integral) > this->ti_cap) 
        this->time_integral = sign(this->time_integral) * this->ti_cap;
};

void AutoOptimizingPID::differentiate() {
    // three-point central difference formula
    unsigned int lii = this->last_input_index;
    unsigned int li = (AutoOptimizingPID::MAX_STORED + lii - 1) % AutoOptimizingPID::MAX_STORED;
    unsigned int l = (AutoOptimizingPID::MAX_STORED + li - 1) % AutoOptimizingPID::MAX_STORED;
    
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
    
    if (std::abs(this->derivative) > this->dv_cap) 
        this->derivative = sign(this->derivative) * this->dv_cap;
};

void AutoOptimizingPID::optimize() {
    // determine the error between the setpoint and the input
    double diff = this->last_points[this->last_input_index];
    double error = 0.5*std::pow(diff, 2);

    // gradient
    DoubleVector grad;
    
    // the derivatives wrt. to each parameter
    grad.push_back(diff);
    grad.push_back(this->time_integral);
    grad.push_back(this->derivative);

    grad *= diff;

    // gradient descent
    this->params -= this->lr * grad;
};