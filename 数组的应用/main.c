#include "Array.h"

int main()
{
    /* a, b为如下对称矩阵的压缩矩阵：
        [1,2,3]
        [2,4,5]
        [3,5,6]
    */
    printf("MatrixMul:\n");
    int a[6] = {1, 2, 4, 3, 5, 6};
    int b[6] = {1, 2, 4, 3, 5, 6};
    int ** c = MatrixMul(a, b, 3);
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1;j <= 3; j++)
        {
            printf("%d ", c[i-1][j-1]);
        }
        printf("\n");
    }

    printf("MatrixPrint:\n");
    printf("矩阵a:\n");
    MatrixPrint(a, 3);
    printf("矩阵b:\n");
    MatrixPrint(b, 3);
    return 0;
}