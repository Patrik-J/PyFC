from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup, find_packages

ext_modules = [
    Pybind11Extension("pyfc._core", 
                      ["src/pyfc/fc_exceptions.cpp",
                       "src/pyfc/feedbackcontroller.cpp", 
                       "src/pyfc/math/fc_math.cpp", 
                       "src/pyfc/pid/pidcontroller.cpp", 
                       "src/pyfc/pid/autooptpid.cpp", 
                       "src/pyfc/timer/timer.cpp", 
                       "src/pyfc/_core.cpp"], 
                      include_dirs=[
                                    "include",
                                    "include/pyfc", 
                                    "include/pyfc/math", 
                                    "include/pyfc/timer", 
                                    "include/pyfc/pid"],
                      cxx_std=17),
]

setup(
    name="pyfc",
    version="0.1.0",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    ext_modules=ext_modules, 
    cmdclass={"build_ext": build_ext})