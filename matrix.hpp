#ifndef MAT_H 
#define MAT_H

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iomanip>

using namespace std;

class matrix{
	vector<vector<double>> value;
	int rows;
	int cols;
	void subtractRow(int p, int q, double k){
		if ((p < rows) && (q < rows)){
			for(int i = 0; i < cols; i++){
				this->set(p, i, this->get(p,i) - k * this->get(q,i));
			}
		}
	}
						//Subtracts row j from row i
	void swapRows(int p, int q){
		if ((p < rows) && (q < rows)){
			for(int i = 0; i < cols; i++){
				double temp = this->get(q,i);
				this->set(q, i, this->get(p,i));
				this->set(p, i, temp);
			}
		}	
	}
						//Swaps rows i and j
	void multiplyRow(int p, double d){
		if (p < rows){
			for(int i = 0; i < cols; i++){
				this->set(p, i, this->get(p,i) * d);
			}
		}			
	}

public:
	matrix(){}

	matrix(int r, int c): rows(r), cols(c)
	{	
		if ((r > 0) && (c > 0)){
			value.resize(rows);
			for (int i = 0; i < rows; i++){
				value[i].resize(c);
			}
		}
		else{
			value.resize(0);
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

	matrix(const matrix& m){
		value = m.value;
		cols = m.cols;
		rows = m.rows;
	}

	~matrix(){}

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

	friend ostream& operator<<(ostream& os,const matrix& m){
		for (int i = 0; i < m.getRows(); i++){
			for (int j = 0; j < m.getCols(); j++){
				os << std::setfill(' ') << std::setw(12) << m.get(i,j);
			}
			os << '\n';
		}
    	return os;
	}

	void minus(double k){
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				this -> set(i, j, this -> get(i,j) - k);
			}
		}
	}

	vector<matrix> choleskyDecomposition();
	matrix transpose();
	matrix inverse();

	void operator=(const matrix& m);				//assignment operator
	matrix operator + (const matrix& m);			//addition operator
	matrix operator - (const matrix& m);
	matrix operator *(const matrix& m);				//matrix multiplication
	matrix operator *(double d);					//multiplication by const
	matrix operator -(double k){
		matrix temp(value);
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				temp.set(i, j, temp.get(i,j) - k);
			}
		}
		return temp;
	}
};

const matrix EMPTY_matrix(0, 0);

vector<matrix> matrix::choleskyDecomposition(){
	std::vector<matrix> decomposition (2);
	int rowSize = rows;
	int colSize = cols;
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
			L.set(i, j, (this->get(i, j) - temp2) / L.get(j, j));
			L_t.set(j, i, (this->get(i, j) - temp2) / L.get(j, j));
		}

		double temp = this->get(i, i);
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

matrix matrix::transpose(){
	matrix output(cols, rows);
	if (value.size() > 0){
		for(int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				output.set(j, i, this->get(i,j));
			}
		}
		return output;
	}
	else{
		return EMPTY_matrix;
	}
}

void matrix::operator=(const matrix& m){
	try{
		if (m.value.size() > 0){
			value = m.value;
			rows = m.getRows();
			cols = m.getCols();
		}
		else{
			throw "matrix initialization error.";
		}
	}
	catch(const char* msg){
		cout << msg << endl;
	}	
}

matrix matrix::operator + (const matrix& m){
	matrix output(rows, cols);
	if ((this->rows == m.rows) && (this->cols == m.cols)){
		for(int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				output.set(i, j, this->get(i,j) + m.get(i,j));
			}
		}
		return output;
	}
	else{
		return EMPTY_matrix;
	}
}

matrix matrix::operator - (const matrix& m){
	matrix output(rows, cols);
	if ((this->rows == m.rows) && (this->cols == m.cols)){
		for(int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				output.set(i, j, this->get(i,j) - m.get(i,j));
			}
		}
		return output;
	}
	else{
		return EMPTY_matrix;
	}
}

matrix matrix::operator *(const matrix& m){
	matrix output(rows, cols);
	if ((this->rows == m.cols) && (this->cols == m.rows)){
		for(int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				double k = 0;
				for (int p = 0; p < cols; p++){
					k += this->get(i, p) * m.get(p, j);
				}
				output.set(i, j, k);
			}
		}
		return output;
	}
	else{
		return EMPTY_matrix;
	}	
}

matrix matrix::operator *(double d){
	matrix output(rows, cols);
	if (value.size() > 0){
		for(int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				output.set(i, j, this->get(i,j) * d);
			}
		}
		return output;
	}
	else{
		return EMPTY_matrix;
	}	
}

matrix matrix::inverse(){
	matrix output(cols, rows);
	matrix cp = *this;
	if ((cols != rows) || (cols == 0)){
		return EMPTY_matrix;
	}
	else {
		try{
		matrix I(rows, rows);
		for(int i = 0; i < rows; i++){
			I.set(i, i, 1);
		}
		for(int i = 0; i < rows; i++){
			while (cp.get(i,i) == 0){
				cp.swapRows(i,i +1);
				I.swapRows(i,i +1);
				if (i == rows - 1){
					throw "The matrix is not invertible.";
				}
			}
			double temp = 1 / cp.get(i,i);
			cp.multiplyRow(i, temp);
			I.multiplyRow(i, temp);
			for (int j = i + 1; j < rows; j++){
				double scale = cp.get(j, i);
				cp.subtractRow(j, i, scale);
				I.subtractRow(j, i, scale);
			}
		}
		for(int i = rows - 1; i >= 0; i--){
			for (int j = i - 1; j >= 0; j--){
				double scale = cp.get(j, i);
				cp.subtractRow(j, i, scale);
				I.subtractRow(j, i, scale);
			}
		}
		return I;
		}
		catch(const char * m){
			cout << m << endl;
			return EMPTY_matrix;
		}
	}
}

matrix randommatrix(int r, int c){
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

#endif
