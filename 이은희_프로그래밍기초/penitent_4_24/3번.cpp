#include <iostream>
using namespace std;

class Point
{
private:
	int x, y;

public:
	Point(const Point& p) { x = p.x; y = p.y; }
	int getX() { return x; }
	int getY() { return y; }
};

int main()
{
	Point p1;
	Point p2 = p1;
	cout << "x = " << p2.getX() << " y = " << p2.getY();
	
	return 0;
}

// 4.24의 이은희
// 1. 클래스 멤버 변수를 초기화 하지 않으면 어떤 값이 들어가지?
// 2. 클래스 멤버 변수는 전역,정적,지역 중 어디에 속하지?
// 3. 어? 클래스에 대해서 아는게 뭐지...?