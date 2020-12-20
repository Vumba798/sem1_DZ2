#include "Calculator.h"

#define _USE_MATH_DEFINES
#include <algorithm>


#include <cmath>
#include <iostream>
#include <stack>
#include <string>

using std::endl;
using std::cin;
using std::cout;

void Calculator::clear()
{
	elements.clear();
	while (!numbers.empty())
	{
		numbers.pop();
	}
	while (!operators.empty())
	{
		operators.pop();
	}
}

void Element::clear()//�������� ��������
{
	priority = 0;
	isNumber = false;
	data.clear();
}

float convert_operator(float a, float b, Element oper)//��������� �������� � ����� � ������� ���������
{
	float c;
	if (oper.data == "+")
	{
		c = a + b;
	}
	else if (oper.data == "-")
	{
		c = a - b;
	}
	else if (oper.data == "*")
	{
		c = a * b;
	}
	else if (oper.data == "/")
	{
		c = a / b;
	}
	else if (oper.data == "^")
	{
		c = pow(a, b);
	}
	return c;
}

std::vector<Element> Calculator::parse_expression(std::string expr)//������������� ��������� ���������
{
	expr.erase(std::remove_if(expr.begin(), expr.end(), std::isspace), expr.end());//������� ��� ���� ��������
	std::vector<Element> parsedExpr;
	Element element;
	size_t i = 0;
	std::stack<char> brackets;
	bool variableFlag = false;
	bool numberFlag = false;//�������� �� ���� ������ ������������ �����
	bool dot = false;
	float x;
	try
	{

		while (i < expr.length())
		{
			if ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.')//���� ������ - �����, �� ������ ���������
			{

				if (expr[i] == '.' && dot == true)
				{
					dot = false;
					throw "doble dot";
				}
				if (expr[i] == '.')
				{
					dot = true;
				}
				numberFlag = true;
				element.data.push_back(expr[i]);
				element.isNumber = true;
				i++;
				if (i >= expr.length())
				{
					parsedExpr.push_back(element);
					element.clear();
				}
				continue;
			}
			else if (numberFlag == true)
			{
				dot = false;
				parsedExpr.push_back(element);
				element.clear();//������� ���������
				numberFlag = false;
			}

			if (expr[i] == 'x' || expr[i] == 'X')//�������� �� ����������
			{
				if (i + 1 >= expr.length())
				{
					if (variableFlag == false)
					{
						cout << "Please, input the value of x: ";
						cin >> x;
					}
					variableFlag = true;
					element.data = std::to_string(x);
					element.isNumber = true;
					parsedExpr.push_back(element);
					element.clear();
					i++;
				}
				else if (expr[i + 1] == '^' || expr[i + 1] == '+' || expr[i + 1] == '-' || expr[i + 1] == '*' || expr[i + 1] == '/')
				{
					if (variableFlag == false)
					{
						cout << "Please, input the value of x: ";
						cin >> x;
					}
					variableFlag = true;
					element.data = std::to_string(x);
					element.isNumber = true;
					parsedExpr.push_back(element);
					element.clear();
					i++;
				}
				else
				{
					throw "unable to recognize an element";//���� � ��� ��� � ��������� ��� ���� ������
				}
				continue;
			}

			if (expr[i] == 'p' || expr[i] == 'P')//�������� �� ��������� pi
			{

				if (i + 1 < expr.length())
				{
					if (expr[i + 1] == 'i' || expr[i] == 'I')
					{
						if (i + 2 >= expr.length())//�������� ������� ����� pi
						{
							element.data = std::to_string(M_PI);
							element.isNumber = true;
							parsedExpr.push_back(element);
							element.clear();
							i += 2;
							continue;
						}
						else if (expr[i + 2] == '^' || expr[i + 2] == '+' || expr[i + 2] == '-' || expr[i + 2] == '*' || expr[i + 2] == '/' || expr[i + 2] == ')')
						{
							element.data = std::to_string(M_PI);
							element.isNumber = true;
							parsedExpr.push_back(element);
							element.clear();
							i += 2;
							continue;
						}
					}
					else
					{
						throw "unknown symbol";
					}
				}
				else if (i + 1 > expr.length())
				{
					throw "unable to recognize an element";
				}
			}



			else if (expr[i] == 'e')//�������� ��������� e
			{
				if (i + 1 > expr.length())//�������� ������� ����� e
				{
					element.data = std::to_string(M_E);
					element.isNumber = true;
					parsedExpr.push_back(element);
					element.clear();
					i++;
					continue;
				}
				else if (expr[i + 1] == '^' || expr[i + 1] == '+' || expr[i + 1] == '-' || expr[i + 1] == '*' || expr[i + 1] == '/')
				{
					element.data = std::to_string(M_E);
					element.isNumber = true;
					parsedExpr.push_back(element);
					element.clear();
					i += 1;
					continue;
				}
			}


			else if ((expr[i] == 's') && (i + 3 < expr.length()))//�������� sin(
			{
				if ((expr[i + 1] == 'i') && (expr[i + 2] == 'n') && (expr[i + 3] == '('))
				{
					element.data = "sin(";
					element.isOpenBracket = true;
					element.priority = 0;
					brackets.push('(');
					parsedExpr.push_back(element);
					element.clear();
					i += 4;
					continue;
				}
			}

			if ((expr[i] == 'c') && (i + 3 < expr.length()))//�������� �� cos(
			{
				if ((expr[i + 1] == 'o') && (expr[i + 2] == 's') && (expr[i + 3] == '('))
				{
					element.data = "cos(";
					element.isOpenBracket = true;
					element.priority = 0;
					brackets.push('(');
					parsedExpr.push_back(element);
					element.clear();
					i += 4;
					continue;
				}
			}
			if ((expr[i] == 'c') && (i + 3 < expr.length()))//�������� �� �tg(
			{
				if ((expr[i + 1] == 't') && (expr[i + 2] == 'g') && (expr[i + 3] == '('))
				{
					element.data = "ctg(";
					element.isOpenBracket = true;
					element.priority = 0;
					brackets.push('(');
					parsedExpr.push_back(element);
					element.clear();
					i += 4;
					continue;
				}
			}

			if ((expr[i] == 't') && (i + 2 < expr.length()))//�������� �� tg(
			{
				if ((expr[i + 1] == 'g') && (expr[i + 2] == '('))
				{
					element.data = "tg(";
					element.isOpenBracket = true;
					element.priority = 0;
					brackets.push('(');
					parsedExpr.push_back(element);
					element.clear();
					i += 3;
					continue;
				}
			}

			if ((expr[i] == 'e') && (i + 3 < expr.length()))//�������� �� exp(
			{
				if ((expr[i + 1] == 'x') && (expr[i + 2] == 'p') && (expr[i + 3] == '('))
				{
					element.data = "exp(";
					element.isOpenBracket = true;
					element.priority = 0;
					brackets.push('(');
					parsedExpr.push_back(element);
					element.clear();
					i += 4;
					continue;
				}
			}
			if ((expr[i] == 's') && (i + 4 < expr.length()))//�������� �� sqrt(
			{
				if ((expr[i + 1] == 'q') && (expr[i + 2] == 'r') && (expr[i + 3] == 't') && (expr[i + 4] == '('))
				{
					element.data = "sqrt(";
					element.isOpenBracket = true;
					element.priority = 0;
					brackets.push('(');
					parsedExpr.push_back(element);
					element.clear();
					i += 5;
					continue;
				}
			}
			if (expr[i] == '+')
			{
				if (i > 0)
				{
					if (expr[i - 1] == '(')
					{
						/*element.data = "+";
						element.isNumber = true;
						numberFlag = true;*/
						i += 1;
						continue;
					}
					else
					{
						element.data = "+";
						element.priority = 2;
						element.isOpenBracket = false;
						parsedExpr.push_back(element);
						element.clear();
						i++;
						continue;
					}
				}
				else
				{
					/*element.data = "+";
					element.isNumber = true;
					numberFlag = true;*/
					i += 1;
					continue;
				}
			}
			if (expr[i] == '-')
			{
				if (i > 0)
				{
					if (expr[i - 1] == '(')
					{
						element.data = "-";
						element.isNumber = true;
						numberFlag = true;
						i += 1;
						continue;
					}
					else
					{
						element.data = "-";
						element.priority = 2;
						element.isOpenBracket = false;
						parsedExpr.push_back(element);
						element.clear();
						i++;
						continue;
					}
				}
				else
				{
					element.data = "-";
					element.isNumber = true;
					numberFlag = true;
					i += 1;
					continue;
				}
			}
			else if ((expr[i] == '^' || expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/')
				&& (i - 1 >= 0) && (i + 1 <= expr.length()))//�������� �� ��������
			{
				element.data = expr[i];
				element.isOpenBracket = false;
				switch (expr[i])//����������� ��������� ���������
				{
				case '+':
					element.priority = 2;
					break;
				case '-':
					element.priority = 2;
					break;
				case '*':
					element.priority = 3;
					break;
				case '/':
					element.priority = 3;
					break;
				case '^':
					element.priority = 4;
					break;
				}
				parsedExpr.push_back(element);
				element.clear();
				i += 1;
				continue;
			}
			else if (expr[i] == '(')
			{
				element.data = "(";
				element.isOpenBracket = true;
				element.priority = 0;
				brackets.push('(');
				parsedExpr.push_back(element);
				element.clear();
				i++;
				continue;
			}
			else if (expr[i] == ')')
			{
				if (brackets.size() == 0)//���� ������ - ������ �������
				{
					throw "')'";
				}
				else if (brackets.top() != '(')//���� �� ���������� ������� ������ 
				{
					throw "')'";
				}
				else
				{
					brackets.pop();
				}
				element.data = ")";
				element.priority = -1;
				parsedExpr.push_back(element);
				element.clear();
				i++;
				continue;
			}
			else
			{
				throw "unknown symbol";
			}

		}
		if (brackets.size() != 0)
		{
			throw "brackets";
		}

	}
	catch (const char* exception)
	{
		throw exception;//������ ���������� ������
	}

	return parsedExpr;
}

float Calculator::calculate()
{
	try
	{
		Element tmpOperator;
		float tmpNumber;
		for (size_t i = 0; i < elements.size(); i++)
		{
			if (elements[i].isNumber == true) // ���� ������� - �����
			{
				numbers.push(std::stof(elements[i].data));
			}
			else
			{
				if (i + 1 < elements.size())
				{
					if (elements[i].data != ")" && elements[i + 1].isNumber == false && elements[i + 1].isOpenBracket == false)
					{
						throw "you forgot few numbers";
					}
				}

				if (elements[i].priority == 0)
				{
					operators.push(elements[i]);
				}
				else if (operators.size() > 0)
				{
					//������ � ����, ���� ��������� �������� ���� ���������� ��� ����� � ����������� ������
					if (elements[i].priority > operators.top().priority)
					{
						operators.push(elements[i]);
					}
					else if (elements[i].data == ")")//���� �� ����� ������������� ������, ��������� ���������, ���� �� �������� �������������
					{
						if (numbers.size() == 0)
						{
							throw "empty operator";
						}
						while (operators.top().isOpenBracket != true)
						{
							tmpNumber = numbers.top();
							numbers.pop();
							numbers.top() = convert_operator(numbers.top(), tmpNumber, operators.top());
							operators.pop();
						}
						if (operators.top().data == "sin(")//���������� ������
						{
							numbers.top() = sin(numbers.top());
						}
						if (operators.top().data == "cos(")//���������� ��������
						{
							numbers.top() = cos(numbers.top());
						}
						if (operators.top().data == "tg(")//���������� ��������
						{
							numbers.top() = tan(numbers.top());
						}
						if (operators.top().data == "ctg(")//���������� ����������
						{
							numbers.top() = 1 / tan(numbers.top());
						}
						if (operators.top().data == "exp(")//���������� e^x
						{
							numbers.top() = exp(numbers.top());
						}
						if (operators.top().data == "sqrt(")//���������� �����
						{
							if (numbers.top() < 0)
							{
								throw "you can't sqrt the value < 0";
							}
							numbers.top() = sqrt(numbers.top());
						}
						operators.pop();
					}
					else
					{

						//��������� ���������, ���� ��������� �������� ��������� ���� ����������
						while ((elements[i].priority <= operators.top().priority))
						{
							tmpNumber = numbers.top();
							numbers.pop();
							numbers.top() = convert_operator(numbers.top(), tmpNumber, operators.top());
							operators.pop();
							if (operators.size() == 0)
							{
								break;
							}
						}
						operators.push(elements[i]);
					}
				}
				else
				{
					operators.push(elements[i]);
				}
			}
		}
		while (operators.size() != 0)//��������� ���������� ��������� � �����
		{
			if (numbers.size() < 2)
			{
				throw "err";
			}
			tmpNumber = numbers.top();
			numbers.pop();
			numbers.top() = convert_operator(numbers.top(), tmpNumber, operators.top());
			operators.pop();
		}
		if (numbers.size() != 1)
		{
			throw "stack with numbers is not empty, maybe you forgot an operand";
		}
	}
	catch (const char* exception)
	{
		throw exception;

	}
	return numbers.top();
}