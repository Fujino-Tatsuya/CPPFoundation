#include <iostream>
using namespace std;

class Calculator
{
	int Add(int a, int b)
	{
		return a + b;
	}

	int Add(const int& a, const int& b)
	{
		return a + b;
	}
};

int main() 
{
	Calculator calc;

	cout << calc.Add(5, 10) << endl;

	return 0;
}
//Q. 매개변수에 속성이 부여된다면 다른 자료형으로 취급되는가?
//A. 속성이 부여되어도 동일한 자료형으로 취급된다