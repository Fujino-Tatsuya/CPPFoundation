#include <iostream>


int main()
{
    int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int* pArr = arr; // 1���� �迭�� ���� �ּҸ� ����Ŵ

    //���(Matrix)�� ��(row) �� ��(column) �� �̷���� 2���� �迭
    // [1, 2, 3] [4, 5, 6] [7, 8, 9] 
    // �� ������ �޸𸮿� ���������� ��ġ�ȴ�.
    int matrix[3][3] = { 0, };

    //int* p = matrix; ������ ����
   //int** pp  = matrix; ������ ����. �ؼ��� ���ϰڴٰ� �ϴ� �ſ���.

    int* p = &matrix[0][0]; // 2���� �迭�̶� �����Ϸ� �ؼ��� �޶��. / ��������� �آa
    int* p2 = *matrix; // &matrix[0][0] �� �ؼ� / �׷���
    int** pp = &p;

    std::cout << &matrix[0][0] << std::endl;
    std::cout << *matrix << std::endl; // &matrix[0][0]

    //�̰� �� �ǳİ��? CTRL+LBUTTON ���� �����ô�. <<
    std::cout << matrix << std::endl;

    int* ptrMat = &matrix[0][0];

    std::cout << "1���� �迭ó�� ��� " << std::endl;
    for (int i = 0; i < 9; i++)
    {
        if (0 == (i % 3)) std::cout << '\n';
        std::cout << ptrMat[i] << ", ";
    }

    std::cout << '\n';

    //1���� �迭�� 2���� �迭�� ���� �ؼ��� �޶���. (�����Ϸ��� �ο��� ���ƿ�...)
    std::cout << **matrix << std::endl; //matrix[0][0] �� �� 
    std::cout << *ptrMat << std::endl; //matrix[0][0] �� �� //cout�� �˾Ƽ� �ؼ� ���ش�

    // [1, 2, 3] [4, 5, 6] [7, 8, 9] �迭�� �迭�̶�� �ؼ��ؾ� �մϴ�.
    int* p00 = *matrix; // matrix[0][0] �� �ּ�
    int* p10 = *(matrix + 1); // matrix[1][0] �� �ּ�
    int* p20 = *(matrix + 2); // matrix[2][0] �� �ּ�

    std::cout << "�밡���� ���: " << '\n';
    for (int i = 0; i < 3; i++)
    {
        std::cout << p00[i] << ',';
    }

    std::cout << '\n';

    for (int i = 0; i < 3; i++)
    {
        std::cout << p10[i] << ',';
    }

    std::cout << '\n';

    for (int i = 0; i < 3; i++)
    {
        std::cout << p20[i] << ',';
    }


    std::cout << "��-�� ���" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << matrix[i][j] << ", ";
        }

        std::cout << '\n';
    }

    std::cout << "��-�� ���" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << matrix[j][i] << ", ";
        }

        std::cout << '\n';
    }



    return 0;
}