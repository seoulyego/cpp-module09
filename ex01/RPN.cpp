#include "RPN.hpp"

static double add(double a, double b) { return a + b; }

static double sub(double a, double b) { return a - b; }

static double multiple(double a, double b) { return a * b; }

static double divide(double a, double b) {
	if (b == 0)
		throw std::runtime_error("Error");
	return a / b;
}

std::string RPN::_expression;

std::stack<double> RPN::_stack;

void RPN::setExpression(char *argv[]) {
	_expression = "";
	for (size_t i = 1; argv[i] != NULL; i++) {
		if (i != 1)
			_expression += " ";
		_expression += argv[i];
	}
	trimExpression();
	if (_expression.empty())
		throw std::runtime_error("Error");
}

void RPN::trimExpression() {
	static const char *spaces = " \n\t\r\v\f";
	_expression.erase(_expression.find_last_not_of(spaces) + 1);
	_expression.erase(0,_expression.find_first_not_of(spaces));
}

bool RPN::isOperator(const char c) {
	static const std::string oper = "+-*/";
	return (oper.find_first_of(c) != oper.npos);
}

void RPN::calculate() {
	while (!_expression.empty()) {
		if (std::isdigit(_expression[0]))
			_stack.push(_expression[0] - '0');
		else if (isOperator(_expression[0])) {
			if (_stack.size() < 2)
				throw std::runtime_error("Error");

			double b = _stack.top();
			_stack.pop();
			double a = _stack.top();
			_stack.pop();

			if (_expression[0] == '+')
				_stack.push(add(a, b));
			else if (_expression[0] == '-')
				_stack.push(sub(a, b));
			else if (_expression[0] == '*')
				_stack.push(multiple(a, b));
			else
				_stack.push(divide(a, b));
		}
		else
			throw std::runtime_error("Error");
		_expression.erase(0, 1);
		trimExpression();
	}
	if (_stack.size() != 1)
		throw std::runtime_error("Error");
}

void RPN::print() {
	std::cout << _stack.top() << std::endl;
}

// void RPN::printStack() {
	// std::cout << "stack: " << _stack << std::endl;
// }
