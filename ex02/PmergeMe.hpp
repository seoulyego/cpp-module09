#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

class PmergeMe {
public:
  static void setSequence(std::vector<int> sequence);
  static size_t getJacobsthalNumber(size_t index);

  static std::vector<std::pair<int, int>> makePairVector();
  static void mergeVector(std::vector<std::pair<int, int>> &pairVector,
                          int left, int mid, int right);
  static void mergePairVector(std::vector<std::pair<int, int>> &pairVector,
                              int left, int right);
  static std::vector<int>::size_type
  binarySearchVector(std::vector<int> sorted, int left, int right, int key);
  static void mergeInsertionSortVector();

  static std::deque<std::pair<int, int>> makePairDeque();
  static void mergeDeque(std::deque<std::pair<int, int>> &pairDeque, int left,
                         int mid, int right);
  static void mergePairDeque(std::deque<std::pair<int, int>> &pairDeque,
                             int left, int right);
  static std::deque<int>::size_type
  binarySearchDeque(std::deque<int> sorted, int left, int right, int key);
  static void mergeInsertionSortDeque();

  static void printUnsorted();
  static void printSorted();
  static void printVectorTime();
  static void printDequeTime();

  static void sortMe(int argc, char *argv[]);

  static void printIsAscendingVector();
  static void printIsAscendingDeque();

private:
  static std::vector<int> _vectorSequence;
  static std::deque<int> _dequeSequence;
  static double _vectorTime;
  static double _dequeTime;

  PmergeMe();
  PmergeMe(PmergeMe const &object);
  ~PmergeMe();
  PmergeMe &operator=(PmergeMe const &object);
};

#endif // PMERGEME_HPP
