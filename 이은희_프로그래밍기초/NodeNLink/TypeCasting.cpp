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
        //int* pNum = num; //c에선 num 주소를 자동형변환, 포인터에다 감히 정수를 넣어?
    }

    {
        int* pNum = static_cast<int*>(&num); //명시적 캐스팅 권고??
    }

    int* pNum = (int*)num; //컴파일은 됐대...

    std::cout << "pNum: " << pNum << std::endl;

    {
        //int* pNum = reinterpret_cast<int>(num); //API 사용시 포인터 변환. void*
    }

    {
        int* pNum = reinterpret_cast<int*>(num); // ptr <-> ptr 변환만 허용
    }


    {
        int* pNum = (int*)&fNum;
    }

    {
       // int* pNum = static_cast<int*>(&fNum); // 잠재적 위험성 미리 차단
    }

    {
        int* pNum = reinterpret_cast<int*>(&fNum); // 얘는 포인터 형태인지만 검사
    }

    {
     //   int* pNum = dynamic_cast<int*>(&fNum); // dynamic_cast는 기본형은 안돼
    }
    // 컴파일 타임에 인텔리센스가 체크 해주는거임
    // static cast랑 reinterpret cast만 머릿속에 넣으셈

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
        Base* pBase = dynamic_cast<Base*>(pDerivedA); // 컴파일은 되지만 의미가 있을까? / 업캐스트에서 의미 없음
    }

    {
        DerivedB* pDerivedB = static_cast<DerivedB*>(pDerivedA);
        DerivedB* pDerivedB = dynamic_cast<DerivedB*>(pDerivedA); // nullptr / 다형 클래스 형식?
    }

    {
        // Upcasting
        Base* pBaseA = static_cast<Base*>(pDerivedA);
        Base* pBaseB = static_cast<Base*>(pDerivedB);
        // static_cast 랑 친해지셈
        // 

        // Downcasting
        DerivedA* pDerivedA = dynamic_cast<DerivedA*>(pBaseA); // 가상함수테이블이 있으면 찾아서 해줄 수 있대 RTTI
        DerivedB* pDerivedB = dynamic_cast<DerivedB*>(pBaseB);

        DerivedA* pDrivedAA = dynamic_cast<DerivedA*>(pBaseB); // nullptr
        DerivedB* pDrivedBB = static_cast<DerivedB*>(pBaseA);

        //다운캐스팅 할땐 dynamic 씀 런타임때 타입 체크 해서 // but dynamiccast는 비용이 큼
        //static_cast 는 런타임때 타입체크 안함
    }



    return 0;
}