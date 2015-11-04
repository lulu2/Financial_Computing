#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iomanip>
#include "matrix.hpp"
#include "RefCount.hpp"

using namespace std;

int main(){
	printf("For choleskyDecomposition, input matrix is:\n");
	vector<double> v({83.210509 ,   2.458952  , 54.01988});
	vector<double> v2({ 2.458952 , 599.423640 ,-117.82514});
	vector<double> v3({ 54.019882, -117.825136 , 188.88430});
	vector<vector<double>> test;
	test.push_back(v);
	test.push_back(v2);
	test.push_back(v3);
	matrix k(test);
	cout << k << endl;

	vector<matrix> LL = k.choleskyDecomposition();
	matrix L = LL[0];
	matrix L_t = LL[1];
	printf("output matrix 1 is:\n");
	cout << L << endl;
	printf("output matrix 2 is:\n");
	cout << L_t << endl;

	cout << "Matrix A is:" <<endl;
	vector<double> v11({1,  2, 3});
	vector<double> v12({4 , 5 ,6});
	vector<double> v13({7, 8 , 9});
	vector<vector<double>> test1;
	test1.push_back(v11);
	test1.push_back(v12);
	test1.push_back(v13);
	matrix k1(test1);
	cout << k1 <<endl;

	cout << "Matrix B is:" <<endl;
	vector<double> v21({11 ,   14  , 17});
	vector<double> v22({ 12 , 15 ,18});
	vector<double> v23({ 13, 16 , 23});
	vector<vector<double>> test2;
	test2.push_back(v21);
	test2.push_back(v22);
	test2.push_back(v23);
	matrix k2(test2);
	cout << k2 << endl;

	cout << "A +B is:" <<endl;
	matrix sumM = k1 + k2;
	cout << sumM << endl;

	cout << "A - B is:" <<endl;
	matrix dedM = k1 - k2;
	cout << dedM << endl;

	cout << "A * B is:" <<endl;
	matrix prodM = k1 * k2;
	cout << prodM << endl;

	cout << "A * 1.5 is:" <<endl;
	matrix prodSM = k1 *1.5;
	cout << prodSM << endl;

	cout << "A.transpose() is:" <<endl;
	matrix tA = k1.transpose();
	cout << tA << endl;

	cout << "B.inverse() is:"<<endl;
	matrix iB = k2.inverse();
	cout << iB << endl;

	cout << "A.inverse() is:"<<endl;
	matrix iA = k1.inverse();
	cout << iA << endl;

	return 0;
}
