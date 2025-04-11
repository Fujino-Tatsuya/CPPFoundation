#include <windows.h>
#include <iostream>


int main()
{
    LARGE_INTEGER start, end, frequency;
    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&start);

    Sleep(1000); // 1초 대기
    // Sleep(0) 테스트
        QueryPerformanceCounter(&end);

    double elapsedTime = (double)((end.QuadPart - start.QuadPart) * 1000.0f) / frequency.QuadPart;


    std::cout << "경과 시간: " << elapsedTime << " 밀리초" << std::endl;

    return 0;

    //정확히 1초가 아니다
    //why?
    //time slice? 남은시간을 양보?

}