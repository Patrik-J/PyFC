from pathlib import Path
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

this_directory = Path(__file__).parent
long_description = (this_directory / "README.md").read_text(encoding="utf-8")

setup(
    name="py-feedback-controller",
    version="0.1.2",
    author="Patrik Jelic",
    description="A Python package implementing feedback controllers in C++.",
    long_description=long_description, 
    long_description_content_type="text/markdown",
    url="https://github.com/Patrik-J/PyFC",
    licence="MIT",
    classifiers= [
        "Programming Language :: Python :: 3",
        "Operating System :: OS Independent",
    ],
    python_requires=">=3.13",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    ext_modules=ext_modules, 
    cmdclass={"build_ext": build_ext})