#ifndef AUTOOPTPID_HPP
#define AUTOOPTPID_HPP

#include "pidcontroller.hpp"

class AutoOptimizingPID {
    public:
        AutoOptimizingPID();
        AutoOptimizingPID(double setpoint);
        AutoOptimizingPID(DoubleVector params, double setpoint);
        AutoOptimizingPID(PIDController pid);

        // perform a normal PID step
        double step(double input);
        // optimize the params wrt. to a new value
        void optimize(double new_input);

        void setLearningRate(double lr);
        double getLearningRate();

        PIDController getPIDController();

    private:
        PIDController pid;
        double lr = 1e-3;
};

#endif