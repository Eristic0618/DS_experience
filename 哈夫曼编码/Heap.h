#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

typedef double DataType;

typedef struct Node
{
    DataType data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Node* HPDataType;

typedef struct Heap
{
	HPDataType* arr;
	int size;
	int capacity;
}Heap;

void HeapInit(Heap* hp)//初始化堆
{
	assert(hp);
	hp->arr = NULL;
	hp->size = 0;
	hp->capacity = 0;
}

void HeapDestory(Heap* hp)//销毁堆
{
	assert(hp);
	free(hp->arr);
	hp->arr = NULL;
	hp->size = hp->capacity = 0;
}

int HeapSize(Heap* hp)//堆的有效数据个数
{
	assert(hp);
	return hp->size;
}

bool HeapEmpty(Heap* hp)//堆的判空
{
	assert(hp);
	return hp->size == 0;
}

void AdjustUp(HPDataType* arr, int child)//向上调整（小堆）
{
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if ((arr[child])->data < (arr[parent])->data)
		{
			HPDataType tmp = arr[parent];
			arr[parent] = arr[child];
			arr[child] = tmp;
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

void AdjustDown(HPDataType* arr, int size, int parent)//向下调整（小堆）
{
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size && (arr[child + 1])->data < (arr[child])->data)
		{
			child = child + 1;
		}
		if ((arr[child])->data < (arr[parent])->data)
		{
			HPDataType tmp = arr[child];
			arr[child] = arr[parent];
			arr[parent] = tmp;
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapPush(Heap* hp, HPDataType x)//插入数据
{
	assert(hp);
	if (hp->size == hp->capacity)
	{
		int newcapacity = hp->capacity == 0 ? 4 : hp->capacity * 2;
		HPDataType* tmp = (HPDataType*)realloc(hp->arr, sizeof(HPDataType) * newcapacity);
		if (tmp == NULL)
		{
			perror("realloc fail");
			return;
		}
		hp->arr = tmp;
		hp->capacity = newcapacity;
	}
	hp->arr[hp->size] = x;
	hp->size++;
	AdjustUp(hp->arr, hp->size - 1);
}

void HeapPop(Heap* hp)//删除数据（堆顶）（首尾数据交换，尾删，再调堆）
{
	assert(hp);
	assert(!HeapEmpty(hp));
	HPDataType tmp = hp->arr[hp->size - 1];
	hp->arr[hp->size - 1] = hp->arr[0];
	hp->arr[0] = tmp;
	hp->size--;
	AdjustDown(hp->arr, hp->size, 0);
}

HPDataType HeapTop(Heap* hp)//获取堆顶数据
{
	assert(hp);
	assert(!HeapEmpty(hp));
	return hp->arr[0];
}