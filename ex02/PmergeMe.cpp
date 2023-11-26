#include "PmergeMe.hpp"

std::vector<int> PmergeMe::_vectorSequence;
std::deque<int> PmergeMe::_dequeSequence;
double PmergeMe::_vectorTime;
double PmergeMe::_dequeTime;

void PmergeMe::setSequence(std::vector<int> sequence) {
	_vectorSequence = sequence;
	for (size_t i = 0; i < sequence.size(); i++)
		_dequeSequence.push_back(sequence[i]);
}

size_t PmergeMe::getJacobsthalNumber(size_t index) {
	if (index <= 1)
		return 1;
	return getJacobsthalNumber(index - 1) + 2 * getJacobsthalNumber(index - 2);
}

std::vector<std::pair<int, int> > PmergeMe::makePairVector() {
	std::vector<std::pair<int, int> > pairSequence;
	for (size_t i = 0; i + 1 < _vectorSequence.size(); i += 2) {
		std::pair<int, int> pair;
		if (_vectorSequence[i] > _vectorSequence[i + 1])
			pair = std::make_pair(_vectorSequence[i], _vectorSequence[i + 1]);
		else
			pair = std::make_pair(_vectorSequence[i + 1], _vectorSequence[i]);
		pairSequence.push_back(pair);
	}
	return pairSequence;
}

void PmergeMe::mergeVector(std::vector<std::pair<int, int> >& pairVector, int left, int mid, int right) {
	std::vector<std::pair<int, int> > leftVector;
	std::vector<std::pair<int, int> > rightVector;
	for (int i = left; i <= mid; i++)
		leftVector.push_back(pairVector[i]);
	for (int i = mid + 1; i <= right; i++)
		rightVector.push_back(pairVector[i]);

	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = left;
	while (i < leftVector.size() && j < rightVector.size()) {
		if (leftVector[i] <= rightVector[j]) {
			pairVector[k] = leftVector[i];
			i++;
		}
		else {
			pairVector[k] = rightVector[j];
			j++;
		}
		k++;
	}
	while (i < leftVector.size()) {
		pairVector[k] = leftVector[i];
		i++;
		k++;
	}
	while (j < rightVector.size()) {
		pairVector[k] = rightVector[j];
		j++;
		k++;
	}
}

void PmergeMe::mergePairVector(std::vector<std::pair<int, int> >& pairVector, int left, int right) {
	if (left < right) {
		int middle = left + (right - left) / 2;
		mergePairVector(pairVector, left, middle);
		mergePairVector(pairVector, middle + 1, right);
		mergeVector(pairVector, left, middle, right);
	}
}

size_t PmergeMe::binarySearchVector(std::vector<int> sorted, int left, int right, int key) {
	if (right <= left) {
		if (key > sorted[left])
			return left + 1;
		return left;
	}
	int mid = (left + right) / 2;
	if (key == sorted[mid])
		return mid + 1;
	if (key > sorted[mid])
		return binarySearchVector(sorted, mid + 1, right, key);
	return binarySearchVector(sorted, left, mid - 1, key);
}

void PmergeMe::mergeInsertionSortVector() {
	clock_t startTime = clock();
	if (_vectorSequence.size() > 1) {
		std::vector<std::pair<int, int> > pairSequence;
		int remainder = 0;
		if (_vectorSequence.size() % 2 == 1) {
			remainder = _vectorSequence[_vectorSequence.size() - 1];
			_vectorSequence.pop_back();
		}
		pairSequence = makePairVector();
		mergePairVector(pairSequence, 0, pairSequence.size() - 1);
		std::vector<int> sortedSequence;
		for (unsigned int i = 0; i < pairSequence.size(); i++)
			sortedSequence.push_back(pairSequence[i].first);
		sortedSequence.insert(sortedSequence.begin(), pairSequence[0].second);
		size_t jacobIndex = 2;
		for (std::vector<std::pair<int, int> >::size_type prevPairIndex = 0; prevPairIndex < pairSequence.size(); jacobIndex++) {
			size_t curPairIndex = getJacobsthalNumber(jacobIndex) - 1;
			if (curPairIndex >= pairSequence.size())
				curPairIndex = pairSequence.size() - 1;
			for (; curPairIndex > prevPairIndex; curPairIndex--) {
				std::vector<int>::size_type insertIndex = binarySearchVector(sortedSequence, 0, sortedSequence.size() - 1, pairSequence[curPairIndex].second);
				sortedSequence.insert(sortedSequence.begin() + insertIndex, pairSequence[curPairIndex].second);
			}
			prevPairIndex = getJacobsthalNumber(jacobIndex) - 1;
		}
		if (remainder != 0) {
			size_t insertIndex = binarySearchVector(sortedSequence, 0, sortedSequence.size() - 1, remainder);
			sortedSequence.insert(sortedSequence.begin() + insertIndex, remainder);
		}
		_vectorSequence = sortedSequence;
	}
	clock_t finishTime = clock();
	_vectorTime = (finishTime - startTime) * 1000;
}

std::deque<std::pair<int, int> > PmergeMe::makePairDeque() {
	std::deque<std::pair<int, int> > pairSequence;
	for (size_t i = 0; i + 1 < _dequeSequence.size(); i += 2) {
		std::pair<int, int> pair;
		if (_dequeSequence[i] > _dequeSequence[i + 1])
			pair = std::make_pair(_dequeSequence[i], _dequeSequence[i + 1]);
		else
			pair = std::make_pair(_dequeSequence[i + 1], _dequeSequence[i]);
		pairSequence.push_back(pair);
	}
	return pairSequence;
}

void PmergeMe::mergeDeque(std::deque<std::pair<int, int> >& pairDeque, int left, int mid, int right) {
	std::deque<std::pair<int, int> > leftDeque;
	std::deque<std::pair<int, int> > rightDeque;
	for (int i = left; i <= mid; i++)
		leftDeque.push_back(pairDeque[i]);
	for (int i = mid + 1; i <= right; i++)
		rightDeque.push_back(pairDeque[i]);

	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = left;
	while (i < leftDeque.size() && j < rightDeque.size()) {
		if (leftDeque[i] <= rightDeque[j]) {
			pairDeque[k] = leftDeque[i];
			i++;
		}
		else {
			pairDeque[k] = rightDeque[j];
			j++;
		}
		k++;
	}
	while (i < leftDeque.size()) {
		pairDeque[k] = leftDeque[i];
		i++;
		k++;
	}
	while (j < rightDeque.size()) {
		pairDeque[k] = rightDeque[j];
		j++;
		k++;
	}
}

void PmergeMe::mergePairDeque(std::deque<std::pair<int, int> >& pairDeque, int left, int right) {
	if (left < right) {
		int middle = left + (right - left) / 2;
		mergePairDeque(pairDeque, left, middle);
		mergePairDeque(pairDeque, middle + 1, right);
		mergeDeque(pairDeque, left, middle, right);
	}
}

size_t PmergeMe::binarySearchDeque(std::deque<int> sorted, int left, int right, int key) {
	if (right <= left) {
		if (key > sorted[left])
			return left + 1;
		return left;
	}
	int mid = (left + right) / 2;
	if (key == sorted[mid])
		return mid + 1;
	if (key > sorted[mid])
		return binarySearchDeque(sorted, mid + 1, right, key);
	return binarySearchDeque(sorted, left, mid - 1, key);
}

void PmergeMe::mergeInsertionSortDeque() {
	clock_t startTime = clock();
	if (_vectorSequence.size() > 1) {
		std::deque<std::pair<int, int> > pairSequence;
		int remainder = 0;
		if (_dequeSequence.size() % 2 == 1) {
			remainder = _dequeSequence[_dequeSequence.size() - 1];
			_dequeSequence.pop_back();
		}
		pairSequence = makePairDeque();
		mergePairDeque(pairSequence, 0, pairSequence.size() - 1);
		std::deque<int> sortedSequence;
		for (unsigned int i = 0; i < pairSequence.size(); i++)
			sortedSequence.push_back(pairSequence[i].first);
		sortedSequence.insert(sortedSequence.begin(), pairSequence[0].second);
		size_t jacobIndex = 2;
		for (std::deque<std::pair<int, int> >::size_type prevPairIndex = 0; prevPairIndex < pairSequence.size(); jacobIndex++) {
			size_t curPairIndex = getJacobsthalNumber(jacobIndex) - 1;
			if (curPairIndex >= pairSequence.size())
				curPairIndex = pairSequence.size() - 1;
			for (; curPairIndex > prevPairIndex; curPairIndex--) {
				std::deque<int>::size_type insertIndex = binarySearchDeque(sortedSequence, 0, sortedSequence.size() - 1, pairSequence[curPairIndex].second);
				sortedSequence.insert(sortedSequence.begin() + insertIndex, pairSequence[curPairIndex].second);
			}
			prevPairIndex = getJacobsthalNumber(jacobIndex) - 1;
		}
		if (remainder != 0) {
			size_t insertIndex = binarySearchDeque(sortedSequence, 0, sortedSequence.size() - 1, remainder);
			sortedSequence.insert(sortedSequence.begin() + insertIndex, remainder);
		}
		_dequeSequence = sortedSequence;
	}
	clock_t finishTime = clock();
	_dequeTime = (finishTime - startTime) * 1000;
}

void PmergeMe::printUnsorted() {
	std::cout << "Before:  ";
	for (std::vector<int>::size_type i = 0; i < _vectorSequence.size(); i++) {
		if (i != 0)
			std::cout << " ";
		std::cout << _vectorSequence[i];
	}
	std::cout << std::endl;
}

void PmergeMe::printSorted() {
	std::cout << "After:   ";
	for (std::vector<int>::size_type i = 0; i < _vectorSequence.size(); i++) {
		if (i != 0)
			std::cout << " ";
		std::cout << _vectorSequence[i];
	}
	std::cout << std::endl;
}

void PmergeMe::printVectorTime() {
	std::cout << "Time to process a range of " << _vectorSequence.size() <<
	" elements with std::vector : " << _vectorTime / CLOCKS_PER_SEC << " ms" << std::endl;
}

void PmergeMe::printDequeTime() {
	std::cout << "Time to process a range of " << _dequeSequence.size() <<
	" elements with std::list : " << _dequeTime / CLOCKS_PER_SEC << " ms" << std::endl;
}

// void PmergeMe::printIsAscendingVector() {
	// std::cout << "Vector sorting: " << std::boolalpha << std::is_sorted(_vectorSequence.begin(), _vectorSequence.end()) << std::endl;
// }

// void PmergeMe::printIsAscendingDeque() {
	// std::cout << "Deque sorting: " << std::boolalpha << std::is_sorted(_dequeSequence.begin(), _dequeSequence.end()) << std::endl;
// }
