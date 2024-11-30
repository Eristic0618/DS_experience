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
    Heap hp; // 用堆实现优先队列
    HeapInit(&hp);

    HPDataType *nodes = (HPDataType *)malloc(sizeof(HPDataType) * n);
    for (int i = 0; i < n; i++) // 将数组中的元素存储到节点中
    {
        nodes[i] = (HPDataType)malloc(sizeof(Node));
        nodes[i]->data = arr[i];
        nodes[i]->left = nodes[i]->right = NULL;
    }

    for (int i = 0; i < n; i++)
        HeapPush(&hp, nodes[i]); // 用堆对节点进行排序

    while (HeapSize(&hp) > 1)
    {
        HPDataType left = HeapTop(&hp); // 取最小节点作为左孩子
        HeapPop(&hp);
        HPDataType right = HeapTop(&hp); // 取最小节点作为右孩子
        HeapPop(&hp);
        HPDataType root = (HPDataType)malloc(sizeof(Node));
        root->data = left->data + right->data;
        root->left = left;
        root->right = right;
        HeapPush(&hp, root); // 将根节点加入堆
    }

    // 堆中只剩下Huffman树的根节点
    HPDataType ret = HeapTop(&hp);
    HeapPop(&hp);

    HeapDestory(&hp);
    return ret; // 返回根节点
}

bool FindLeft(HPDataType root, int code[], DataType x, int i)
{
    if (root == NULL)
        return false;
    if (!root->left && !root->right) //当前为叶子节点
    {
        if (root->data == x) //找到目标节点
        {
            code[i] = -1; //作为结束标志
            return true;
        }
        else
            return false;
    }
    if (FindLeft(root->left, code, x, i + 1)) // 在左子树中查找
        code[i] = 0;
    else // 没找到
    {
        if (FindRight(root->right, code, x, i + 1)) // 在右子树中查找
            code[i] = 1;
        else
            return false; // 树中不存在对应节点
    }
    return true;
}

bool FindRight(HPDataType root, int code[], DataType x, int i)
{
    if (root == NULL)
        return false;
    if (!root->left && !root->right) //当前为叶子节点
    {
        if (root->data == x) //找到目标节点
        {
            code[i] = -1; //作为结束标志
            return true;
        }
        else
            return false;
    }

    if (FindLeft(root->left, code, x, i + 1)) // 在左子树中查找
        code[i] = 0;
    else // 没找到
    {
        if (FindRight(root->right, code, x, i + 1)) // 在右子树中查找
            code[i] = 1;
        else
            return false; // 树中不存在对应节点
    }
    return true;
}

bool OutputEncode(HPDataType root, int code[], DataType x, int i)
{
    if (FindLeft(root->left, code, x, i + 1)) // 在左子树中查找
        code[i] = 0;
    else // 没找到
    {
        if (FindRight(root->right, code, x, i + 1)) // 在右子树中查找
            code[i] = 1;
        else
            return false; // 树中不存在对应节点
    }
    return true;
}