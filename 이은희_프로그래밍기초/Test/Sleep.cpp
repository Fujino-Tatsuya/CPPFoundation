#include <windows.h>
#include <iostream>


int main()
{
    LARGE_INTEGER start, end, frequency;
    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&start);

    Sleep(1000); // 1�� ���
    // Sleep(0) �׽�Ʈ
        QueryPerformanceCounter(&end);

    double elapsedTime = (double)((end.QuadPart - start.QuadPart) * 1000.0f) / frequency.QuadPart;


    std::cout << "��� �ð�: " << elapsedTime << " �и���" << std::endl;

    return 0;

    //��Ȯ�� 1�ʰ� �ƴϴ�
    //why?
    //time slice? �����ð��� �纸?

}