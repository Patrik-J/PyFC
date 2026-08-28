#ifndef PIDCONTROLLER_HPP
#define PIDCONTROLLER_HPP

#include "feedbackcontroller.hpp"
#include "timer.hpp"

class PIDController : public FeedbackController {
    
    static inline const unsigned int MAX_STORED = 5;
    
    public:
        PIDController();
        PIDController(DoubleVector params, double setpoint);

        double request_loop(double input) override;
        void init() override;

        void setCaps(double time_integral, double derivative);
        DoubleVector getCaps();

        void setGains(DoubleVector gains);
        DoubleVector getGains();

    private:
        // param 0: proportional gain
        // param 1: integral gain
        // param 2: derivative gain
        DoubleVector params;

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
};

#endif