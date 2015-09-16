#include <iostream>
#include <cmath>
#include <iomanip>
#include <climits>

int main()
{	
	std::cout << "Print amortization table:" << std::endl;

	double r;
	bool proceed = false;
	while (!proceed){
		std::cout << "Input interest rate r and press enter:" << std::endl;
		std::cin >> r;
		if (std::cin.fail() || r <= 0){
			std::cout << "Error: Input must be a positive value" << std::endl;
			std::cin.clear();
		}
		else {
			proceed = true;
			std::cout << "r is " << r << "."<< std::endl;
		}
		std::cin.ignore(INT_MAX, '\n');
	}

	unsigned int N;
	bool proceedN = false;
	while (!proceedN){
		std::cout << "Input period N and press enter:" << std::endl;
		std::cin >> N;
		if (std::cin.fail() || N == 0){
			std::cout << "Error: Input must be a positive integer" << std::endl;
			std::cin.clear();
		}
		else {
			proceedN = true;
			std::cout << "N is " << N << "."<< std::endl;
		}
		std::cin.ignore(INT_MAX, '\n');
	}

	double P;
	bool proceedP = false;
	while (!proceedP){
		std::cout << "Input amount P0 and press enter:" << std::endl;
		std::cin >> P;
		if (std::cin.fail() || P == 0){
			std::cout << "Error: Input must be a positive value" << std::endl;
			std::cin.clear();
		}
		else {
			proceedP = true;
			std::cout << "P0 is " << P << "."<< std::endl;
		}
		std::cin.ignore(INT_MAX, '\n');
	}

	double B = P;
	double C = P * pow(1 + r, N) * r / (pow(1 + r, N) - 1);

	std::cout << "Amortization Table:" << std::endl;
	std::cout << std::setfill('-') << std::setw(71) << "" << std::endl;
	std::cout << std::setfill(' ') << std::setw(1) << "| " 
	<< std::setw(4) << "" << std::setw(6) << "Period" << std::setw(4) << "" << std::setw(1) << "| " 
	<< std::setw(4) << "" << std::setw(8) << "interest" << std::setw(4) << "" << std::setw(1) << "| " 
	<< std::setw(4) << "" << std::setw(9) << "Principal" << std::setw(4) << "" << std::setw(1) << "| " 
	<< std::setw(4) << "" << std::setw(7) << "Balance" << std::setw(4) << "" << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('=') << std::setw(71) << "" << std::endl;
	for (int i = 1; i < N + 1; i++){
		double I = r * B;
		P = C - I;
		B = B - P;
	std::cout << std::setfill(' ') << std::setw(1) << "| " 
	<< std::setw(14) <<std::left << i << std::setw(1) << "| " 
	<< std::setw(16) <<std::left << I << std::setw(1) << "| " 
	<< std::setw(17) <<std::left << P << std::setw(1) << "| " 
	<< std::setw(15) <<std::left << B << std::setw(1) << "|" << std::endl;
	std::cout << std::setfill('-') << std::setw(71) << "" << std::endl;
	}

	return 0;
}
