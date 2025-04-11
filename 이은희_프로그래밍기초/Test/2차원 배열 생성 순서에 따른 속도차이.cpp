#include <iostream>
#include <chrono>

using namespace std;


int main()
{

    int rows = 1000; // �� ����
    int cols = 1000; // �� ����

    // 1. ������ �迭�� �Ҵ� (�� ������ �迭)
    int** array = (int**)malloc(rows * sizeof(int*));
    if (array == NULL)
    {
        perror("Failed to allocate memory for rows");
        return EXIT_FAILURE;
    }

    // 2. �� ���� �� �޸𸮸� �Ҵ�
    for (int i = 0; i < rows; i++)
    {
        array[i] = (int*)malloc(cols * sizeof(int));
        if (array[i] == NULL) {
            perror("Failed to allocate memory for columns");
            // ������ �Ҵ��� �޸� ����
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return EXIT_FAILURE;
        }
    }

    // �׽�Ʈ A
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

        cout << "���꿡 �ҿ�� �ð� = " << time.count() << " : " << dur.count() << '\n';
    }


    // �׽�Ʈ B
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

        cout << "���꿡 �ҿ�� �ð� = " << time.count() << " : " << dur.count() << '\n';
    }

    return 0;
}
