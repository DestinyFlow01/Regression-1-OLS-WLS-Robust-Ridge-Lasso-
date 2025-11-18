#pragma once

//C++ libraries : 
#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
#include<omp.h>
#include<chrono>
#include<fstream>
#include<unordered_map>
using namespace std;

//External libraries : 
#include "eigen-3.4.0/Eigen/Dense"
#include <boost/math/distributions/students_t.hpp>
using namespace Eigen;

//Struct : 
struct Stats {
	double CoefficientEstimate;
	double SE;
	double t_statistics; 
	double p_value;
	double CI_Left; 
	double CI_Right;
};

struct Quality {
	double R2; 
	double adjusted_R2;
	double RMSE;
};

//Type aliasing : 
using DataFrame = unordered_map<string, vector<double>>;
/*
	DataFrame is the type alias to keep raw data. For now, the type that it can keep is only double.
	The first part consists of the name of the quantity itself, while the second part consists of the data itself

	Here, unordered map is chosen in the design to prevent the need to use linear search through hashing,
	in the case users want to find the desired column
*/

using RegressionResult = unordered_map<string, Stats>;
/*
	RegressionResult is the type alias to keep regression result. For now, the quantities (for each coefficient) that will be kept are :
	1. Estimates value
	2. SSE
	3. t statistics
	4. p value

	The unordered map is chosen using the same reasons as before and to make it easier for reporting.
*/

