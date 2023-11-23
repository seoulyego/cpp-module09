#include "PmergeMe.hpp"
#include <iostream>

std::vector<int> PmergeMe::_vectorSequence;
std::list<int> PmergeMe::_listSequence;
double PmergeMe::_vectorTime;
double PmergeMe::_listTime;

void PmergeMe::mergeInsertSortVector() {
	;
}

void PmergeMe::sortVector() {
	clock_t startTime = clock();
	mergeInsertSortVector();
	clock_t finishTime = clock();
	_vectorTime = finishTime - startTime;
}

void PmergeMe::mergeInsertSortList() {
	;
}

void PmergeMe::sortList() {
	clock_t startTime = clock();
	mergeInsertSortList();
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
	" elements with std::vector : " << _vectorTime << " ms" << std::endl;
}

void PmergeMe::printListTime() {
	std::cout << "Time to process a range of " << _listSequence.size() <<
	" elements with std::list : " << _listTime << " ms" << std::endl;
}

void PmergeMe::print() {
	printUnsorted();
	sortVector();
	printSorted();
	printVectorTime();
	sortList();
	printListTime();
}
