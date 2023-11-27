#include "PmergeMe.hpp"

// static void i_wanna_go_home() {
    // system("leaks $PPID");
// }

int main(int argc, char *argv[]) {
    try {
        // atexit(i_wanna_go_home);
        PmergeMe::sortMe(argc, argv);
        // PmergeMe::printIsAscendingVector();
        // PmergeMe::printIsAscendingDeque();
        PmergeMe::printDequeTime();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
