#include "PmergeMe.hpp"
#include <iostream>

std::vector<int> PmergeMe::_vectorSequence;
std::list<int> PmergeMe::_listSequence;
double _vectorTime;
double _listTime;

void PmergeMe::sortVector() {
	clock_t startTime = clock();
	clock_t finishTime = clock();
	_vectorTime = finishTime - startTime;
}

void PmergeMe::sortList() {
	clock_t startTime = clock();
	clock_t finishTime = clock();
	_listTime = finishTime - startTime;

}

void PmergeMe::printUnsorted() {
	std::cout << "Before:  ";
	for (int i = 0; i < _vectorSequence.size(); i++) {
		if (i != 0)
			std::cout << " ";
		std::cout << _vectorSequence[i];
	}
	std::cout << std::endl;
}

void PmergeMe::printSorted() {
	std::cout << "After:   ";
	for (int i = 0; i < _vectorSequence.size(); i++) {
		if (i != 0)
			std::cout << " ";
		std::cout << _vectorSequence[i];
	}
	std::cout << std::endl;
}

void PmergeMe::printVectorTime() {
	std::cout << "Time to process a range of " << _vectorSequence.size() <<
	" elements with std::vector : " << _vectorTime << " us" << std::endl;
}

void PmergeMe::printListTime() {
	std::cout << "Time to process a range of " << _listSequence.size() <<
	" elements with std::list : " << _listTime << " us" << std::endl;
}

void PmergeMe::print() {
	printUnsorted();
	sortVector();
	printSorted();
	printVectorTime();
	sortList();
	printListTime();
}
