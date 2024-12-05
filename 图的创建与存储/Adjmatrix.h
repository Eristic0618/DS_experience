#pragma once

#include "SeqList.h"
#include <assert.h>
#include <stdlib.h>

#define MAXWEIGHT 10000
#define MAXVERTEX 100

typedef struct Adjmatrix
{
    SeqList sl_; //点集
    int edge_[MAXVERTEX][MAXVERTEX]; //边集
    int numofedge_; //边数
}Adjmatrix;

void MatrixInit(Adjmatrix* am, int n) //图的初始化
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
    SeqListInit(&(am->sl_)); //顺序表初始化
}

void VertexInsert(Adjmatrix* am, SLDataType v) //增加顶点
{
    SeqListPushBack(&(am->sl_), v); 
}

void EdgeInsert(Adjmatrix* am, int v1, int v2, int w) //增加边
{
    assert(v1 >= 0 && v1 < am->sl_.size && v2 >= 0 && v2 < am->sl_.size);
    am->edge_[v1][v2] = w;
    am->numofedge_++;
}

void EdgeErase(Adjmatrix* am, int v1, int v2) //删除边
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
            if((i == v || j == v) && am->edge_[i][j] > 0 && am->edge_[i][j] < MAXWEIGHT) //判断顶点对应的边是否存在
                am->numofedge_--; //删除边
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


