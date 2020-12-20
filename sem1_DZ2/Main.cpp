#define _USE_MATH_DEFINES

#include "Calculator.h"

#include <algorithm>
#include <iostream>
#include <cmath>
#include <stack>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;


int main()
{
	std::string expression;
	Calculator calc;
	int check = 1;
	do
	{
		try
		{
			check = 1;
			cout << endl << "Please, input the expression: ";
			getline(cin, expression);//считываем строку-выражение
			calc.form_calculator(expression);
			cout << "--------------------------------------------" << endl << expression << " = " << calc.calculate() << endl;
			check = 0;
		}
		catch (const char* exception)
		{
			cout << "Error: " << exception << endl;
			check = 0;
		}
		if (check == 0)
		{
			cout << "Do you want to input a new expression? 1/0 ";
			cin >> check;
			cout << "--------------------------------------------" << endl;
			calc.clear();//очистить поля калькулятора
			cin.ignore();
		}
	} while (check == 1);

	return 0;
}