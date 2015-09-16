#include <iostream>
#include <cmath>
#include <vector>
#include <iterator>
#include <climits>

int main()
{	
	std::cout << "Generate random array of length N-1 with one number between 1 and N missed:" << std::endl;
	unsigned int N;

	//Following is to generate an array.
	bool proceed = false;
	while (!proceed){
		std::cout << "Input an possitive integer N > 1 and press enter:" << std::endl;
		std::cin >> N;
		if (std::cin.fail() || N == 0 || N == 1){
			std::cout << "Error: Input must be a positive integer larger than 1, input again" << std::endl;
			std::cin.clear();
		}
		else {
			proceed = true;
			std::cout << "N is " << N << "."<< std::endl;
		}
		std::cin.ignore(INT_MAX, '\n');
	}

	std::vector<int> input;
	input.resize(++N);

	for (int i = 0; i < N; i++){
    	input[i] = i;
	}
	std::random_shuffle(input.begin() + 1, input.end());
	input.resize(N - 1);

	std::cout << "Generated array is [ ";
	std::vector<int>::iterator i = input.begin() + 1;
	while (i != input.end ()){
    	std::cout << *i << " ";
    	++i;
   	}
   	std::cout << "]" << std::endl;
   	
   	//Following is to find the missed number in array input. Time complexity is O(N). 
	std::vector<int> buffer;
	buffer.resize(N);
	i = input.begin();
   	while (i != input.end()){
       buffer[*i] = 1;
       i++;
   	}

	for (int j = 0; j < N; j ++){
		if (!buffer[j]){
			std::cout << "The missed number is " << j << "." << std::endl;
			break;
		}
	}
}
