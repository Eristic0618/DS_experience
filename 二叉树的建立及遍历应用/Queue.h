#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct BinaryTreeNode;

typedef struct BinaryTreeNode* QDataType;

typedef struct QueueNode
{
	struct QueueNode* next;
	QDataType data;
}QNode;

typedef struct Queue
{
	QNode* phead; //指向队头
	QNode* ptail; //指向队尾
	int size; //可选，提高效率
}Queue;

bool QueueEmpty(Queue* que)//检测队列是否为空
{
	assert(que);
	return que->size == 0;
}

void QueueInit(Queue* que)//初始化队列
{
	assert(que);
	que->phead = NULL;
	que->ptail = NULL;
	que->size = 0;
}

void QueueDestroy(Queue* que)//销毁队列
{
	assert(que);
	QNode* cur = que->phead;
	while (cur)
	{
		que->phead = que->phead->next;
		free(cur);
		cur = que->phead;
	}
	que->phead = que->ptail = NULL;
	que->size = 0;
}

void QueuePush(Queue* que, QDataType x)//队尾入队列
{
	assert(que);
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		return;
	}
	newnode->data = x;
	newnode->next = NULL;
	if (que->phead == NULL || que->ptail == NULL)
	{
		assert(que->phead == NULL);
		assert(que->ptail == NULL);
		que->phead = que->ptail = newnode;
	}
	else
	{
		que->ptail->next = newnode;
		que->ptail = newnode;
	}
	que->size++;
}

void QueuePop(Queue* que)//队头出队列
{
	assert(que);
	assert(!QueueEmpty(que));
	if (que->phead->next == NULL)
	{
		free(que->phead);
		que->phead = que->ptail = NULL;
	}
	else
	{
		QNode* cur = que->phead;
		que->phead = que->phead->next;
		free(cur);
	}
	que->size--;
}

QDataType QueueFront(Queue* que)//获取队列头部元素
{
	assert(que);
	assert(!QueueEmpty(que));
	return que->phead->data;
}

QDataType QueueBack(Queue* que)//获取队列队尾元素
{
	assert(que);
	assert(!QueueEmpty(que));
	return que->ptail->data;
}

int QueueSize(Queue* que)//获取队列中有效元素个数
{
	assert(que);
	return que->size;
}

