#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>

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

double vega(double S, double K, double sigma, double 	T, double r){
	return S * normal(d(S, K, sigma, T, r)[0]) * sqrt(T);
}

double BlackScholesPut(double S, double K, double sigma, double tau, double r){
	double d_positive = d(S, K, sigma, tau, r)[0];
	double d_negative = d(S, K, sigma, tau, r)[1];
	return K * exp(-r * tau) *normal(-d_negative) - S * normal(-d_positive);
}

double volatility_Newton(double S, double K, double P, double tau, double r){
	double sigma = 0.5;
	double sigma0 = 0;
	while (std::abs(sigma0 - sigma) > 0.0000001) {
		sigma0 = sigma;
		sigma = sigma - (BlackScholesPut(S, K, sigma, tau, r) - P) / vega(S, K, sigma, tau, r);
	}
	return sigma;
}

double volatility_secant(double S, double K, double P, double tau, double r){
	double sigma0 = 0, sigma1 = 0.3;
	while(std::abs(sigma1 - sigma0) > 0.000001){
		double secant = (BlackScholesPut(S, K, sigma1, tau, r) - BlackScholesPut(S, K, sigma0, tau, r)) / (sigma1 - sigma0);
		sigma0 = sigma1;
		sigma1 = sigma1 - (BlackScholesPut(S, K, sigma1, tau, r) - P) / secant; 
	}
	return sigma1;
}

double volatility(double S, double K, double P, double tau, double r, double bound){
	double sigma0 = 0;
	double sigma1 = 14;
	double sigma = (sigma0 + sigma1) / 2;
	double term = BlackScholesPut(S, K, sigma, tau, r) - P;
	while (std::abs(term) > bound){
		double term0 = BlackScholesPut(S, K, sigma0, tau, r) - P;
		double term1 = BlackScholesPut(S, K, sigma1, tau, r) - P;
		if (term0 * term > 0) {
			if (term1 * term > 0){
				sigma1 *= 1.5;
			}
			else if (term1 * term < 0) {
				sigma0 = sigma;
			}
			else {
				sigma = sigma1;
				break;
			}
		}
		else if (term0 * term < 0) {
			if (term1 * term < 0){
				sigma1 *= 1.5;
			}
			else if (term1 * term > 0){
				sigma1 = sigma;
			}
			else {
				sigma = sigma1;
				break;
			}
		}
		else {
			sigma = sigma0;
			break;
		}
		sigma = (sigma0 + sigma1) / 2;
		term = BlackScholesPut(S, K, sigma, tau, r) - P;
	}
	return sigma;
}

int main(){
	double S = 28, tau = 1, r = 0;
	double bound;
	double K = 17.5;
	double P = 0.28;
	double sigma_n = volatility_Newton(S, K, P, tau, r);
	double sigma_s = volatility_secant(S, K, P, tau, r);
	std::cout << sigma_n << std::endl;
	std::cout << sigma_s << std::endl;
	return 0;
}
