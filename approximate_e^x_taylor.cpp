#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>

std::vector<double> approximation(double x, double bound);
int main()
{	
	std::cout << "This is to compute approximation to exp(x): \n";
	double x;
	double bound;

	bool proceed = false;
	while (!proceed){
		std::cout << "---Step1: Input real number x and press enter" << std::endl;
		std::cin >> x;
		if (std::cin.fail()){
			std::cout << "Error: Input must be a real number, input again" << std::endl;
			std::cin.clear();
		}
		else {
			proceed = true;
			std::cout << "Input real number x is " << x << std::endl;
		}
		std::cin.ignore(INT_MAX, '\n');
	}
	std::cout << "" << std::endl;

	proceed = false;
	while (!proceed){
		std::cout << "---Step2: Choose error bound and press enter, default value 0.0001 when input 0 " << std::endl;
		std::cin >> bound;
		if (std::cin.fail() || bound < 0){
			std::cout << "Error: error bound must be real value larger than 0" << std::endl;
			std::cin.clear();
		}
		else 
		{
			if (bound == 0){
				bound = 0.0001;
			}
			proceed = true;
			std::cout << "error bound is set to  " << bound << std::endl;
		}
		std::cin.ignore(INT_MAX, '\n');
	}
	std::cout << "" << std::endl;

	std::vector<double> kk = approximation(x, bound);
	printf("Approximation of exp(%f) is %f with error bound %f \n", x, kk[0], bound);
	std::cout << "Use Taylor approximation: " << std::endl;
	std::cout << "exp(x) ~ ";
	int order = kk[1];
	double a = kk[2];
	double f_a = exp(a);
	if (kk[1] == 0){
		std::cout << f_a << std::endl;
	}
	else{
		if (a == 0){
			if (kk[1] == 1){
				printf ("%f + %f * x", f_a, f_a);
			}
			else{
				printf ("%f + %f * x", f_a, f_a);
				for (int i = 2; i < kk[1] + 1; i++){
					printf (" + %f * x^%i/%i!", f_a, i, i);
				}
			}
		}
		else if (a > 0) {
			if (kk[1] == 1){
				printf ("%f + %f * (x-%f)", f_a, f_a, a);
			}
			else{
				printf ("%f + %f * (x-%f)", f_a, f_a, a);
				for (int i = 2; i < kk[1] + 1; i++){
					printf (" + %f * (x-%f)^%i/%i!", f_a, a, i, i);
				}
			}
		}
		else if (a < 0) {
			double a_n = -a;
			if (kk[1] == 1){
				printf ("%f + %f * (x+%f)", f_a, f_a, a_n);
			}
			else{
				printf ("%f + %f * (x+%f)", f_a, f_a, a_n);
				for (int i = 2; i < kk[1] + 1; i++){
					printf (" + %f * (x+%f)^%i/%i!", f_a, a_n, i, i);
				}
			}
		}		
	}
	std::cout << " " << std::endl;
	return 0;
}

std::vector<double> approximation(double x, double bound){
	std::vector<double> k;
	if (x == 0){
	k.push_back(1);
	k.push_back(0);
	k.push_back(0);
	return k;
	}

	int n = 0;
	int prod = 1;
	double nTerm = 1;
	double target = exp(x);
	int intPart = (int) x;
	double a = 0;
	if ((x - intPart == 0) && (intPart > 0 )){
		a = intPart - 0.1;
	}
	else if ((x - intPart == 0) && (intPart < 0 )){
		a = intPart - 0.5;
	}
	else {
		a = intPart;
	}
	double approx = exp(a);
	std::cout<< "Approximation Path: " << std::endl;
	while (std::abs(approx - target) > bound){
		n++;
		prod *= n;
		nTerm *= x - a;
		approx += exp(a) * nTerm / prod;
		if (n < 40){
		std::cout << approx << std::endl;
		}
	}
	k.push_back(approx);
	k.push_back(n);
	k.push_back(a);
	return k;
}

