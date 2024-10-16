#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

typedef int DataType;

typedef struct queue
{
    DataType *arr_;
    size_t head_; //队头位置
    size_t size_; //队列元素数量
    size_t cap_;  //队列容量
} queue;

void QueueInitiate(queue* q)
{
    assert(q);
    q->arr_ = (DataType *)malloc(sizeof(DataType) * 10);
    q->head_ = 0;
    q->size_ = 0;
    q->cap_ = 10;
}

bool QueueNotEmpty(queue* q)
{
    assert(q);
    return q->size_ != 0;
}

void QueueAppend(queue* q, DataType x) //入队列，在队列Q的队尾插入数据元素x。
{
    assert(q);
    if((q->head_ + q->size_ + 1) % q->cap_ == q->head_) //循环队列留一个空用来判满
    {
        printf("队列已满!\n");
        return;
    }
    q->arr_[(q->head_ + q->size_) % q->cap_] = x; //元素入队
    q->size_++; //更新元素个数
}

void QueueDelete(queue* q, DataType* d) //出队列，把队列Q的队头元素删除并由参数d带回。
{
    assert(q);
    if(!q->size_)
    {
        printf("队列为空!\n");
        return;
    }
    *d = q->arr_[q->head_]; //取出队头元素
    q->head_ = (q->head_ + 1) % q->cap_; // 队头位置更新
    q->size_--;
}

