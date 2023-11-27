#include "RPN.hpp"

// static void i_wanna_go_home() {
	// system("leaks $PPID");
// }

int main(int argc, char *argv[]) {
	// atexit(i_wanna_go_home);
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
