#include <iostream>
#include <climits>
#include <vector>

//Function declaration is specifically required by instructor.
void myBubbleSort (double* arr, int size){
	if (size > 1){
		double* entry =  arr;
		double* mark = arr;
		double key = *arr;
		arr++;
		for (int i = 0; i < size - 1; i++){
			if (*arr > key){
				mark = arr;
				key = *arr;
			}
			arr++;
		}
		*mark = *entry;
		*entry = key;
		return myBubbleSort(++entry, --size);
	}
}

size_t getInput();
std::vector<double> randomVector (size_t n);

int main(){
	size_t n = getInput();
	std::vector<double> target = randomVector(n);
	printf("Randomly generated array is:\n");
	for (int i = 0; i < target.size(); i++){
		std::cout << target[i] << " ";
	}
	std::cout << '\n';
	double* arr = &target[0];
	myBubbleSort(arr, n);
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

std::vector<double> randomVector (size_t n){
	std::vector<double> output;
	output.resize(n);
	for (size_t i = 0; i < n; i++){
		output[i] = rand() % 1000;
	}
	return output;
}
