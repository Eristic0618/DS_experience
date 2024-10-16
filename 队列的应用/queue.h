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
    size_t head_; //��ͷλ��
    size_t size_; //����Ԫ������
    size_t cap_;  //��������
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

void QueueAppend(queue* q, DataType x) //����У��ڶ���Q�Ķ�β��������Ԫ��x��
{
    assert(q);
    if((q->head_ + q->size_ + 1) % q->cap_ == q->head_) //ѭ��������һ������������
    {
        printf("��������!\n");
        return;
    }
    q->arr_[(q->head_ + q->size_) % q->cap_] = x; //Ԫ�����
    q->size_++; //����Ԫ�ظ���
}

void QueueDelete(queue* q, DataType* d) //�����У��Ѷ���Q�Ķ�ͷԪ��ɾ�����ɲ���d���ء�
{
    assert(q);
    if(!q->size_)
    {
        printf("����Ϊ��!\n");
        return;
    }
    *d = q->arr_[q->head_]; //ȡ����ͷԪ��
    q->head_ = (q->head_ + 1) % q->cap_; // ��ͷλ�ø���
    q->size_--;
}

