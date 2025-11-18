// Regression1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Main Libraries.h"
#include "FileManager.h"
#include "LinearRegression.h"

void RunningCase(const string& filepath, vector<string>& column_fitted, string& output_fitted, const string& method_name);

int main()
{   
    omp_set_num_threads(4);
    {
        // Data 1 : 
        const string filepath = "Dataset/data1.csv", method_name = "OLS";

        //Columns to be used for model : 
        vector<string> column_fitted = { "Dow_Q_EX_R", "Pepsi_Q_EX_R", "REV_Q_R" };
        string output_fitted = "Coke_Q_EX_R";

        cout << "For file : " << filepath << "\n\n";
        RunningCase(filepath, column_fitted, output_fitted, method_name);
    }
    
    {
        // Data 2 : 
        const string filepath = "Dataset/data2.csv", method_name = "OLS";

        //Columns to be used for model : 
        vector<string> column_fitted = { "METALS", "US_STK", "X10Y_TBY", "X13W_TB", "EURUSD"};
        string output_fitted = "DXY";

        cout << "For file : " << filepath << "\n\n";
        RunningCase(filepath, column_fitted, output_fitted, method_name);
    }

    char ch; cin >> ch;
}

void RunningCase(const string& filepath, vector<string>& column_fitted, string& output_fitted, const string& method_name) {
    auto time_begin = chrono::high_resolution_clock::now();
    FileManager fm(filepath);
    //fm.PrintData();

    //Requesting data from data : 
    vector<vector<double>> X;
    X.reserve(column_fitted.size());
    for (auto const& col : column_fitted) X.push_back(fm.GetData()[col]);
    vector<double> y = fm.GetData()[output_fitted];

    //Making model : 
    LinearRegression model(X, y, column_fitted, output_fitted);
    model.Fit(method_name);
    model.PrintFitResult();

    auto time_end = chrono::high_resolution_clock::now();
    double time_elapsed_ms = chrono::duration_cast<chrono::milliseconds> (time_end - time_begin).count();
    cout << "\n\nTime needed for calculation = " << fixed << setprecision(3) << time_elapsed_ms << " ms\n\n";
}
