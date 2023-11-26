#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <string>
# include <list>
# include <vector>
# include <ctime>

class PmergeMe {
	public:
		static const std::vector<int>& getVectorSequence();
		static const std::list<int>& getListSequence();
		static void setSequence(std::vector<int> sequence);

		static std::vector<std::pair<int, int> > makePairVector();
		static void mergePairVector(std::vector<std::pair<int, int> >& pairVector, int left, int right);
		static void mergeVector(std::vector<std::pair<int, int> >& pairVector, int left, int mid, int right);
		static size_t getJacobsthalNumber(size_t index);
		static size_t binarySearchVector(std::vector<int> sortedVector, int left, int right, int key);
		static void mergeInsertionSortVector();

		static void mergePairList();
		static void mergeInsertionSortList();

		static void printUnsorted();
		static void printSorted();
		static void printVectorTime();
		static void printListTime();
		static void printIsAscending();

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
