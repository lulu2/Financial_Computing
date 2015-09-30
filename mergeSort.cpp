#include <iostream>
#include <vector>
template<typename T>
void merge(std::vector<T>& input, size_t p, size_t q, size_t r){
	size_t n_1 = q - p + 1;
	size_t n_2 = r - q;
	std::vector<T> v_1 (n_1);
	std::vector<T> v_2 (n_2);
	int j = p;
	for (size_t i = 0; i < n_1; i++){
		v_1[i] = input[j++];
	}
	for (size_t i = 0; i < n_2; i++){
		v_2[i] = input[j++];
	}
	for (size_t i = p; i <= r; i++){
		if (v_1.empty()) {
			input[i] = v_2[0];
			v_2.erase(v_2.begin());
		}
		else if (v_2.empty()) {
			input[i] = v_1[0];
			v_1.erase(v_1.begin());
		}
		else{
			if (v_1[0] < v_2[0]){
				input[i] = v_1[0];
				v_1.erase(v_1.begin());
			}
			else{
				input[i] = v_2[0];
				v_2.erase(v_2.begin());
			}
		}
	}
}

template<typename T>
void splitSort(std::vector<T>& input, size_t p, size_t r){
	if (p < r){
		size_t q = (p + r) / 2;
		if (p == q){
			if (input[p] > input[r]){
				T temp = input[p];
				input[p] = input[r];
				input[r] = temp;
			}
		}
		else{
			splitSort(input, p, q);
			splitSort(input, q + 1, r);
			merge(input, p, q, r);
		}
	}
}

template<typename T>
void mergeSort(std::vector<T>& input){
	splitSort(input, 0, input.size() - 1);
}

int main(){
	std::vector<double> input;
	input.push_back(1.5);
	input.push_back(2.5);	
	input.push_back(7.5);
	input.push_back(4.5);
	input.push_back(-5.5);
	input.push_back(9.5);
	std::cout << "double arrar is: \n";
	for (int i = 0; i < input.size(); i++){
		std::cout << input[i] << " ";
	}
	std::cout << '\n';
	mergeSort(input);
	std::cout << "sorted double array is: \n";
	for (int i = 0; i < input.size(); i++){
		std::cout << input[i] << " ";
	}
	std::cout << '\n';

	std::vector<char> inputC;
	inputC.push_back('a');
	inputC.push_back('c');	
	inputC.push_back('z');
	inputC.push_back('r');
	inputC.push_back('k');
	inputC.push_back('p');
	std::cout << "char array is: \n";
	for (int i = 0; i < inputC.size(); i++){
		std::cout << inputC[i] << " ";
	}
	std::cout << '\n';
	mergeSort(inputC);
	std::cout << "sorted char array is: \n";
	for (int i = 0; i < inputC.size(); i++){
		std::cout << inputC[i] << " ";
	}
	std::cout << '\n';
}
