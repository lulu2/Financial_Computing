#include <iostream>
#include <cmath>
#include <vector>

typedef std::vector<std::vector<double>> splineParameters;

double price(double currentMaturity, double currentSR, double coupon){
	double couponTimes = floor(currentMaturity / 0.5);
	double slope = currentSR / currentMaturity;
	double price = 0;
	for (int i = 0; i < couponTimes; i++){
		double r = currentSR - 0.5 * slope * (i + 1);
		price += 0.5 * coupon * 0.01 * exp(-r * (currentMaturity - (i + 1) * 0.5));
	}
	price += (1 + 0.5 * coupon) * exp(-currentSR * currentMaturity);
	return 100 * price;
}

double getSpotRate(double currentMaturity, double currentPrice, double coupon){
	double estimation0 = 0;
	double estimation1 = 1;
	double estimation = (estimation0 + estimation1) / 2;
	double term = price(currentMaturity, estimation, coupon) - currentPrice;
	while (std::abs(term) > 0.001){
		double term0 = price(currentMaturity, estimation0, coupon) - currentPrice;
		double term1 = price(currentMaturity, estimation1, coupon) - currentPrice;
		if (term0 * term1 > 0){
			estimation1 *= 1.5;
		}
		else if (term0 == 0){
			estimation = estimation0;
			break;
		}
		else if (term1 == 0){
			estimation = estimation1;
			break;
		}
		else{
			if (term1 * term < 0) {
				estimation0 = estimation;
			}
			else {
				estimation1 = estimation;
			}
		}
		estimation = (estimation0 + estimation1) / 2;
		term = price(currentMaturity, estimation, coupon) - currentPrice;
		//std::cout << "term is" << term << std::endl;
	}
	return estimation;
}

std::vector<double> getSRSet(){
	std::vector<double> sr;
	sr.push_back(0);
	sr.push_back(0);
	sr.push_back(0);
	sr.push_back(-log(99.96/100) / 0.5014);
	double r = -log(99.77/100) / 0.9425;
	sr.push_back(r);
	r = getSpotRate(1.9836, 100.00025, 0.625);
	sr.push_back(r);
	r = getSpotRate(3.0247, 100.2658875, 0.875);
	sr.push_back(r);
	r = getSpotRate(4.9863, 100.0688375, 1.375);
	sr.push_back(r);
	r = getSpotRate(6.9863, 100.043975, 1.750);
	sr.push_back(r);
	r = getSpotRate(9.8630, 99.724, 2.00);
	sr.push_back(r);
	r = getSpotRate(29.877, 100.133625, 2.875);
	sr.push_back(r);
	return sr;
}

std::vector<double> getForward(std::vector<double> m){
	std::vector<double> forward;
	std::vector<double> sr = getSRSet();
	for (int i = 0; i < sr.size(); i++){
		double temp = (sr[i + 1] - sr[i]) / (m[i + 1] - sr[i]);
		forward.push_back(temp);
	}
	return forward;
}

splineParameters getSpline(std::vector<double> yields, std::vector<double> points){
	int n = yields.size() - 1;
	std::vector<double> aVec;
	aVec.resize(n);
	std::vector<double> bVec;
	bVec.resize(n);
	std::vector<double> cVec;
	cVec.resize(n);
	std::vector<double> dVec;
	dVec.resize(n);
	std::vector<double> hVec;
	hVec.resize(n);
	for (int i = 0; i < n; i++){
		hVec[i] = points[i + 1] - points[i];
	}
	for (int i = 1; i < n; i++){
		bVec[i] = 2 * (hVec[i - 1] + hVec[i]);
	}
	for (int i = 1; i < n - 1; i++){
		cVec[i] = hVec[i];
	}
	for (int i = 2; i < n; i++){
		aVec[i] = hVec[i - 1];
	}
	for (int i = 1; i < n; i++){
		dVec[i] = 6 * ((yields[i + 1] - yields[i]) / hVec[i] - (yields[i] - yields[i - 1]) / hVec[i - 1]);
	}
	std::vector<double> tilda_cVec;
	tilda_cVec.resize(n);
	std::vector<double> tilda_dVec;
	tilda_dVec.resize(n);
	std::vector<double> mVec;
	mVec.resize(n + 1);
	tilda_cVec[1] = cVec[1] / bVec[1];
	for (int i = 2; i < n; i++){
		tilda_cVec[i] = cVec[i] / (bVec[i] - tilda_cVec[i - 1] * aVec[i]);
	}
	tilda_dVec[1] = dVec[1] / bVec[1];
	for (int i = 2; i < n; i++){
		tilda_dVec[i] = (dVec[i] - tilda_dVec[i - 1] * aVec[i]) / (bVec[i] - tilda_cVec[i - 1] * aVec[i]);
	}
	mVec[n - 1] = tilda_dVec[n - 1];
	for (int i = n - 2; i > 0; i--){
		mVec[i] = tilda_dVec[i] - tilda_cVec[i] * mVec[i + 1];	
	}
	mVec[0] = 0;
	mVec[n] = 0;

	std::vector<double> a_i;
	a_i.resize(n);
	std::vector<double> b_i;
	b_i.resize(n);
	std::vector<double> c_i;
	c_i.resize(n);
	std::vector<double> d_i;
	d_i.resize(n);
	for (int i = 0; i < n; i++){
		a_i[i] = yields[i];
	}
	for (int i = 0; i < n; i++){
		b_i[i] = (yields[i + 1] - yields[i]) / hVec[i] - (mVec[i + 1] / 6 + mVec[i] / 3) * hVec[i];
	}
	for (int i = 0; i < n; i++){
		c_i[i] = mVec[i] / 2;
	}
	for (int i = 0; i < n; i++){
		d_i[i] = (mVec[i + 1] - mVec[i]) / (6 * hVec[i]);
	}
	splineParameters output;
	output.push_back(a_i);
	output.push_back(b_i);
	output.push_back(c_i);
	output.push_back(d_i);
	return output;
} 

double buildCurve(double t, double r_t, double F_t, double delta){
	return (r_t * t + F_t * delta) / (t + delta);
}

int main(){
	std::vector<double> intervalPoint;
	intervalPoint.push_back(0.0795);
	intervalPoint.push_back(0.2521);
	intervalPoint.push_back(0.5014);
	intervalPoint.push_back(0.9425);
	intervalPoint.push_back(1.9836);
	intervalPoint.push_back(3.0247);
	intervalPoint.push_back(4.9863);
	intervalPoint.push_back(6.9863);
	intervalPoint.push_back(9.8630);
	intervalPoint.push_back(29.877);
	std::vector<double> temp = getForward(intervalPoint);
	splineParameters sp = getSpline(temp, intervalPoint);
	std::cout << "Get Parameter of curve of forward rate:" << std::endl;
	std::cout << "For a_i + b_i(t - t_i) + c_i(t - t_i)^2 + d_i(t - t_i)^3, parameters are:" << std::endl;
	int count = 0;
	for (std::vector<double> i : sp){
		if (count == 0) {
			std::cout << "a_i are:" << std::endl;
		}
		else if (count == 1) {
			std::cout << "b_i are:" << std::endl;
		}
		else if (count == 2) {
			std::cout << "c_i are:" << std::endl;
		}
		else if (count == 3) {
			std::cout << "d_i are:" << std::endl;
		}
		for (double j : i){
			std::cout << j << ", ";
		}
		count++;
		std::cout << '\n';
	}
	std::cout << "t_i are 0 and maturities given in the table except 29.877" << std::endl;
	std::cout << "\n" << std::endl;

	temp = getSRSet();
	sp = getSpline(temp, intervalPoint);
	std::cout << "Get Parameter of yield curve:" << std::endl;
	std::cout << "For a_i + b_i(t - t_i) + c_i(t - t_i)^2 + d_i(t - t_i)^3, parameters are:" << std::endl;
	count = 0;
	for (std::vector<double> i : sp){
		if (count == 0) {
			std::cout << "a_i are:" << std::endl;
		}
		else if (count == 1) {
			std::cout << "b_i are:" << std::endl;
		}
		else if (count == 2) {
			std::cout << "c_i are:" << std::endl;
		}
		else if (count == 3) {
			std::cout << "d_i are:" << std::endl;
		}
		for (double j : i){
			std::cout << j << ", ";
		}
		count++;
		std::cout << '\n';
	}
	std::cout << "t_i are 0 and maturities given in the table except 29.877" << std::endl;

}

