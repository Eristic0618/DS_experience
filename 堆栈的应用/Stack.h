#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int STDataType;

typedef struct Stack
{
    STDataType *arr_;
    int size_;     // ջ��Ԫ�ظ���
    int capacity_; // ջ������С
} Stack;

void StackInit(Stack *pst) // ��ʼ��ջ
{
    assert(pst);
    pst->arr_ = NULL;
    pst->size_ = 0;
    pst->capacity_ = 0;
}

bool StackEmpty(Stack *pst) // ���ջ�Ƿ�Ϊ��
{
    assert(pst);
    return pst->size_ == 0;
}

void StackPush(Stack *pst, STDataType x) // ��ջ
{
    assert(pst);
    if (pst->size_ >= pst->capacity_) // ʣ����������
    {
        //��ջ�ռ�δ��������������Ϊ4�������������
        int NewCapacity = pst->capacity_ == 0 ? 4 : pst->capacity_ * 2;
        //����һ�����������ݺ�Ŀռ䣬��ֹ����ʧ�ܶ�ʧ����
        STDataType* tmp = (STDataType *)realloc(pst->arr_, sizeof(STDataType) * NewCapacity);
        if(tmp == NULL)
        {
            perror("realloc failed");
            exit(1);
        }
        pst->arr_ = tmp; //��������
        pst->capacity_ = NewCapacity; //��������
    }
    // ջ�ռ����
    pst->arr_[pst->size_] = x;
    pst->size_++;
}

void StackPop(Stack *pst) // ��ջ
{
    assert(pst);
    assert(!StackEmpty(pst)); //��ջ���ܳ�ջ
    pst->size_--; //αɾ����
}

STDataType StackTop(Stack *pst) // ��ȡջ��Ԫ��
{
    assert(pst);
    assert(!StackEmpty(pst)); 
    return pst->arr_[pst->size_ - 1];
}

int StackSize(Stack *pst) // ��ȡջ����ЧԪ�ظ���
{
    assert(pst);
    return pst->size_;
}

void StackDestory(Stack *pst) // ����ջ
{
    assert(pst);
    free(pst->arr_);
    pst->arr_ = NULL;
    pst->size_ = 0;
    pst->capacity_ = 0;
}