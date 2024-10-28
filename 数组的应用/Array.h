#pragma once

#include <stdio.h>
#include <stdlib.h>

int UpExtract(int i, int j) // 将上三角矩阵行列标转化为压缩矩阵下标
{
    int k = (j * (j - 1)) / 2 + i - 1;
    return k;
}

int DownExtract(int i, int j) // 将下三角矩阵行列标转化为压缩矩阵下标
{
    int k = (i * (i - 1)) / 2 + j - 1;
    return k;
}

int **MatrixMul(int *a, int *b, int n) // 矩阵乘法(n为阶数)
{
    int **c = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        c[i] = (int *)malloc(sizeof(int) * n);
    }
    for (int i = 1; i <= n; i++) // 矩阵中行列标从1开始
    {
        for (int j = 1; j <= n; j++) // 遍历矩阵c的每一个元素
        {
            int res = 0;
            for (int k = 1; k <= n; k++)
            {
                int x1, x2;
                if (i <= k) // 上三角
                    x1 = a[UpExtract(i, k)];
                else // 下三角
                    x1 = a[DownExtract(i, k)];
                if (k <= j)
                    x2 = b[UpExtract(k, j)];
                else
                    x2 = b[DownExtract(k, j)];
                res += x1 * x2;
            }
            c[i - 1][j - 1] = res;
        }
    }
    return c;
}

void MatrixPrint(int *a, int n) // 按矩阵方式打印压缩矩阵
{
    for (int i = 1; i <= n; i++) // 矩阵中行列标从1开始
    {
        for (int j = 1; j <= n; j++) // 遍历矩阵c的每一个元素
        {
            int x;
            if (i <= j) // 上三角
                x = a[UpExtract(i, j)];
            else // 下三角
                x = a[DownExtract(i, j)];
            printf("%d ", x);
        }
        printf("\n");
    }
}
