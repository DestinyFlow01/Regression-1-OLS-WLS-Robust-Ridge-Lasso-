# Regression-1-OLS-WLS-Robust-Ridge-Lasso-

## Overview
This repository contains the initial version of a regression toolkit implemented in C++.
Currently, the project supports:
- Importing CSV files (with double data type only)
- Ordinary Least Squares (OLS) estimation
  <br>⚠️ Prediction capabilities and additional regression methods (WLS, Robust, Ridge, Lasso) are planned for future extensions.

## Dependencies
This project relies on two external libraries:
1.  Eigen
- Used for numerical linear algebra (matrix and vector operations).
- Installation guide: [Eigen Getting Started](https://libeigen.gitlab.io/eigen/docs-nightly/GettingStarted.html)
- A zipped copy is included in the repository for convenience.

2. Boost
- Used for computational statistics (e.g., p‑value calculation with Student’s t distribution).
- Due to GitHub size limitations, Boost is not uploaded here.
- Installation guide : [Boost Official Site](https://www.boost.org/) 


## Compilation
- You will need g++ installed on your system.
- Compile from the terminal using a command such as:
### Compile the project
g++ -std=c++17 \\ <br>
    -I /path/to/eigen \\ <br>
    -I /path/to/boost \\ <br>
    FileManager.cpp Regression1.cpp LinearRegression.cpp \\ <br>
    -o Regression1.exe <br><br>
Replace /path/to/eigen and /path/to/boost with the actual installation paths on your system.

<br>
Of course, you can make a makefile for it. However, it will not be given here for efficiency purpose.

## Notes
- Some optimization routines may not work due to GitHub file upload limitations.
- Future updates will extend functionality to handle more file formats, prediction, and additional regression methods, or even making it in CMake to collect them as Machine Learning libraries.
- Development time is long and demanding, and I'm still learning OOP concepts such as polymorphism and templates. Updates will come as I continue to grow this project

## Closing 
Stay tuned for the updates. Thank you very much 
<br> <br>
Bryan Goh (18th November 2025)
