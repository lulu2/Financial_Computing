#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>

using namespace std;

class matrix{
	vector<vector<double>> value;
	int rows;
	int cols;
public:
	matrix(){}

	matrix(int r, int c): rows(r), cols(c)
	{
		value.resize(rows);
		for (int i = 0; i < rows; i++){
			value[i].resize(c);
		}
	}

	matrix(vector<vector<double>> v): value(v)
	{
		rows = value.size();
		cols = value[0].size();
	}

	matrix(vector<double> v, int r, int c): rows(r), cols(c)
	{
		try{
			if (v.size() != rows * cols){
				throw "Size not match.";
			}
			value.resize(rows);
			for (int i = 0; i < rows; i++){
				value[i].resize(c);
			}
			int j = 0;
			for (int i = 0; i < rows; i++){
				vector<double> temp (cols);
				for (int k = 0; k < cols; k++){
					temp[0] = v[j++];
				}
				value[i] = temp;
			}
		}
		catch(const char* m){
			cout << m << endl;;
		}
	}

	void set(int r, int c, double vv){
		try{
			if ((r > rows - 1)||(c > cols - 1)){
				throw "index out of matrix size.";
			}
			vector<double> temp = value[r];
			temp[c] = vv;
			value[r] = temp;
		}
		catch(const char* m){
			cout << m << endl;
		}
	}

	double get(int r, int c) const {
		try{
			if ((r > rows - 1)||(c > cols - 1)){
				throw "index out of matrix size.";
			}
			vector<double> temp = value[r];
			return temp[c];
		}
		catch(const char* m){
			cout << m << endl;
			return 0;
		}
	}

	int getRows() const {return rows;}

	int getCols() const {return cols;}

	void printMatrix() const {
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				//cout << this -> get(i,j) << ", ";
				printf("%.3f, ", this -> get(i,j));
			}
			cout << '\n';
		}
	}

	void minus(double k){
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				this -> set(i, j, this -> get(i,j) - k);
			}
		}
	}
};

std::vector<matrix> CholeskyDecomposition(matrix inputMatrix){
	std::vector<matrix> decomposition (2);
	int rowSize = inputMatrix.getRows();
	int colSize = inputMatrix.getCols();
	matrix L(rowSize, colSize);
	matrix L_t(rowSize, colSize);

	for (int i = 0; i < rowSize; i++){
		for (int j = 0; j < colSize; j++){
			L.set(i, j, 0);
			L_t.set(i, j, 0);
		}
	}

	for (int i = 0; i < rowSize; i++){

		for (int j = 0; j < i; j++){
			double temp2 = 0;
			for (int k = 0; k < j; k++){
				temp2 += L.get(i, k) * L.get(j, k);
			}
			L.set(i, j, (inputMatrix.get(i, j) - temp2) / L.get(j, j));
			L_t.set(j, i, (inputMatrix.get(i, j) - temp2) / L.get(j, j));
		}

		double temp = inputMatrix.get(i, i);
		for (int j = 0; j < i; j++){
			temp -= pow(L.get(i, j), 2);
		}
		L.set(i, i, sqrt(temp));
		L_t.set(i, i, sqrt(temp));
	}

	decomposition[0] = L;
	decomposition[1] = L_t;
	return decomposition;
}

matrix randomMatrix(int r, int c){
	matrix output(r, c);
	srand(time(NULL));
	for (int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			double temp = rand() / RAND_MAX;
			output.set(i, j, (double)(rand()%1000)/100);
		}
	}
	return output;
}

matrix rowAVG(matrix input){
	int rowSize = input.getRows();
	int colSize = input.getCols();
	matrix output(rowSize,1);
	for (int i = 0; i < rowSize; i++){
		double avg = 0;
		for (int j = 0; j < colSize; j++){
			avg += input.get(i,j);
		}
		avg /= colSize;
		output.set(i, 0, avg);
	}
	return output;
}

int main(){
	printf("input matrix is:\n");
	vector<double> v({83.210509 ,   2.458952  , 54.01988});
	vector<double> v2({ 2.458952 , 599.423640 ,-117.82514});
	vector<double> v3({ 54.019882, -117.825136 , 188.88430});
	vector<vector<double>> test;
	test.push_back(v);
	test.push_back(v2);
	test.push_back(v3);
	matrix k(test);
	k.printMatrix();
	cout << '\n';

	vector<matrix> LL = CholeskyDecomposition(k);
	matrix L = LL[0];
	matrix L_t = LL[1];
	printf("output matrix 1 is:\n");
	L.printMatrix();
	cout << '\n';
	printf("output matrix 2 is:\n");
	L_t.printMatrix();

	return 0;
}
