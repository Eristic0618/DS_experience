#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Heap.h"

bool FindLeft(HPDataType root, int code[], DataType x, int i);

bool FindRight(HPDataType root, int code[], DataType x, int i);

HPDataType BuildHuffmanTree(DataType arr[], size_t n)
{
    Heap hp; // �ö�ʵ�����ȶ���
    HeapInit(&hp);

    HPDataType *nodes = (HPDataType *)malloc(sizeof(HPDataType) * n);
    for (int i = 0; i < n; i++) // �������е�Ԫ�ش洢���ڵ���
    {
        nodes[i] = (HPDataType)malloc(sizeof(Node));
        nodes[i]->data = arr[i];
        nodes[i]->left = nodes[i]->right = NULL;
    }

    for (int i = 0; i < n; i++)
        HeapPush(&hp, nodes[i]); // �öѶԽڵ��������

    while (HeapSize(&hp) > 1)
    {
        HPDataType left = HeapTop(&hp); // ȡ��С�ڵ���Ϊ����
        HeapPop(&hp);
        HPDataType right = HeapTop(&hp); // ȡ��С�ڵ���Ϊ�Һ���
        HeapPop(&hp);
        HPDataType root = (HPDataType)malloc(sizeof(Node));
        root->data = left->data + right->data;
        root->left = left;
        root->right = right;
        HeapPush(&hp, root); // �����ڵ�����
    }

    // ����ֻʣ��Huffman���ĸ��ڵ�
    HPDataType ret = HeapTop(&hp);
    HeapPop(&hp);

    HeapDestory(&hp);
    return ret; // ���ظ��ڵ�
}

bool FindLeft(HPDataType root, int code[], DataType x, int i)
{
    if (root == NULL)
        return false;
    if (!root->left && !root->right) //��ǰΪҶ�ӽڵ�
    {
        if (root->data == x) //�ҵ�Ŀ��ڵ�
        {
            code[i] = -1; //��Ϊ������־
            return true;
        }
        else
            return false;
    }
    if (FindLeft(root->left, code, x, i + 1)) // ���������в���
        code[i] = 0;
    else // û�ҵ�
    {
        if (FindRight(root->right, code, x, i + 1)) // ���������в���
            code[i] = 1;
        else
            return false; // ���в����ڶ�Ӧ�ڵ�
    }
    return true;
}

bool FindRight(HPDataType root, int code[], DataType x, int i)
{
    if (root == NULL)
        return false;
    if (!root->left && !root->right) //��ǰΪҶ�ӽڵ�
    {
        if (root->data == x) //�ҵ�Ŀ��ڵ�
        {
            code[i] = -1; //��Ϊ������־
            return true;
        }
        else
            return false;
    }

    if (FindLeft(root->left, code, x, i + 1)) // ���������в���
        code[i] = 0;
    else // û�ҵ�
    {
        if (FindRight(root->right, code, x, i + 1)) // ���������в���
            code[i] = 1;
        else
            return false; // ���в����ڶ�Ӧ�ڵ�
    }
    return true;
}

bool OutputEncode(HPDataType root, int code[], DataType x, int i)
{
    if (FindLeft(root->left, code, x, i + 1)) // ���������в���
        code[i] = 0;
    else // û�ҵ�
    {
        if (FindRight(root->right, code, x, i + 1)) // ���������в���
            code[i] = 1;
        else
            return false; // ���в����ڶ�Ӧ�ڵ�
    }
    return true;
}