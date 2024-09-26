#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int DataType;

typedef struct ListNode{
    DataType val;
    struct ListNode *next;
} ListNode;

void SListInit(ListNode** phead) //初始化链表
{
    assert(!(*phead)); //psl为空才初始化

    *phead = (ListNode *)malloc(sizeof(ListNode)); //哨兵位
    (*phead)->val = 0;
    (*phead)->next = NULL;
}   

void SListInsert(ListNode* phead, DataType x) //插入元素x同时链表保持有序
{
    assert(phead);
    ListNode *newnode = (ListNode *)malloc(sizeof(ListNode)); //创建新节点
    newnode->val = x;

    ListNode *p = phead;
    while(p->next && p->next->val < x) //遍历链表找到合适的位置
    {
        p = p->next;
    }
    //插入节点
    newnode->next = p->next;
    p->next = newnode;

    phead->val++; //节点数+1
}

int SListDelete(ListNode* phead, DataType x) //删除元素x
{
    assert(phead);
    assert(phead->next); //链表为空不能删除

    ListNode *prev = phead;
    ListNode *cur = prev->next;
    while(cur)
    {
        if(cur->val == x) //找到对应元素
        {
            prev->next = cur->next;
            free(cur);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0; //没找到
}

void Destroy(ListNode* phead) //销毁链表
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

void Print(ListNode* phead) //打印单链表(debug)
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
