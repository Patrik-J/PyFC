import subprocess

subprocess.run(["pip", "install", "-e", ".", "--no-build-isolation", "--no-cache-dir"]) 
subprocess.run(["pybind11-stubgen", "pyfc._core", "--output-dir", "src"]) 