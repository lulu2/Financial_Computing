#include <iostream>
#include <stdio.h>
#include <stdlib.h>
char * stringReverse(const char *st){
	int n = 0;
	while (st[++n] != '\0'){}
	char * reversed = new char[n];
	char * origin = reversed;
	st += n - 1;

	for (int i = 0; i < n; i++){
		reversed[i] = *st;
		st--;
	}
	return origin;
}

const char * randomCharArray(int n){
	char * stringIn = new char[n];
	if (stringIn == NULL) exit (1);
	srand(time(NULL));
	for (size_t i = 0; i < n; i++){
		stringIn[i] = rand()%90 + '!';
	}
	stringIn[n] = '\0';
	const char* output = stringIn;
	return output;
}

int main(){
	int n;
	printf("Input generated string length:");
	scanf ("%i", &n);
	try{
		if (!n) throw "String length must be larger than 0.\n";
		const char * target = randomCharArray(n);
		
		printf("Generated string is:\n");
		int i = 0;
		while (target[i] != '\0'){
			std::cout << target[i++];
		}
		printf("\n");
		
		char* output = stringReverse(target);
		delete [] target;
		printf("Reversed string is:\n");
		i = 0;
		while (output[i] != '\0'){
			std::cout << output[i++];
		}
		printf("\n");
		delete [] output;
	}
	catch(const char* m){
		std::cout << m;
	}
	return 0;
}
