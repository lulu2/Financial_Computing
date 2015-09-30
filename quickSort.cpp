#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
size_t partition(std::vector<double>& array, size_t left, size_t right){
	double pivot = array[right];
	size_t less = left - 1;
	for (size_t more = left; more < right; more++){
		if (array[more] <= pivot) {
			less++;
			double temp = array[less];
			array[less] = array[more];
			array[more] = temp;
		}
	}
	double temp2 = array[less + 1];
	array[less + 1] = pivot;
	array[right] = temp2;
	return (less + 1);
}

void quickSort(std::vector<double>& array, size_t left, size_t right){
	if (left < right){
		size_t q = partition(array, left, right);
		if (q > 0){
			quickSort(array, left, q - 1);
		}
		if (q < right){
		quickSort(array, q + 1, right);
		}
	}
}

std::vector<double> randomVector (size_t n){
	srand(time(NULL));
	std::vector<double> output;
	output.resize(n);
	for (size_t i = 0; i < n; i++){
		output[i] = rand() % 100;
	}
	return output;
}

size_t getInput();

int main(){
	size_t n = getInput();
	std::vector<double> target = randomVector(n);
	printf("Randomly generated array is:\n");
	for (int i = 0; i < target.size(); i++){
		std::cout << target[i] << " ";
	}
	printf("\n");
	size_t exitP = n - 1; 
	quickSort(target, 0, exitP);
	printf("Sorted array is:\n");
	for (int i = 0; i < n; i++){
		std::cout << target[i] << " ";
	}
	std::cout <<'\n';
	return 0;
}

size_t getInput(){
	bool proceed = false;
	size_t n;
	while (!proceed){
		std::cout << "Input array size n:" << std::endl;
		std::cin >> n;
		if (std::cin.fail() || n <= 0){
			std::cout << "Error: Input must be a positive value" << std::endl;
			std::cin.clear();
		}
		else {
			proceed = true;
		}
		std::cin.ignore(INT_MAX, '\n');
	}
	return n;
}
