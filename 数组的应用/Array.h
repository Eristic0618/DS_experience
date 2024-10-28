#pragma once

#include <stdio.h>
#include <stdlib.h>

int UpExtract(int i, int j) // �������Ǿ������б�ת��Ϊѹ�������±�
{
    int k = (j * (j - 1)) / 2 + i - 1;
    return k;
}

int DownExtract(int i, int j) // �������Ǿ������б�ת��Ϊѹ�������±�
{
    int k = (i * (i - 1)) / 2 + j - 1;
    return k;
}

int **MatrixMul(int *a, int *b, int n) // ����˷�(nΪ����)
{
    int **c = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        c[i] = (int *)malloc(sizeof(int) * n);
    }
    for (int i = 1; i <= n; i++) // ���������б��1��ʼ
    {
        for (int j = 1; j <= n; j++) // ��������c��ÿһ��Ԫ��
        {
            int res = 0;
            for (int k = 1; k <= n; k++)
            {
                int x1, x2;
                if (i <= k) // ������
                    x1 = a[UpExtract(i, k)];
                else // ������
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

void MatrixPrint(int *a, int n) // ������ʽ��ӡѹ������
{
    for (int i = 1; i <= n; i++) // ���������б��1��ʼ
    {
        for (int j = 1; j <= n; j++) // ��������c��ÿһ��Ԫ��
        {
            int x;
            if (i <= j) // ������
                x = a[UpExtract(i, j)];
            else // ������
                x = a[DownExtract(i, j)];
            printf("%d ", x);
        }
        printf("\n");
    }
}
