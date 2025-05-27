#include <iostream>

class Cat
{
public:
    void Print()
    {
        std::cout << "林家(this):\t" << this << std::endl;
    }
};

int main()
{
    Cat myCat;
    Cat yourCat;

    myCat.Print();
    std::cout << "林家(&myCat):\t" << &myCat << std::endl;

    yourCat.Print();
    std::cout << "林家(&yourCat):\t" << &yourCat << std::endl;

    void (Cat:: * funcPtr)() = &Cat::Print;

    std::cout << "糕滚 窃荐 器牢磐 林家: " << (void*)(*(std::uintptr_t*)(&funcPtr)) << '\n';

    return 0;
}
