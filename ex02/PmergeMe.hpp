#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <string>
#include <list>
#include <vector>
#include <ctime>

class PmergeMe {
	public:
		static void mergeInsertSortVector();
		static void sortVector();
		static void mergeInsertSortList();
		static void sortList();

		static void printUnsorted();
		static void printSorted();
		static void printVectorTime();
		static void printListTime();
		static void print();

	private:
		static std::vector<int> _vectorSequence;
		static std::list<int> _listSequence;
		static double _vectorTime;
		static double _listTime;

		PmergeMe();
		PmergeMe(PmergeMe const &object);
		~PmergeMe();
		PmergeMe &operator=(PmergeMe const &object);
};

#endif  // PMERGEME_HPP
