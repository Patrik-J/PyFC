#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "feedbackcontroller.hpp"
#include "timer/timer.hpp"
#include "pid/pidcontroller.hpp"
#include "pid/autooptpid.hpp"
#include "fc_exceptions.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    m.doc() = "Bindings for the PyFC module.";

    // exceptions
    static py::exception<FeedbackControllerException> fc_exc(m, "FeedbackControllerException");
    static py::exception<VectorMathException> vm_exc(m, "VectorMathException");


    // Timer class
    py::class_<Timer>(m, "Timer")
    .def(py::init(), "Create an instance of the Timer class")
    .def("start", &Timer::start, "Set the start time of the timer.")
    .def("millis", &Timer::currentMillis, "Get the milliseconds since the timer was started")
    .def("micros", &Timer::currentMicros, "Get the microseconds since the timer was started");

    // base FeedbackController class
    py::class_<FeedbackController>(m, "FeedbackController")
    .def("setSetpoint", &FeedbackController::setSetpoint, py::arg("setpoint"), "Set the setpoint of the feedback controller.")
    .def("getSetpoint", &FeedbackController::getSetpoint, "Get the setpoint of the feedback controller.")
    .def("__repr__", [](const FeedbackController &self) {
        std::ostringstream oss;
        oss << self;
        return oss.str();
    });

    // PIDController class
    py::class_<PIDController, FeedbackController>(m, "PIDController")
    .def(py::init<DoubleVector, double>(), py::arg("params"), py::arg("setpoint"))
    .def("requestLoop", &PIDController::requestLoop, py::arg("input"), "Request a single loop of the PID controller.")
    .def("init", &PIDController::init, "Initialize the PID controller")
    .def("setCaps", &PIDController::setCaps, py::arg("time_integral"), py::arg("derivative"), "Set the upper and lower caps of the integral and derivative.")
    .def("getCaps", &PIDController::getCaps, "Get the upper and lower caps of the integral and derivative.")
    .def("setGains", &PIDController::setGains, py::arg("gains"),"Set the parameter gains of the PID controller.")
    .def("getGains", &PIDController::getGains, "Get the parameter gains of the PID controller.");

    // AutoOptimizingPID class
    py::class_<AutoOptimizingPID, FeedbackController>(m, "AutoOptimizingPID")
    .def(py::init<DoubleVector, double, double>(), py::arg("params"), py::arg("setpoint"), py::arg("lr") = 1e-3)
    .def(py::init<double, double>(), py::arg("setpoint"), py::arg("lr") = 1e-3)
    .def("requestLoop", &AutoOptimizingPID::requestLoop, py::arg("input"), "Request a single loop of the auto-optimizing PID controller.")
    .def("init", &AutoOptimizingPID::init, "Initialize the auto-optimizing PID controller")
    .def("setCaps", &AutoOptimizingPID::setCaps, py::arg("time_integral"), py::arg("derivative"), "Set the upper and lower caps of the integral and derivative.")
    .def("getCaps", &AutoOptimizingPID::getCaps, "Get the upper and lower caps of the integral and derivative.")
    .def("setLearningRate", &AutoOptimizingPID::setLearningRate, py::arg("lr"), "Set the learning rate of the gradient descent algorithm.")
    .def("getLearningRate", &AutoOptimizingPID::getLearningRate, "Get the learning rate of the gradient descent algorithm.")
    .def("getAsPID", &AutoOptimizingPID::getAsPIDController, "Get the auto-optimizing PID controller as a simple PID controller.");
};