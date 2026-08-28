"""
Bindings for the PyFC module.
"""
from __future__ import annotations
import collections.abc
import typing
__all__: list[str] = ['AutoOptimizingPID', 'FeedbackController', 'FeedbackControllerException', 'PIDController', 'Timer', 'VectorMathException']
class AutoOptimizingPID(FeedbackController):
    @typing.overload
    def __init__(self, params: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], setpoint: typing.SupportsFloat | typing.SupportsIndex, lr: typing.SupportsFloat | typing.SupportsIndex = 0.001) -> None:
        ...
    @typing.overload
    def __init__(self, setpoint: typing.SupportsFloat | typing.SupportsIndex, lr: typing.SupportsFloat | typing.SupportsIndex = 0.001) -> None:
        ...
    def getAsPID(self) -> PIDController:
        """
        Get the auto-optimizing PID controller as a simple PID controller.
        """
    def getCaps(self) -> list[float]:
        """
        Get the upper and lower caps of the integral and derivative.
        """
    def getLearningRate(self) -> float:
        """
        Get the learning rate of the gradient descent algorithm.
        """
    def init(self) -> None:
        """
        Initialize the auto-optimizing PID controller
        """
    def requestLoop(self, input: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Request a single loop of the auto-optimizing PID controller.
        """
    def setCaps(self, time_integral: typing.SupportsFloat | typing.SupportsIndex, derivative: typing.SupportsFloat | typing.SupportsIndex) -> None:
        """
        Set the upper and lower caps of the integral and derivative.
        """
    def setLearningRate(self, lr: typing.SupportsFloat | typing.SupportsIndex) -> None:
        """
        Set the learning rate of the gradient descent algorithm.
        """
class FeedbackController:
    def __repr__(self) -> str:
        ...
    def getSetpoint(self) -> float:
        """
        Get the setpoint of the feedback controller.
        """
    def setSetpoint(self, setpoint: typing.SupportsFloat | typing.SupportsIndex) -> None:
        """
        Set the setpoint of the feedback controller.
        """
class FeedbackControllerException(Exception):
    pass
class PIDController(FeedbackController):
    def __init__(self, params: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], setpoint: typing.SupportsFloat | typing.SupportsIndex) -> None:
        ...
    def getCaps(self) -> list[float]:
        """
        Get the upper and lower caps of the integral and derivative.
        """
    def getGains(self) -> list[float]:
        """
        Get the parameter gains of the PID controller.
        """
    def init(self) -> None:
        """
        Initialize the PID controller
        """
    def requestLoop(self, input: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Request a single loop of the PID controller.
        """
    def setCaps(self, time_integral: typing.SupportsFloat | typing.SupportsIndex, derivative: typing.SupportsFloat | typing.SupportsIndex) -> None:
        """
        Set the upper and lower caps of the integral and derivative.
        """
    def setGains(self, gains: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex]) -> None:
        """
        Set the parameter gains of the PID controller.
        """
class Timer:
    def __init__(self) -> None:
        """
        Create an instance of the Timer class
        """
    def micros(self) -> int:
        """
        Get the microseconds since the timer was started
        """
    def millis(self) -> int:
        """
        Get the milliseconds since the timer was started
        """
    def start(self) -> None:
        """
        Set the start time of the timer.
        """
class VectorMathException(Exception):
    pass
