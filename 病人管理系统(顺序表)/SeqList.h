/*
������˳���:)
�þ�֮ǰд��һ�飬Ȩ����ϰ��
*/
#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct patient
{
    char *_name; //����
    long long _id; //������
    char *_symptom; //֢״
}patient;

typedef patient DataType;

typedef struct SeqList
{
    DataType *_arr;
    int _size;
    int _capacity;
} SeqList;

void SeqListInit(SeqList* psl) //��ʼ��˳���
{
    assert(psl); //���ԣ���ֹpslΪ��ָ��
    psl->_arr = (DataType *)malloc(sizeof(DataType) * 10); //��ʼ��������Ϊ10
    if(psl->_arr == NULL) //��mallocʧ��
    {
        perror("malloc failed");
        return;
    }
    psl->_size = 0; //��ʼ��size
    psl->_capacity = 10; //��ʼ��capacity
}

void SeqListCheckCapacity(SeqList* psl) //���ռ�/����
{
    assert(psl); //���ԣ���ֹpslΪ��ָ��
    if(psl->_size == psl->_capacity) //˳�����������
    {
        DataType *tmp = (DataType *)realloc(psl->_arr, sizeof(DataType) * psl->_capacity * 2); //2������
        //����һ����ʱ���飬��ֹreallocʧ�ܶ�ʧ����
        if(tmp == NULL) //��reallocʧ��
        {
            perror("realloc failed");
            return;
        }
        psl->_arr = tmp; //��ʱ���鸳ֵ��˳���
        psl->_capacity *= 2; //��������
    }
}

DataType CreatePatient() //����������Ϣ
{
    DataType *d = (DataType *)malloc(sizeof(DataType));
    long long id;
    char *name = (char *)malloc(15);
    char *symptom = (char *)malloc(30);
    printf("����������: ");
    scanf("%s", name);
    printf("�����벡����: ");
    scanf("%lld", &id);
    printf("������֢״: ");
    scanf("%s", symptom);
    d->_id = id;
    d->_name = name;
    d->_symptom = symptom;
    return *d;
}

void SeqListPushBack(SeqList *psl) //��˳���β�����Ӳ�����Ϣ
{
    assert(psl); //���ԣ���ֹpslΪ��ָ��
    SeqListCheckCapacity(psl); //�������
    psl->_arr[psl->_size++] = CreatePatient(); //β������˳�����size
}

void SeqListPopBack(SeqList *psl) //��˳���β��ɾ��������Ϣ
{
    assert(psl); //���ԣ���ֹpslΪ��ָ��
    assert(psl->_size > 0); //���ԣ���ֹ˳���Ϊ�ջ�����ɾ�� 
    psl->_size--; //αɾ����
}

void SeqListPushFront(SeqList *psl) //��˳���ͷ�����Ӳ�����Ϣ
{
    assert(psl); //���ԣ���ֹpslΪ��ָ��
    SeqListCheckCapacity(psl); //�������
    for (int i = psl->_size - 1; i >= 0; i--) // �Ӻ���ǰ�ƶ�Ԫ��
    {
        psl->_arr[i + 1] = psl->_arr[i];
    }
    psl->_arr[0] = CreatePatient(); //ͷ��
    psl->_size++; //����size
}

void SeqListPopFront(SeqList *psl) //��˳���ͷ��ɾ��������Ϣ
{
    assert(psl); //���ԣ���ֹpslΪ��ָ��
    assert(psl->_size > 0); //���ԣ���ֹ˳���Ϊ�ջ�����ɾ��
    for (int i = 0; i < psl->_size - 1; i++) //��ǰ����ƶ�Ԫ��
    {
        psl->_arr[i] = psl->_arr[i + 1];
    }
    psl->_size--; //����size
}

int SeqListFind(SeqList *psl, char *name) //ͨ���������Ҳ�����Ϣ
{
    assert(psl); //���ԣ���ֹpslΪ��ָ��
    assert(name); //���ԣ���ֹnameΪ��ָ��
    for (int i = 0; i < psl->_size; i++) //����������Ϣ
    {
        if(strcmp(psl->_arr[i]._name, name) == 0) //��������
        {
            return i; //�����±�
        }
    }
    return -1; //δ�ҵ�������-1
}

void SeqListInsert(SeqList *psl, int pos) //��ָ���±���벡����Ϣ
{
    assert(psl); //���ԣ���ֹpslΪ��ָ��
    assert(pos >= 0 && pos <= psl->_size); //���pos�Ƿ�Ϸ�
    SeqListCheckCapacity(psl); //�������
    for (int i = psl->_size - 1; i >= pos; i--) //�Ӻ���ǰ�ƶ�pos �� ��������Ԫ��
    {
        psl->_arr[i + 1] = psl->_arr[i];
    }
    psl->_arr[pos] = CreatePatient(); //��posλ�ò���
    psl->_size++; //����size
}

void SeqListErase(SeqList *psl, int pos) //ɾ��ָ���±�Ĳ�����Ϣ
{
    assert(psl); //���ԣ���ֹpslΪ��ָ��
    assert(pos >= 0 && pos <= psl->_size); //���pos�Ƿ�Ϸ�
    for (int i = pos; i < psl->_size - 1; i++) //��ǰ�����ƶ�pos��������Ԫ��
    {
        psl->_arr[i] = psl->_arr[i + 1]; 
    }
    psl->_size--; //����size
}

void SeqListDestroy(SeqList *psl) //����˳���
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

void SeqListPrint(SeqList *psl) //��ӡ���в�����Ϣ
{
    assert(psl); //���ԣ���ֹpslΪ��ָ��
    for (int i = 0; i < psl->_size; i++)
    {
        printf("[����%d]����:%s, ������:%lld, ֢״:%s\n", i, psl->_arr[i]._name, psl->_arr[i]._id, psl->_arr[i]._symptom);
    }
    printf("\n");
}

int SeqListSize(SeqList *psl) //����˳����С
{
    return psl->_size;
}

int SeqListCapacity(SeqList *psl) //����˳�������
{
    return psl->_capacity;
}