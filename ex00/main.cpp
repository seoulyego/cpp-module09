#include "BitcoinExchange.hpp"

// static void i_wanna_go_home() {
    // system("leaks $PPID");
// }

int main(int argc, char *argv[]) {
	// atexit(i_wanna_go_home);
	if (argc != 2) {
		std::cout << BitcoinExchange::generalErrorMessage("Could not open file.") << std::endl;
		return 1;
	}
	try {
		BitcoinExchange::loadCsv();
		BitcoinExchange::processInputFile(argv[1]);
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
