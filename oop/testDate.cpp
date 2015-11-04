#include "Date.hpp"
#include <iostream>
using namespace std;
int main(){
	Date k(5,6,7);
	cout << k.testLeap() << endl;
	cout << k.testValid() << endl;
	k.add_days(365);
	pDate(k);
	k.add_months(15);
	pDate(k);
	Date kk(9,30,9);
	bool t = k == kk;
	cout << t << endl;
	pDate(k);
	pDate(kk);
	cout << k <<endl;
	cout << k - kk <<endl;
	cout << Date::Julian(k, kk) << endl;
	cout << Date::CountACT_365(k, kk) << endl;
	cout << (k < kk) <<endl;
	cout << (k != kk) <<endl;
	cout << (k > kk) <<endl;
	return 0;
}
