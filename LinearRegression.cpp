#include "LinearRegression.h"

LinearRegression::LinearRegression(vector<vector<double>>& X, vector<double>& y, vector<string>& PredictorName, string& PredictedName) 
: predictors_name(PredictorName), predicted_name(PredictedName) 
{
	FillX(X); FillY(y);
	predictors_name.insert(predictors_name.begin(), "Intercept");
}

void LinearRegression::FillX(vector<vector<double>>& X) {
	int num_colsX = X.size();
	int num_rowsX = X[0].size();
	MatrixXd& target = (!predict) ? X_actual : X_pred;
	target.resize(num_rowsX, num_colsX + 1);	//Plus 1 due to intercept 

	//Filling the intercept : 
	#pragma omp parallel for
	for (int i = 0; i < num_rowsX; i++) target(i, 0) = 1;

	//Filling the other parts :
	#pragma omp parallel for
	for (int i = 0; i < num_rowsX; i++) {
		for (int j = 0; j < num_colsX; j++) target(i, j + 1) = X[j][i];
	}
}

void LinearRegression::FillY(vector<double>& y_input) {
	VectorXd& target = (!predict) ? y_actual : y_reference;
	target = Map<VectorXd>(y_input.data(), y_input.size());		
}

void LinearRegression::Fit(const string& method_name) {
	MethodName = method_name;
	ChangeSetting(false);

	if (MethodName == "OLS") OrdinaryRegression();
	

}

void LinearRegression::OrdinaryRegression() {
	VectorXd beta_coefficient = X_actual.colPivHouseholderQr().solve(y_actual);
	
	//Inserting to Results : 
	for (int i = 0; i < predictors_name.size(); i++) Result[predictors_name[i]].CoefficientEstimate = beta_coefficient(i);
	
	//Obtain fitted value : 
	y_fitted = X_actual * beta_coefficient;

	CalculateResidual();
	
	//Other required parameters : 
	int df = X_actual.rows() - X_actual.cols();
	double sigma2 = Residual_fitted.squaredNorm() / static_cast<double>(df);
	
	MatrixXd XtX_inv = (X_actual.transpose() * X_actual).ldlt().solve(MatrixXd::Identity(X_actual.cols(), X_actual.cols()));
	
	#pragma omp parallel for
	for (int j = 0; j < X_actual.cols(); j++) {
		double SE = sqrt(sigma2 * XtX_inv(j, j));
		double t_stat = beta_coefficient(j) / SE;
		Result[predictors_name[j]].SE = SE;
		Result[predictors_name[j]].t_statistics = t_stat;
	
		//Two sided p-value via Student's t distribution
		boost::math::students_t tdist(df);
		Result[predictors_name[j]].p_value = 2 * boost::math::cdf(boost::math::complement(tdist, fabs(t_stat)));

		double t_crit = boost::math::quantile(tdist, 0.975);	//95% CI
		Result[predictors_name[j]].CI_Left = Result[predictors_name[j]].CoefficientEstimate - t_crit * SE;
		Result[predictors_name[j]].CI_Right = Result[predictors_name[j]].CoefficientEstimate + t_crit * SE;
	}

	CalculateQuality();
}

inline void LinearRegression::CalculateResidual() {
	VectorXd& target_Residual = (!predict) ? Residual_fitted : Residual_pred;
	target_Residual = (!predict) ? y_fitted - y_actual : y_pred - y_reference ;
}

void LinearRegression::CalculateQuality() {
	//Calculate SSE
	double SSE = (!predict) ? Residual_fitted.squaredNorm() : Residual_pred.squaredNorm();
	
	//Calculate SST or TSS : 
	VectorXd& target_y = (!predict) ? y_actual : y_reference;
	double mean_y = target_y.mean();
	VectorXd Centered_y = target_y.array() - mean_y;
	double SST = Centered_y.squaredNorm();

	//Calculate Quality : 
	ModelQuality.R2 = 1 - SSE / SST;
	double n = target_y.size();
	double p = ( (!predict) ? X_actual : X_pred ).cols();
	ModelQuality.adjusted_R2 = 1 - (SSE / (n - p) ) / (SST / (n - 1));
	ModelQuality.RMSE = sqrt(SSE / n);
}

void LinearRegression::PrintFitResult() {
	const int colWidth = 15;
	//Fit result :
	cout << "Estimate results : \n";
	cout << setw(colWidth) << left << "Quantity"
		<< setw(colWidth) << "Estimates"
		<< setw(colWidth) << "SE"
		<< setw(colWidth) << "t-stat"
		<< setw(colWidth) << "p-val" 
		<< setw(colWidth) << "0.025" 
		<< setw(colWidth) << "0.975" << endl;
	cout << string(colWidth * 7, '-') << fixed << setprecision(5)<< endl;

	for (const auto& name : predictors_name) {
		cout << setw(colWidth) << left << name
			<< setw(colWidth) << Result[name].CoefficientEstimate
			<< setw(colWidth) << Result[name].SE
			<< setw(colWidth) << Result[name].t_statistics
			<< setw(colWidth) << Result[name].p_value
			<< setw(colWidth) << Result[name].CI_Left 
			<< setw(colWidth) << Result[name].CI_Right << endl;
	}

	

	// Model quality
	cout << "\nModel Quality:\n";
	cout << "R2          : " << ModelQuality.R2 << endl;
	cout << "Adjusted R2 : " << ModelQuality.adjusted_R2 << endl;
	cout << "RMSE        : " << ModelQuality.RMSE << endl;
}

void LinearRegression::Predict(vector<vector<double>>& X_input) {
}
