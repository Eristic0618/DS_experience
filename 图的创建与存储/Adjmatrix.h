#pragma once

#include "SeqList.h"
#include <assert.h>
#include <stdlib.h>

#define MAXWEIGHT 10000
#define MAXVERTEX 100

typedef struct Adjmatrix
{
    SeqList sl_; //�㼯
    int edge_[MAXVERTEX][MAXVERTEX]; //�߼�
    int numofedge_; //����
}Adjmatrix;

void MatrixInit(Adjmatrix* am, int n) //ͼ�ĳ�ʼ��
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(i == j)
                am->edge_[i][j] = 0; 
            else
                am->edge_[i][j] = MAXWEIGHT;
        }
    }
    SeqListInit(&(am->sl_)); //˳����ʼ��
}

void VertexInsert(Adjmatrix* am, SLDataType v) //���Ӷ���
{
    SeqListPushBack(&(am->sl_), v); 
}

void EdgeInsert(Adjmatrix* am, int v1, int v2, int w) //���ӱ�
{
    assert(v1 >= 0 && v1 < am->sl_.size && v2 >= 0 && v2 < am->sl_.size);
    am->edge_[v1][v2] = w;
    am->numofedge_++;
}

void EdgeErase(Adjmatrix* am, int v1, int v2) //ɾ����
{
    assert(v1 >= 0 && v1 < am->sl_.size && v2 >= 0 && v2 < am->sl_.size);
    am->edge_[v1][v2] = MAXWEIGHT;
    am->numofedge_--;
}

void VertexErase(Adjmatrix* am, SLDataType v)
{
    assert(v >= 0 && v < am->sl_.size);

    int n = am->sl_.size;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if((i == v || j == v) && am->edge_[i][j] > 0 && am->edge_[i][j] < MAXWEIGHT) //�ж϶����Ӧ�ı��Ƿ����
                am->numofedge_--; //ɾ����
        }
    }
    for (int i = v; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            am->edge_[i][j] = am->edge_[i + 1][j]; 
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = v; j < n; j++)
        {
            am->edge_[i][j] = am->edge_[i][j + 1];
        }
    }
    int pos = SeqListFind(&(am->sl_), v);
    SeqListErase(&(am->sl_), pos);
}


