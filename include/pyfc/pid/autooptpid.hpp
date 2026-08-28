#ifndef AUTOOPTPID_HPP
#define AUTOOPTPID_HPP

#include "feedbackcontroller.hpp"
#include "pidcontroller.hpp"

class AutoOptimizingPID : public FeedbackController {
    static inline const unsigned int MAX_STORED = 3;

    public:
        AutoOptimizingPID();
        AutoOptimizingPID(DoubleVector initialParams, double setpoint, double lr = 1e-3);
        AutoOptimizingPID(double setpoint, double lr = 1e-3);
        ~AutoOptimizingPID();

        double requestLoop(double input) override;
        void init() override;

        void setLearningRate(double lr);
        double getLearningRate();

        void setCaps(double time_integral, double derivative);
        DoubleVector getCaps();

        PIDController getAsPIDController();

    private:
        // param 0: proportional gain
        // param 1: integral gain
        // param 2: derivative gain
        DoubleVector params;

        // learning rate for gradient descent
        double lr = 1e-3;

        // storage for integral and derivative
        double* last_points;
        double* last_times;
        unsigned int last_input_index = 0;

        // time integral
        double time_integral = 0.0;
        double ti_cap = 0.0;    // to prevent overshooting

        // derivative
        double derivative = 0.0;
        double dv_cap = 0.0;    // to prevent overshooting

        // timer for time steps
        Timer timer;

        // functions
        void integrate();
        void differentiate();
        void optimize();
};

#endif