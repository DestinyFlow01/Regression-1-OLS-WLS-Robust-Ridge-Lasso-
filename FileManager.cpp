#include "FileManager.h"

FileManager::FileManager(const string& filepath) : filepath(filepath) {
	read_csv();
}

//Note : This function assumes that the file has header, and MUST HAVE HEADER
void FileManager::read_csv() {
	//Openning file : 
	ifstream myfile(filepath);
	
	//Ensuring that the file is openned properly : 
	if (!myfile.is_open()) throw runtime_error("File is not openned properly!");

	//At this point, we can process it then 
	//Defining helper variables : 
	string line, colName;
	double value;

	//Processing : 
	//1. Header : 
	if (getline(myfile, line)) {
		stringstream ss(line); 

		while (getline(ss, colName, ',')) {
			ColumnName.push_back(colName);
			data[colName] = {};
			num_cols++;
		}
	}

	//2. Non-header :
	while (getline(myfile, line)) {
		stringstream ss(line);

		int ColIdx = 0;
		while (ss >> value) {
			data[ColumnName[ColIdx]].push_back(value);
			if (ss.peek() == ',') ss.ignore();
			ColIdx++;
		}
		num_rows++;
	}

	//Closing file :
	myfile.close();
}

void FileManager::PrintHeader(const int& colWidth1, const int& colWidth2) {
	cout << setw(colWidth1) << left << "Row" << " | ";

	for (int i = 0; i < num_cols; i++) cout << setw(colWidth2) << left << i << "|";

	cout << "\n" << string(8 + colWidth2 * (num_cols + 2), '-') << "\n";
}

void FileManager::PrintContent(const int& n, const int& colWidth1, const int& colWidth2) {
	for (int i = 0; i < n; i++) {
		cout << setw(colWidth1) << left << i << " | ";
		for (const string col : ColumnName)
			cout << setw(colWidth2) << left << setprecision(2) << data[col][i] << "|";
		cout << "\n";
	}
}

void FileManager::PrintData(const int& num_data) {
	const int colWidth1 = 3;
	const int colWidth2 = 10;

	cout << "Printing Data : \n\n";
	PrintHeader(colWidth1, colWidth2);
	PrintContent((num_data <= 0) ? min(num_rows, 5) : num_data, colWidth1, colWidth2);

	cout << "\n\nwith : ";
	for (int i = 0; i < num_cols; i++) cout << "\ni = " << i << " -> " << ColumnName[i];
	cout << endl;
}