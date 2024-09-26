#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int DataType;

typedef struct ListNode{
    DataType val;
    struct ListNode *next;
} ListNode;

void SListInit(ListNode** phead) //��ʼ������
{
    assert(!(*phead)); //pslΪ�ղų�ʼ��

    *phead = (ListNode *)malloc(sizeof(ListNode)); //�ڱ�λ
    (*phead)->val = 0;
    (*phead)->next = NULL;
}   

void SListInsert(ListNode* phead, DataType x) //����Ԫ��xͬʱ����������
{
    assert(phead);
    ListNode *newnode = (ListNode *)malloc(sizeof(ListNode)); //�����½ڵ�
    newnode->val = x;

    ListNode *p = phead;
    while(p->next && p->next->val < x) //���������ҵ����ʵ�λ��
    {
        p = p->next;
    }
    //����ڵ�
    newnode->next = p->next;
    p->next = newnode;

    phead->val++; //�ڵ���+1
}

int SListDelete(ListNode* phead, DataType x) //ɾ��Ԫ��x
{
    assert(phead);
    assert(phead->next); //����Ϊ�ղ���ɾ��

    ListNode *prev = phead;
    ListNode *cur = prev->next;
    while(cur)
    {
        if(cur->val == x) //�ҵ���ӦԪ��
        {
            prev->next = cur->next;
            free(cur);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0; //û�ҵ�
}

void Destroy(ListNode* phead) //��������
{
    assert(phead);

    ListNode *p = phead;
    while(p)
    {
        ListNode *tmp = p;
        p = p->next;
        free(tmp);
    }
}

void Print(ListNode* phead) //��ӡ������(debug)
{
    assert(phead);

    ListNode *p = phead->next;
    while(p)
    {
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
}
