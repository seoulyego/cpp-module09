#include "PmergeMe.hpp"
#include <limits>
#include <algorithm>
#include <sstream>
#include <iostream>

void i_wanna_go_home() {
    system("leaks $PPID");
}

static bool validateNumber(std::string str) {
    char *endptr = NULL;
    long value = std::strtol(str.c_str(), &endptr, 10);
    if (value == 0 && !std::isdigit(str[0]))
        return false;
    if (*endptr != '\0')
        return false;
    if (value <= 0 || value > std::numeric_limits<int>::max())
        return false;
    return true;
}

static std::vector<int> validateInput(int argc, char *argv[]) {
	if (argc < 2)
		throw std::runtime_error("Error: need more parameters");
	std::vector<int> inputData;
	for (int i = 1; i < argc; i++) {
		std::istringstream ss(argv[i]);
		for (std::string inputBuffer; std::getline(ss, inputBuffer, ' ');) {
			if (inputBuffer.empty())
				break ;
			if (!validateNumber(inputBuffer))
				throw std::runtime_error("Error: invalid input number");
			int number = static_cast<int>(std::strtol(inputBuffer.c_str(), NULL, 10));
			// if (std::find(inputData.begin(), inputData.end(), number) != inputData.end())
			// 	throw std::runtime_error("Error: duplicate input number");
			inputData.push_back(number);
		}
	}
    if (inputData.empty())
        throw std::runtime_error("Error: empty input data");
	return inputData;
}

int main(int argc, char *argv[]) {
    try {
        // atexit(i_wanna_go_home);
        PmergeMe::setSequence(validateInput(argc, argv));
        PmergeMe::printUnsorted();
        PmergeMe::mergeInsertionSortVector();
        PmergeMe::printSorted();
        PmergeMe::printVectorTime();
        // PmergeMe::mergeInsertionSortList();
        // PmergeMe::printListTime();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
