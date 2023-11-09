#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << BitcoinExchange::errorMessage("Invalid number of input") << std::endl;
		return 1;
	}
	try {
		BitcoinExchange::openCsvFile();
		BitcoinExchange::openInputFile(argv[1]);
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
