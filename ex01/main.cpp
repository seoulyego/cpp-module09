#include "RPN.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[]) {
	try {
		if (argc != 2)
			throw std::runtime_error("Error");
		RPN::setExpression(argv);
		RPN::calculate();
		RPN::print();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
