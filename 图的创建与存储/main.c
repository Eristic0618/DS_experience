#include <stdio.h>
#include <string.h>
#include "Adjmatrix.h"

typedef struct Edge
{
    int a, b, w;
}Edge;

// 邻接矩阵
int main()
{
    char v[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    Edge e[9] = {{0, 2, 5}, {0, 3, 30}, {1, 0, 2}, {1, 4, 8}, {2, 1, 15}, {2, 5, 7}, {4, 3, 4}, {5, 3, 10}, {5, 4, 18}};

    Adjmatrix am;
    MatrixInit(&am, 6);
    for (int i = 0; i < 6; i++)
    {
        VertexInsert(&am, v[i] - 'A');
    }
    for (int i = 0; i < 9; i++)
    {
        EdgeInsert(&am, e[i].a, e[i].b, e[i].w);
    }
    printf("点集为:\n");
    for (int i = 0; i < 6; i++)
    {
        printf("%8c", v[i]);
    }
    printf("\n边权为:\n");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            printf("%8d", am.edge_[i][j]);
        }
        printf("\n");
    }
}

//邻接表（数组模拟）
// #define N 100

// int e[N], w[N], ne[N], h[N], idx;
 
// void add(int a, int b, int weight) // 将a指向b的边加入邻接表
// {
//     w[idx] = weight, e[idx] = b, ne[idx] = h[a], h[a] = idx++;
// }

// int main()
// {
//     char v[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
//     Edge edges[9] = {{0, 2, 5}, {0, 3, 30}, {1, 0, 2}, {1, 4, 8}, {2, 1, 15}, {2, 5, 7}, {4, 3, 4}, {5, 3, 10}, {5, 4, 18}};
//     memset(h, -1, sizeof h);
//     for (int i = 0; i < 9; i++)
//     {
//         add(edges[i].a, edges[i].b, edges[i].w);
//     }
//     printf("点集为:\n");
//     for (int i = 0; i < 6; i++)
//     {
//         printf("%8c", v[i]);
//     }
//     printf("\n边权为:\n");
//     for (int i = 0; i < 6; i++)
//     {
//         for (int x = h[i]; x != -1; x = ne[x])
//         {
//             printf("%c->%c:%d ", i + 'A', e[x] + 'A', w[x]);
//         }
//         printf("\n");
//     }
// }