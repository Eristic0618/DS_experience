#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int STDataType;

typedef struct Stack
{
    STDataType *arr_;
    int size_;     // 栈内元素个数
    int capacity_; // 栈容量大小
} Stack;

void StackInit(Stack *pst) // 初始化栈
{
    assert(pst);
    pst->arr_ = NULL;
    pst->size_ = 0;
    pst->capacity_ = 0;
}

bool StackEmpty(Stack *pst) // 检测栈是否为空
{
    assert(pst);
    return pst->size_ == 0;
}

void StackPush(Stack *pst, STDataType x) // 入栈
{
    assert(pst);
    if (pst->size_ >= pst->capacity_) // 剩余容量不足
    {
        //若栈空间未开辟则容量设置为4，否则二倍扩容
        int NewCapacity = pst->capacity_ == 0 ? 4 : pst->capacity_ * 2;
        //用另一个数组存放扩容后的空间，防止扩容失败丢失数据
        STDataType* tmp = (STDataType *)realloc(pst->arr_, sizeof(STDataType) * NewCapacity);
        if(tmp == NULL)
        {
            perror("realloc failed");
            exit(1);
        }
        pst->arr_ = tmp; //更换数组
        pst->capacity_ = NewCapacity; //更新容量
    }
    // 栈空间充足
    pst->arr_[pst->size_] = x;
    pst->size_++;
}

void StackPop(Stack *pst) // 出栈
{
    assert(pst);
    assert(!StackEmpty(pst)); //空栈不能出栈
    pst->size_--; //伪删除法
}

STDataType StackTop(Stack *pst) // 获取栈顶元素
{
    assert(pst);
    assert(!StackEmpty(pst)); 
    return pst->arr_[pst->size_ - 1];
}

int StackSize(Stack *pst) // 获取栈中有效元素个数
{
    assert(pst);
    return pst->size_;
}

void StackDestory(Stack *pst) // 销毁栈
{
    assert(pst);
    free(pst->arr_);
    pst->arr_ = NULL;
    pst->size_ = 0;
    pst->capacity_ = 0;
}