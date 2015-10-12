#include <iostream>
#include <cmath>
#include <vector>
#include <cmath>
#include <random>
#include <cstdlib>
#include <chrono>

static const double pi = 3.1415926535897;
typedef std::pair<double, double> normal2D;
typedef std::vector<double> parameters;
typedef double (*F) (double, parameters);
typedef double (*iF) (double, parameters);
typedef double (*pdf) (double, parameters);
typedef normal2D (*normalG) ();
static const parameters emptyParas = std::vector<double> ();
static std::vector<double> randPool;
static size_t poolPointer;
static size_t numLoop;

enum normalGenerator{
	boxMuller, margaglia, ar 
};

struct prob{
	F cdfFunction;
	iF icdfFunction;
	pdf pdfFunction;
};

void buildPool(size_t n){
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	srand(seed);
	randPool.resize(n * 100);
	size_t counter = 0;
	while (counter < n * 100){
		double temp = (double) rand() / RAND_MAX;
		if ((temp > 0) && (temp < 1)) {
			randPool[counter++] = temp;			
		}
	}
	poolPointer = 0;
}

double inverseTransform(iF reverseF, parameters s){
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	srand(seed);
	double U = (double) rand() / RAND_MAX;
	return reverseF(U, s);
}

double AcceptanceRejection(prob f, prob g, double c, parameters fs = emptyParas, parameters gs = emptyParas){
	double U = randPool[poolPointer++];
	double variable = inverseTransform(g.icdfFunction, gs);
	while (f.pdfFunction(variable, fs) / (c * g.pdfFunction(variable, gs)) < U){
		U = randPool[poolPointer++];
		variable = inverseTransform(g.icdfFunction, gs);
	}
	return variable;
}

normal2D BoxMuller(){
	double U1 = randPool[poolPointer++];
	double U2 = randPool[poolPointer++];
	double Z1 = sqrt(-2 * log(U1)) * cos(2 * pi * U2);
	double Z2 = sqrt(-2 * log(U1)) * sin(2 * pi * U2);
	return normal2D(Z1, Z2);
}

normal2D Margaglia(){
    double U1 = randPool[poolPointer++] * 2 - 1.0;
	double U2 = randPool[poolPointer++] * 2 - 1.0;
	double S = pow(U1, 2) + pow(U2, 2);
	while ((S >= 1) || (S == 0)){
		U1 = randPool[poolPointer++] * 2 - 1.0;
		U2 = randPool[poolPointer++] * 2 - 1.0;
		S = pow(U1, 2) + pow(U2, 2);
	}
	double Z1 = U1 * sqrt(-2 * log(S) / S);
	double Z2 = U2 * sqrt(-2 * log(S) / S);
	return normal2D(Z1, Z2);
}

double iExponential(double cdf, parameters rate){
	return log(1 - cdf) / (-rate[0]);
}

double normalPDF(double x, parameters s = emptyParas){
	return (exp(-pow(x,2) / 2) / (sqrt(2 * pi)));
}

double exponentialPDF(double x, parameters s){
	return x >=0 ? s[0] * exp(-s[0] * x) : 0;
}

normal2D normalAR(){
	prob exponentialP;
	exponentialP.pdfFunction = exponentialPDF;
	exponentialP.icdfFunction = iExponential;
	prob normalP;
	normalP.pdfFunction = normalPDF;
	parameters expP;
	expP.push_back(1);
	double U = randPool[poolPointer++];
	double Z1 = AcceptanceRejection(normalP, exponentialP, sqrt(2 * exp(1) / pi), emptyParas, expP);
	if (U < 0.5){
		Z1 *= -1;
	}
	U = randPool[poolPointer++];
	double Z2 = AcceptanceRejection(normalP, exponentialP, sqrt(2 * exp(1) / pi), emptyParas, expP);
	if (U < 0.5){
		Z2 *= -1;
	}
	return normal2D(Z1, Z2);
}

double payoffCall(double K, double S_T){
	return S_T - K > 0 ? (S_T - K) : 0;
}

double EuropeanCall(normalGenerator ng, double S_t, double K, double sigma, double T, double t, double r){
	normalG ong;
	switch (ng)
	{
		case boxMuller: ong = BoxMuller; break;
		case margaglia: ong = Margaglia; break;
		case ar: ong = normalAR; break;
		default: ong = normalAR;
	}
	double payoffExpectation = 0;
	for (int i = 0; i < numLoop; i++){
		normal2D n2D = ong();
		double S_T = S_t * exp((r - pow(sigma, 2) / 2) * (T - t) + sigma * sqrt(T - t) * n2D.first);
		payoffExpectation += payoffCall(K, S_T);
		S_T = S_t * exp((r - pow(sigma, 2) / 2) * (T - t) + sigma * sqrt(T - t) * n2D.second);
		payoffExpectation += payoffCall(K, S_T);
	}
	payoffExpectation /= 2 * numLoop;
	return exp(-r * (T - t)) * payoffExpectation;
}

void testingNormal(size_t n){
	numLoop = 10000;
	buildPool(numLoop);
	double sum = 0;
	std::cout << "Mean of sampling: " << std::endl;
	for (int i = 0; i < numLoop; i++){
		normal2D j = BoxMuller();
		sum += j.first + j.second;
	}
	std::cout << " box " << sum / numLoop << std::endl;

	poolPointer = 0; sum = 0;
	for (int i = 0; i < numLoop; i++){
		normal2D j = Margaglia();
		sum += j.first + j.second;
	}
	std::cout << " mar " << sum / numLoop << std::endl;

	poolPointer = 0; sum = 0;
	for (int i = 0; i < numLoop; i++){
		normal2D j = normalAR();
		sum += j.first + j.second;
	}
	std::cout << " AR " << sum / numLoop << std::endl; 
}

int main(){
	double S0 = 100, K = 100, sigma = 0.2, T = 1, r = 0.05;
	double t = 0;
	numLoop = 100000;
	buildPool(numLoop);
	std::cout << "Call is: " << std::endl;
	double k = EuropeanCall(ar, S0, K, sigma, T, t, r);
	std::cout << k << " AR " << std::endl;
	poolPointer = 0;
	k = EuropeanCall(boxMuller, S0, K, sigma, T, t, r);
	std::cout << k << " box " << std::endl;
	poolPointer = 0;
	k = EuropeanCall(margaglia, S0, K, sigma, T, t, r);
	std::cout << k << " Mar " << std::endl;
	//testingNormal(10000);
	return 0;
}
