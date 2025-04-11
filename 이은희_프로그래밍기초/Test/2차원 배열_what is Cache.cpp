#include <iostream>


int main()
{
    int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int* pArr = arr; // 1차원 배열의 시작 주소를 가리킴

    //행렬(Matrix)은 행(row) 과 열(column) 로 이루어진 2차원 배열
    // [1, 2, 3] [4, 5, 6] [7, 8, 9] 
    // 이 순서로 메모리에 연속적으로 배치된다.
    int matrix[3][3] = { 0, };

    //int* p = matrix; 컴파일 에러
   //int** pp  = matrix; 컴파일 에러. 해석을 못하겠다고 하는 거에요.

    int* p = &matrix[0][0]; // 2차원 배열이라 컴파일러 해석이 달라요. / 명시적으로 해줭
    int* p2 = *matrix; // &matrix[0][0] 로 해석 / 그렇대
    int** pp = &p;

    std::cout << &matrix[0][0] << std::endl;
    std::cout << *matrix << std::endl; // &matrix[0][0]

    //이건 왜 되냐고요? CTRL+LBUTTON 따라 가봅시다. <<
    std::cout << matrix << std::endl;

    int* ptrMat = &matrix[0][0];

    std::cout << "1차원 배열처럼 출력 " << std::endl;
    for (int i = 0; i < 9; i++)
    {
        if (0 == (i % 3)) std::cout << '\n';
        std::cout << ptrMat[i] << ", ";
    }

    std::cout << '\n';

    //1차원 배열과 2차원 배열에 대한 해석이 달라짐. (컴파일러랑 싸우지 말아요...)
    std::cout << **matrix << std::endl; //matrix[0][0] 의 값 
    std::cout << *ptrMat << std::endl; //matrix[0][0] 의 값 //cout이 알아서 해석 해준대

    // [1, 2, 3] [4, 5, 6] [7, 8, 9] 배열의 배열이라고 해석해야 합니다.
    int* p00 = *matrix; // matrix[0][0] 의 주소
    int* p10 = *(matrix + 1); // matrix[1][0] 의 주소
    int* p20 = *(matrix + 2); // matrix[2][0] 의 주소

    std::cout << "노가다의 결실: " << '\n';
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


    std::cout << "행-열 출력" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << matrix[i][j] << ", ";
        }

        std::cout << '\n';
    }

    std::cout << "열-행 출력" << std::endl;
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