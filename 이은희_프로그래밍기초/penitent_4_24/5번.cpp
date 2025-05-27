#include <iostream>

class Cat
{
public:
    void Print()
    {
        std::cout << "�ּ�(this):\t" << this << std::endl;
    }
};

int main()
{
    Cat myCat;
    Cat yourCat;

    myCat.Print();
    std::cout << "�ּ�(&myCat):\t" << &myCat << std::endl;

    yourCat.Print();
    std::cout << "�ּ�(&yourCat):\t" << &yourCat << std::endl;

    void (Cat:: * funcPtr)() = &Cat::Print;

    std::cout << "��� �Լ� ������ �ּ�: " << (void*)(*(std::uintptr_t*)(&funcPtr)) << '\n';

    return 0;
}
