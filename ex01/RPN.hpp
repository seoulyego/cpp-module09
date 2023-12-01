#ifndef RPN_HPP
#define RPN_HPP

#include <stack>

class RPN {
public:
  static void setExpression(char *argv[]);
  static bool isOperator(const char c);
  static void trimExpression();
  static void calculate();
  static void print();

private:
  static std::string _expression;
  static std::stack<double> _stack;

  RPN();
  RPN(const RPN &object);
  RPN &operator=(const RPN &object);
  ~RPN();
};

#endif // RPN_HPP
