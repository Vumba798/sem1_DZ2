#ifndef calculator
#define calculator

#define _USE_MATH_DEFINES
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
struct Element//элемент полученный в результате parse_string
{
	std::string data;
	int priority = 0;
	bool isNumber = false;
	bool isOpenBracket = false;
	void clear();
};

struct Calculator
{
	std::vector<Element> elements;
	std::stack<float> numbers;
	std::stack<Element> operators;

	inline void form_calculator(std::string expr)
	{
		elements = parse_expression(expr);
	}
	std::vector<Element> parse_expression(std::string expr);
	float calculate();
	void clear();
};

#endif