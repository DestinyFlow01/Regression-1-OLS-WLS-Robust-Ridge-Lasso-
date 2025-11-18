#pragma once
#include "Main Libraries.h"

class LinearRegression {
	private : 
		//Containing the most sacred variables : 
		//Part 0 : General Information
		vector<string> predictors_name;
		string predicted_name;

		//Part 1 : Related to fitted value 
		MatrixXd X_actual; 
		VectorXd y_actual;
		VectorXd Weight;	//For WLS
		VectorXd y_fitted;
		RegressionResult Result;
		Quality ModelQuality;
		VectorXd Residual_fitted;

		//Part 2 : Related to predicted value from new data : 
		MatrixXd X_pred;
		VectorXd y_pred;
		VectorXd y_reference;	//For test data 
		Quality PredQuality;
		VectorXd Residual_pred;

	public : 
		bool predict = false;	//Current condition is predict or fitted
		string MethodName;		//Regression method

		//Functions : 
		LinearRegression(vector< vector<double> >& X, vector<double>& y, vector<string>& PredictorName, string& PredictedName);
		void FillX(vector< vector<double> >& X);	//Filling matrix X
		void FillY(vector<double>& y);				//Filling vector Y

		void Fit(const string& method_name);
		void OrdinaryRegression();	//Standard
		void WeightedRegression();	//Heteroskedastic effect
		void RobustRegression();	//Outlier effect
		
		//Penalized regression
		void RidgeRegression();		
		void LassoRegression();
		
		//Other functions : 
		inline void CalculateResidual();
		void CalculateQuality();
		void ChangeSetting(const bool& predict_input) { predict = predict_input; };
		void PrintFitResult();
		void Predict(vector<vector<double>>& X_input);

		//Accessor : 
		//Part 1 : Related to Fitted Value 
		VectorXd GetFittedValue() { return y_fitted; };
		RegressionResult GetEstimates() { return Result; };
		Quality GetModelQuality() { return ModelQuality; };
		VectorXd GetResidualFitted() { return Residual_fitted; };

		//Part 2 : Related to predicted value : 
		VectorXd GetPredictedValue() { return y_pred; };
		Quality GetPredictedQuality() { return PredQuality; };
		VectorXd GetPredictedResidual() { return Residual_pred; };

};

