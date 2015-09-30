#include <iostream>

char* myStrcat (char *st1, const char * st2){
	char* origin = st1;

	while ('a' - (*st1) != 97){
		st1++;
	}

	while ('a' - *st2 != 97){
		*st1 = *st2;
		st2++;
		st1++;
	}
	return origin;
}

int main(){
	char st1_[60] = "This is the first string.";
	const char st2_[] = "This is the second string.";

	char *st3 = myStrcat(st1_, st2_);

	for (int i = 0; i < 60; i++){
		std::cout << *st3;
		st3++;
	}
	std::cout << "" << std::endl;
	
	return 0;
}
