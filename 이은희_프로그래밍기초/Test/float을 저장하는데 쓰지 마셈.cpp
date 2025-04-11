#include <windows.h>
#include <iostream>


int main()
{
    LARGE_INTEGER start, end, frequency;
    LARGE_INTEGER oldTime, newTime;

    QueryPerformanceFrequency(&frequency);

    //float accumulateTime = 0.0f;
    //float deltaTime = 0.0f;

    double accumulateTime = 0.0f;
    double deltaTime = 0.0f;

    QueryPerformanceCounter(&start);
    oldTime = start;

    do
    {
        QueryPerformanceCounter(&newTime);

        deltaTime = (float)((newTime.QuadPart - oldTime.QuadPart) * 1000.0) / frequency.QuadPart;

        oldTime = newTime;
        accumulateTime += deltaTime;

    } while (accumulateTime < 1000.0f);


    QueryPerformanceCounter(&end);

    double elapsedTime = (double)((end.QuadPart - start.QuadPart) * 1000.0) / (double)(frequency.QuadPart);

    std::cout << "누적 시간: " << accumulateTime << " 밀리초" << std::endl;
    std::cout << "경과 시간: " << elapsedTime << " 밀리초" << std::endl;

    return 0;

}
