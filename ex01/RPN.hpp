#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>

class RPN {
	public:
		static void setExpression(char *argv[]);
		static bool isOperator(const char c);
		static void trimExpression();
		static void calculate();
		static void print();
		static void printStack();

	private:
		static std::string _expression;
		static std::stack<double> _stack;

		RPN();
		RPN(const RPN& object);
		RPN& operator=(const RPN& object);
		~RPN();
};

#endif  // RPN_HPP
