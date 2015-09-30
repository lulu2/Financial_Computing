#include <iostream>
#include <cmath>
#include <vector>

const double pi = 3.1415926535897;
const double b[6] = {0.2316419, 0.3193815300, -0.356563782, 1.7814779370, -1.821255978, 1.3302744290};

double normal(double x){
	double sumTerm = 0;
	double origin = x;
	x = std::abs(x);
	for (int i = 1; i < 6; i++){
		sumTerm += b[i] / pow(1 + b[0] * x,i);
	}
	if (origin > 0){
		return 1 - sumTerm * exp(-pow(x,2) / 2) / sqrt(2 * pi);
	}
	else {
		return sumTerm * exp(-pow(x,2) / 2) / sqrt(2 * pi);
	}
}

std::vector<double> d(double S, double K, double sigma, double tau, double r){
	std::vector<double> output;
	output.resize(2);
	double d_positive = (log(S / K) + (r + pow(sigma, 2) / 2) * tau) / (sigma * sqrt(tau));
	double d_negative = (log(S / K) + (r - pow(sigma, 2) / 2) * tau) / (sigma * sqrt(tau));
	output[0] = d_positive;
	output[1] = d_negative;
	return output;
}

double BlackScholesCall (double S, double K, double sigma, double tau, double r){
	double d_positive = d(S, K, sigma, tau, r)[0];
	double d_negative = d(S, K, sigma, tau, r)[1];
	return S * normal(d_positive) - K * exp(-r * tau) * normal(d_negative);
}

double BlackScholesPut (double S, double K, double sigma, double tau, double r){
	double d_positive = d(S, K, sigma, tau, r)[0];
	double d_negative = d(S, K, sigma, tau, r)[1];
	return K * exp(-r * tau) *normal(-d_negative) - S * normal(-d_positive);
}

int main(){
	double S = 90, K = 87, sigma = 0.2, tau = 0.8, r = 0.15;
	std::cout << "setting is S = 90, K = 87, sigma = 0.2, tau = 0.8, r = 0.15" << std::endl;
	std::cout << "Call is " << BlackScholesCall(S, K, sigma, tau, r) << std::endl;
	std::cout << "Put is " << BlackScholesPut(S, K, sigma, tau, r) << std::endl;
	return 0;
	//Call - Put = S - D * K;
	//D = exp(- r * tau);
}
