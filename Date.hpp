#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>
using namespace std;

class Date {

private:																	
	static const int month_nb;												
	
	static const unsigned char month_days[];								//days in each month, non-leap year
												
	static const unsigned char month_daysLeap[];							//days in each month, non-leap year
													

protected:																	
	static bool testLeap(const int year_){
		if (year_%4 != 0){
			return false;} 
		else if (year_%400 == 0){
			return true;
		}
		else if (year_%100 == 0){
			return false;
		}
		else{
			return true;
		}
	}									
	bool isLeap;											
	int year;
	int month;
	int day;

public:

	Date();												
	Date(const int month_,const int day_,const int year_): year(year_), month(month_), day(day_)
	{
		if (testLeap(year)){
			isLeap = true;
		}
		else {
			isLeap = false;
		}
	}

	int get_month() const {return month;}						
	int get_day() const {return day;}
	int get_year() const {return year;}

	void set_month(int m){month = m;}								
	void set_day(int d){day = d;}										
	void set_year(int y){year = y;}									
	
	void add_months(int m);				
	void add_days(int m);										

	bool testLeap() const{
		if (year%4 != 0){
			return false;} 
		else if (year%400 == 0){
			return true;
		}
		else if (year%100 == 0){
			return false;
		}
		else{
			return true;
		}
	}		

	bool testValid() const{
		if (month > month_nb || month < 1){
			return false;
		}
		else if (year < 0){
			return false;
		}
		else{
			if ((month_days[month - 1] < day) && !testLeap()){
				return false;
			}
			else if ((month_daysLeap[month - 1] < day) && testLeap()){
				return false;
			}
			else return true;
		}
	}
					
	int operator-(const Date & date) const{
		Date temp(month, day, year);
		Date temp2(date.get_month(), date.get_day(), date.get_year());
		int sign = 1;
		if (year > date.get_year()){
			sign = 1;
		}
		else if (year < date.get_year()){
			sign = -1;
		}
		else if (month < date.get_month()){
			sign = -1;
		}
		else if (month > date.get_month()){
			sign = 1;
		}
		else if (day < date.get_day()){
			sign = -1;
		}
		else if (day > date.get_day()){
			sign = 1;
		}
		else {
			return 0;
		}
		int m = 0;
		if (sign == 1){
			while (!((temp.get_month() == temp2.get_month()) && (temp.get_day() == temp2.get_day()) && (temp.get_year() == temp2.get_year()))){
				temp2.add_days(1);
				m++;
			}
		}
		else{
			while (!((temp.get_month() == temp2.get_month()) && (temp.get_day() == temp2.get_day()) && (temp.get_year() == temp2.get_year()))){
				temp.add_days(1);
				m--;
			}
		}
		return m;
	}

	static int Julian(const Date & date1,const Date & date2){
		return date1 - date2;
	}

	static double CountACT_365(const Date & date1,const Date & date2){
		return (double) (date1 - date2) / 365;
	}

	int Julian(const Date & date) const{
		return *this - date;
	}
	
	double CountACT_365(const Date & date) const{
		return (*this - date) / 365;
	}
	
	
	friend ostream& operator<<(ostream& os,const Date& d){
		os << d.get_month() << '/' << d.get_day() << '/' << d.get_year();
    	return os;
	}					//Stream "<<" overloading
};

const int Date::month_nb = 12;
const unsigned char Date::month_days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
const unsigned char Date::month_daysLeap[] = {31,29,31,30,31,30,31,31,30,31,30,31};

bool operator==(const Date& d1, const Date& d2){
	if ((d1.get_month() == d2.get_month()) && (d1.get_day() == d2.get_day()) && (d1.get_year() == d2.get_year())){
		return true;
	}
	else{
		return false;
	}
}

bool operator !=(const Date& d1, const Date& d2){
	return !(d1==d2);
}

bool operator > (const Date& d1, const Date& d2) {
	if (d1 == d2) {
		return false;
	}
	else{
		if (d1.get_year() < d2.get_year()){
			return false;
		}
		else if (d1.get_year() > d2.get_year()){
			return true;
		}
		else if (d1.get_month() > d2.get_month()){
			return true;
		}
		else if (d1.get_month() < d2.get_month()){
			return false;
		}
		else if (d1.get_day() > d2.get_day()){
			return true;
		}
		else if (d1.get_day() < d2.get_day()){
			return false;
		}
		else{
			return false;
		}
	}
}

bool operator < (const Date& d1, const Date& d2){
	if (d1 == d2) {
		return false;
	}
	else{
		return !(d1 > d2);
	}
}

void Date::add_months(int m){
	int addYear = m / 12;
	int addMonth = m % 12;
	year += addYear;
	month += addMonth;
	day = month_days[month - 1];
}

void Date::add_days(int m){
	int predictYear = year;
	while (m > 0){
		if (month == 2){
			if (testLeap()){
				if (day == 29){
					day = 1;
					month = 3;
				}
				else{
					day++;
				}
			}
			else {
				if (day == 28){
					day = 1;
					month = 3;
				}
				else{
					day++;
				}
			}
		}
		else{
			if ((day == month_days[month - 1]) && (month < 12)){
				day = 1;
				month++;
			}
			else if ((day == month_days[month - 1]) && (month == 12)){
				year++;
				month = 1;
				day = 1;
			}
			else {
				day++;
			}
		}
		m--;
	}
}

void pDate(Date d){
	std::cout << d.get_month() << '/' << d.get_day() << '/' << d.get_year() << std::endl;
}




#endif

