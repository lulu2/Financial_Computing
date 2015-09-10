#include <iostream>
#include <cmath>

int main()
{	
	std::cout << "This is to compute x^n: \n";
	double x;
	unsigned int n;

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
		std::cout << "---Step2: Input integer n >= 0 and press enter" << std::endl;
		std::cin >> n;
		if (std::cin.fail()){
			std::cout << "Error: Input must be an integer or decimal no less than 0, input again" << std::endl;
			std::cin.clear();
		}
		else {
			proceed = true;
			std::cout << "Input integer n is " << n << std::endl;
		}
		std::cin.ignore(INT_MAX, '\n');
	}
	std::cout << "" << std::endl;

	double k = pow(x,n);
	std::cout << "---Result: x^n is " << k << std::endl;
	return 0;
}
