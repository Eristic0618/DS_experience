#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Queue.h"

typedef char BTDataType;

typedef struct BinaryTreeNode
{
	BTDataType data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}BTNode;

BTNode* CreateNewNode(BTDataType x) //�����½ڵ�
{
	BTNode* newnode = (BTNode*)malloc(sizeof(BTNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		return NULL;
	}
	newnode->data = x;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

BTNode* CreateBinaryTree() //����������
{
	BTNode* nodeA = CreateNewNode('A');
	BTNode* nodeB = CreateNewNode('B');
	BTNode* nodeC = CreateNewNode('C');
	BTNode* nodeD = CreateNewNode('D');
	BTNode* nodeE = CreateNewNode('E');
	BTNode* nodeF = CreateNewNode('F');
	BTNode* nodeG = CreateNewNode('G');

    nodeA->left = nodeB;
    nodeA->right = nodeF;
    nodeB->left = nodeC;
    nodeC->left = nodeD;
    nodeC->right = nodeE;
    nodeF->left = nodeG;

    return nodeA;
}

void PreOrder(BTNode* root) //������ǰ�����
{
	if (root == NULL)
	{
		return;
	}
	printf("%c ", root->data); //�ȴ�ӡ��
	PreOrder(root->left); //�ݹ�������
	PreOrder(root->right); //�ݹ�������
}

void InOrder(BTNode* root) //�������������
{
	if (root == NULL)
	{
		return;
	}
	InOrder(root->left); //�ݹ�������
	printf("%c ", root->data); //��ӡ��
	InOrder(root->right); //�ݹ�������
}

void PostOrder(BTNode* root) //�������������
{
	if (root == NULL)
	{
		return;
	}
	PostOrder(root->left); //�ݹ�������
	PostOrder(root->right); //�ݹ�������
	printf("%c ", root->data); //����ӡ��
}

void LevelOrder(BTNode* root) //�������������(��Ҫ�õ�����)
{
	Queue que;
	QueueInit(&que); //���г�ʼ��
	if (root) //����Ϊ��
		QueuePush(&que, root); //���������
	while (!QueueEmpty(&que)) //�����в�Ϊ��ʱ
	{
		BTNode* front = QueueFront(&que); //ȡ����ͷ�ڵ�
		QueuePop(&que); //��ͷ�ڵ����
		printf("%c ", front->data); //��ӡ�ڵ�
		if (front->left != NULL) //�ڵ����������Ϊ��
			QueuePush(&que, front->left); //�����
		if (front->right != NULL) //�ڵ����������Ϊ��
			QueuePush(&que, front->right); //�����
	}
	QueueDestroy(&que);
}

int BTreeSize(BTNode* root) //��������ڵ����
{
	if (root == NULL) //��������0
		return 0;
	return BTreeSize(root->left) + BTreeSize(root->right) + 1; //�������ڵ����+�������ڵ����+�Լ�=�������ڵ����
}

int BTreeHeight(BTNode* root) //��������ĸ߶�
{
	if (root == NULL) //��������0
		return 0;
	int leftHeight = BTreeHeight(root->left); //�ݹ���������߶�
	int rightHeight = BTreeHeight(root->right); //�ݹ���������߶�
	return leftHeight >= rightHeight ? leftHeight + 1 : rightHeight + 1; //��������ѡ�ϸ���+1=�������߶�
}

int BTreeLevelKSize(BTNode* root, int k) //���������k��ڵ����
{
	assert(k > 0); //���ԣ���ֹk�Ƿ�
	if (root == NULL) //��������0
		return 0;
	int count = k - 1; //����-1
	if (count == 0) //�����k�㣬ÿ���ڵ㶼����1
		return 1;
	return BTreeLevelKSize(root->left, count) + BTreeLevelKSize(root->right, count); //��������k��ڵ����+��������k��ڵ����
}

int BTreeLeafSize(BTNode* root) //�������Ҷ�ӽڵ����
{
	if (root == NULL) //��������0
		return 0;
	if (root->left == NULL && root->right == NULL) //����������Ϊ����ΪҶ�ӽڵ㣬����1
		return 1;
	return BTreeLeafSize(root->left) + BTreeLeafSize(root->right); //������Ҷ�Ӹ���+������Ҷ�Ӹ���=������Ҷ�Ӹ���
}

BTNode* BTreeFind(BTNode* root, BTDataType x) //�ڶ������в���ֵΪx�Ľڵ�
{
	if (root == NULL) //��������NULL
		return NULL;
	if (root->data == x) //�ҵ�������root
		return root;
	BTNode* left = BTreeFind(root->left, x); //���������в���
	if (left) //��Ϊ��˵���ҵ���
		return left;
	BTNode* right = BTreeFind(root->right, x); //���������в���
	if (right) //��Ϊ��˵���ҵ���
		return right;
	return NULL; //û�ҵ�������NULL
}

void BTreeDestroy(BTNode* root) //���ٶ�����(������������ͷ�������������ͷŸ�)
{
	if (root == NULL) //����ֱ�ӷ���
		return;
	BTreeDestroy(root->left); //�ͷ�������
	BTreeDestroy(root->right); //�ͷ�������
	free(root); //�ͷŸ��ڵ�
}

bool BTreeComplete(BTNode* root) //�ж��Ƿ�Ϊ��ȫ������
{
	Queue que;
	QueueInit(&que); //��ʼ������
	if (root)
		QueuePush(&que, root); //�����ڵ����
	while (!QueueEmpty(&que)) //�����в�Ϊ��ʱ
	{
		BTNode* front = QueueFront(&que); //ȡ��ͷ�ڵ�
		if (front == NULL) //��Ϊ�գ��˳�ѭ������ʼ�ж��Ƿ�Ϊ��ȫ������
			break;
		QueuePop(&que); //��ͷ�ڵ����
        //�ڵ������������
		QueuePush(&que, front->left); 
		QueuePush(&que, front->right);
	}
	while (!QueueEmpty(&que)) 
	{
		BTNode* front = QueueFront(&que); //ȡ��ͷ
		QueuePop(&que); //��ͷ����
		if (front != NULL) //һ�����ֲ�Ϊ�յ������˵���ڵ�֮�䲻����
		{
			QueueDestroy(&que);
			return false; //����false
		}
	}
	QueueDestroy(&que);
	return true; 
}