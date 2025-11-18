#pragma once
#include "Main Libraries.h"

class FileManager {
	private : 
		//Sacred Data : 
		//Raw data : 
		DataFrame data;

		//Number of rows and columns
		int num_rows = 0; 
		int num_cols = 0;
		string filepath;
		
	public :
		vector<string> ColumnName;
		
		//Functions : 
		FileManager(const string& filepath);	//Parametric constructor
		
		void read_csv();
		void PrintHeader(const int& ColWidth1, const int& ColWidth2);
		void PrintContent(const int& n, const int& ColWidth1, const int& ColWidth2);
		void PrintData(const int& num_data = -1);

		//Accessor : 
		DataFrame GetData() { return data; };
		int GetRows() { return num_rows; };
		int GetCols() { return num_cols; };
		string GetFilePath() { return filepath; };
};

