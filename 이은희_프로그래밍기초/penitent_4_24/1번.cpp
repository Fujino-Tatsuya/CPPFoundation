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
//Q. �Ű������� �Ӽ��� �ο��ȴٸ� �ٸ� �ڷ������� ��޵Ǵ°�?
//A. �Ӽ��� �ο��Ǿ ������ �ڷ������� ��޵ȴ�