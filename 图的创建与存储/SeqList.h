#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLDataType;

typedef struct SeqList
{
    SLDataType* a;
    size_t size;
    size_t capicity;
} SeqList;

void SeqListDestory(SeqList* psl)
{
    assert(psl);
    free(psl->a);
    psl->a = NULL;
    psl->capicity = 0;
    psl->size = 0;
}

void SeqListPrint(SeqList* psl)
{
    assert(psl);
    for (size_t i = 0; i < psl->size; i++)
    {
        printf("%d ", psl->a[i]);
    }
    printf("\n");
}

void SeqListInit(SeqList* psl)
{
    assert(psl);
    psl->a = (SLDataType*)malloc(sizeof(SLDataType) * 4);
    if (psl->a == NULL)
    {
        perror("malloc fail");
        return;
    }
    psl->size = 0;
    psl->capicity = 4;
}

void CheckCapacity(SeqList* psl)
{
    assert(psl);
    if (psl->size == psl->capicity)
    {
        SLDataType* tmp = (SLDataType*)realloc(psl->a, sizeof(SLDataType) * psl->capicity * 2);
        if (tmp == NULL)
        {
            perror("realloc fail");
            return;
        }
        psl->a = tmp;
        psl->capicity *= 2;
    }
}

void SeqListPushBack(SeqList* psl, SLDataType x)
{
    assert(psl);
    CheckCapacity(psl);
    psl->a[psl->size++] = x;
}

void SeqListPopBack(SeqList* psl)
{
    assert(psl);
    assert(psl->size > 0);
    psl->size--;
}

void SeqListPushFront(SeqList* psl, SLDataType x)
{
    assert(psl);
    CheckCapacity(psl);
    for (int end = psl->size - 1; end >= 0; end--)
    {
        psl->a[end + 1] = psl->a[end];
    }
    psl->a[0] = x;
    psl->size++;
}

void SeqListPopFront(SeqList* psl)
{
    assert(psl);
    assert(psl->size > 0);
    for (int i = 0; i < psl->size - 1; i++)
    {
        psl->a[i] = psl->a[i + 1];  
    }
    psl->size--;
}

int SeqListFind(SeqList* psl, SLDataType x)
{
    assert(psl);
    for (int i = 0; i < psl->size; i++)
    {
        if (psl->a[i] == x)
        {
            return i;
        }
    }
    return -1;
}

void SeqListInsert(SeqList* psl, size_t pos, SLDataType x) 
{
    assert(psl);
    assert(0 <= pos && pos <= psl->size);
    CheckCapacity(psl);
    for (int end = psl->size - 1; end >= pos; end--)
    {
        psl->a[end + 1] = psl->a[end];
    }
    psl->a[pos] = x;
    psl->size++;
}

void SeqListErase(SeqList* psl, size_t pos)
{
    assert(psl);
    assert(0 <= pos && pos < psl->size);
    while (pos < psl->size - 1)
    {
        psl->a[pos] = psl->a[pos + 1];
        pos++;
    }
    psl->size--;
}
