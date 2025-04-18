#include <iostream>

struct Base
{
    void func()
    {
        std::cout << "Base::func()" << std::endl;
    }
};

struct DerivedA : public Base
{
    DerivedA(const char* derived) : _derived(derived) {}

    void func()
    {
        std::cout << "DerivedA: " << _derived << std::endl;
    }

    const char* _derived = "I am derived object";
};

struct DerivedB : public Base
{
    DerivedB(const char* derived) : _derived(derived) {}

    void func()
    {
        std::cout << "Derived: " << _derived << std::endl;
    }

    const char* _derived = "I am derived object";
};

struct SomeClass
{
    void func()
    {
        std::cout << "SomeClass::func()" << std::endl;
    }
};

int main()
{
    // primitive type casting

    int num = 1;
    float fNum = static_cast<float>(num);
    std::cout << "num: " << num << ", fNum: " << fNum << std::endl;


    {
        //int* pNum = num; //c���� num �ּҸ� �ڵ�����ȯ, �����Ϳ��� ���� ������ �־�?
    }

    {
        int* pNum = static_cast<int*>(&num); //����� ĳ���� �ǰ�??
    }

    int* pNum = (int*)num; //�������� �ƴ�...

    std::cout << "pNum: " << pNum << std::endl;

    {
        //int* pNum = reinterpret_cast<int>(num); //API ���� ������ ��ȯ. void*
    }

    {
        int* pNum = reinterpret_cast<int*>(num); // ptr <-> ptr ��ȯ�� ���
    }


    {
        int* pNum = (int*)&fNum;
    }

    {
       // int* pNum = static_cast<int*>(&fNum); // ������ ���輺 �̸� ����
    }

    {
        int* pNum = reinterpret_cast<int*>(&fNum); // ��� ������ ���������� �˻�
    }

    {
     //   int* pNum = dynamic_cast<int*>(&fNum); // dynamic_cast�� �⺻���� �ȵ�
    }
    // ������ Ÿ�ӿ� ���ڸ������� üũ ���ִ°���
    // static cast�� reinterpret cast�� �Ӹ��ӿ� ������

    // class type casting
    Base* pBase = new Base();
    DerivedA* pDerivedA = new DerivedA("DerivedA");
    DerivedB* pDerivedB = new DerivedB("DerivedB");


    {
        Base* pBase = static_cast<Base*>(pDerivedA);
        pBase->func();
    }

    {
        Base* pBase = static_cast<Base*>(pDerivedA);
        pBase->func();
    }

    {
        SomeClass* pSomeClass = static_cast<SomeClass*>(pDerivedA);
    }

    {
        Base* pBase = dynamic_cast<Base*>(pDerivedA); // �������� ������ �ǹ̰� ������? / ��ĳ��Ʈ���� �ǹ� ����
    }

    {
        DerivedB* pDerivedB = static_cast<DerivedB*>(pDerivedA);
        DerivedB* pDerivedB = dynamic_cast<DerivedB*>(pDerivedA); // nullptr / ���� Ŭ���� ����?
    }

    {
        // Upcasting
        Base* pBaseA = static_cast<Base*>(pDerivedA);
        Base* pBaseB = static_cast<Base*>(pDerivedB);
        // static_cast �� ģ������
        // 

        // Downcasting
        DerivedA* pDerivedA = dynamic_cast<DerivedA*>(pBaseA); // �����Լ����̺��� ������ ã�Ƽ� ���� �� �ִ� RTTI
        DerivedB* pDerivedB = dynamic_cast<DerivedB*>(pBaseB);

        DerivedA* pDrivedAA = dynamic_cast<DerivedA*>(pBaseB); // nullptr
        DerivedB* pDrivedBB = static_cast<DerivedB*>(pBaseA);

        //�ٿ�ĳ���� �Ҷ� dynamic �� ��Ÿ�Ӷ� Ÿ�� üũ �ؼ� // but dynamiccast�� ����� ŭ
        //static_cast �� ��Ÿ�Ӷ� Ÿ��üũ ����
    }



    return 0;
}