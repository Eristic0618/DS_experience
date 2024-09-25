/*
完整版顺序表:)
好久之前写过一遍，权当复习了
*/
#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct patient
{
    char *_name; //姓名
    long long _id; //病历号
    char *_symptom; //症状
}patient;

typedef patient DataType;

typedef struct SeqList
{
    DataType *_arr;
    int _size;
    int _capacity;
} SeqList;

void SeqListInit(SeqList* psl) //初始化顺序表
{
    assert(psl); //断言，防止psl为空指针
    psl->_arr = (DataType *)malloc(sizeof(DataType) * 10); //初始容量设置为10
    if(psl->_arr == NULL) //若malloc失败
    {
        perror("malloc failed");
        return;
    }
    psl->_size = 0; //初始化size
    psl->_capacity = 10; //初始化capacity
}

void SeqListCheckCapacity(SeqList* psl) //检查空间/扩容
{
    assert(psl); //断言，防止psl为空指针
    if(psl->_size == psl->_capacity) //顺序表容量已满
    {
        DataType *tmp = (DataType *)realloc(psl->_arr, sizeof(DataType) * psl->_capacity * 2); //2倍扩容
        //定义一个临时数组，防止realloc失败丢失数据
        if(tmp == NULL) //若realloc失败
        {
            perror("realloc failed");
            return;
        }
        psl->_arr = tmp; //临时数组赋值给顺序表
        psl->_capacity *= 2; //更新容量
    }
}

DataType CreatePatient() //创建病人信息
{
    DataType *d = (DataType *)malloc(sizeof(DataType));
    long long id;
    char *name = (char *)malloc(15);
    char *symptom = (char *)malloc(30);
    printf("请输入姓名: ");
    scanf("%s", name);
    printf("请输入病历号: ");
    scanf("%lld", &id);
    printf("请输入症状: ");
    scanf("%s", symptom);
    d->_id = id;
    d->_name = name;
    d->_symptom = symptom;
    return *d;
}

void SeqListPushBack(SeqList *psl) //在顺序表尾部增加病人信息
{
    assert(psl); //断言，防止psl为空指针
    SeqListCheckCapacity(psl); //检查容量
    psl->_arr[psl->_size++] = CreatePatient(); //尾部插入顺便更新size
}

void SeqListPopBack(SeqList *psl) //从顺序表尾部删除病人信息
{
    assert(psl); //断言，防止psl为空指针
    assert(psl->_size > 0); //断言，防止顺序表为空还继续删除 
    psl->_size--; //伪删除法
}

void SeqListPushFront(SeqList *psl) //在顺序表头部增加病人信息
{
    assert(psl); //断言，防止psl为空指针
    SeqListCheckCapacity(psl); //检查容量
    for (int i = psl->_size - 1; i >= 0; i--) // 从后向前移动元素
    {
        psl->_arr[i + 1] = psl->_arr[i];
    }
    psl->_arr[0] = CreatePatient(); //头插
    psl->_size++; //更新size
}

void SeqListPopFront(SeqList *psl) //从顺序表头部删除病人信息
{
    assert(psl); //断言，防止psl为空指针
    assert(psl->_size > 0); //断言，防止顺序表为空还继续删除
    for (int i = 0; i < psl->_size - 1; i++) //从前向后移动元素
    {
        psl->_arr[i] = psl->_arr[i + 1];
    }
    psl->_size--; //更新size
}

int SeqListFind(SeqList *psl, char *name) //通过姓名查找病人信息
{
    assert(psl); //断言，防止psl为空指针
    assert(name); //断言，防止name为空指针
    for (int i = 0; i < psl->_size; i++) //遍历病人信息
    {
        if(strcmp(psl->_arr[i]._name, name) == 0) //姓名符合
        {
            return i; //返回下标
        }
    }
    return -1; //未找到，返回-1
}

void SeqListInsert(SeqList *psl, int pos) //在指定下标插入病人信息
{
    assert(psl); //断言，防止psl为空指针
    assert(pos >= 0 && pos <= psl->_size); //检查pos是否合法
    SeqListCheckCapacity(psl); //检查容量
    for (int i = psl->_size - 1; i >= pos; i--) //从后往前移动pos 及 后面所有元素
    {
        psl->_arr[i + 1] = psl->_arr[i];
    }
    psl->_arr[pos] = CreatePatient(); //在pos位置插入
    psl->_size++; //更新size
}

void SeqListErase(SeqList *psl, int pos) //删除指定下标的病人信息
{
    assert(psl); //断言，防止psl为空指针
    assert(pos >= 0 && pos <= psl->_size); //检查pos是否合法
    for (int i = pos; i < psl->_size - 1; i++) //从前往后移动pos后面所有元素
    {
        psl->_arr[i] = psl->_arr[i + 1]; 
    }
    psl->_size--; //更新size
}

void SeqListDestroy(SeqList *psl) //销毁顺序表
{
    assert(psl);
    for (int i = 0; i < psl->_size; i++)
    {
        free(psl->_arr[i]._name);
        free(psl->_arr[i]._symptom);
    }
    free(psl->_arr);
    psl->_size = 0;
    psl->_capacity = 0;
    free(psl);
    psl = NULL;
}

void SeqListPrint(SeqList *psl) //打印所有病人信息
{
    assert(psl); //断言，防止psl为空指针
    for (int i = 0; i < psl->_size; i++)
    {
        printf("[病人%d]姓名:%s, 病历号:%lld, 症状:%s\n", i, psl->_arr[i]._name, psl->_arr[i]._id, psl->_arr[i]._symptom);
    }
    printf("\n");
}

int SeqListSize(SeqList *psl) //返回顺序表大小
{
    return psl->_size;
}

int SeqListCapacity(SeqList *psl) //返回顺序表容量
{
    return psl->_capacity;
}