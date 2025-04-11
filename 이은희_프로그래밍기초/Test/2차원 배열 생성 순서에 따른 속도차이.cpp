#include <iostream>
#include <chrono>

using namespace std;


int main()
{

    int rows = 1000; // 행 개수
    int cols = 1000; // 열 개수

    // 1. 포인터 배열을 할당 (행 포인터 배열)
    int** array = (int**)malloc(rows * sizeof(int*));
    if (array == NULL)
    {
        perror("Failed to allocate memory for rows");
        return EXIT_FAILURE;
    }

    // 2. 각 행의 열 메모리를 할당
    for (int i = 0; i < rows; i++)
    {
        array[i] = (int*)malloc(cols * sizeof(int));
        if (array[i] == NULL) {
            perror("Failed to allocate memory for columns");
            // 이전에 할당한 메모리 해제
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return EXIT_FAILURE;
        }
    }

    // 테스트 A
    {
        const auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                array[i][j] = i * cols + j;
            }
        }

        const chrono::duration<double> dur = chrono::steady_clock::now() - start;
        chrono::microseconds time = chrono::duration_cast<chrono::microseconds>(dur);

        cout << "연산에 소요된 시간 = " << time.count() << " : " << dur.count() << '\n';
    }


    // 테스트 B
    {
        const auto start = std::chrono::steady_clock::now();
        for (int j = 0; j < cols; j++)
        {
            for (int i = 0; i < rows; i++)
            {
                array[i][j] = i * cols + j;
            }
        }

        const chrono::duration<double> dur = chrono::steady_clock::now() - start;
        chrono::microseconds time = chrono::duration_cast<chrono::microseconds>(dur);

        cout << "연산에 소요된 시간 = " << time.count() << " : " << dur.count() << '\n';
    }

    return 0;
}
