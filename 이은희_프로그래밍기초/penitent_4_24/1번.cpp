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
//Q. �Լ� �����ε� + �Ű������� �Ӽ� �ο��� �����Ѱ�
//A. �Ű� ������ �Ӽ��� �ο��Ǿ ������ �ڷ������� ��޵ȴ�