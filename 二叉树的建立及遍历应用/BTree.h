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

BTNode* CreateNewNode(BTDataType x) //创建新节点
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

BTNode* CreateBinaryTree() //创建二叉树
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

void PreOrder(BTNode* root) //二叉树前序遍历
{
	if (root == NULL)
	{
		return;
	}
	printf("%c ", root->data); //先打印根
	PreOrder(root->left); //递归左子树
	PreOrder(root->right); //递归右子树
}

void InOrder(BTNode* root) //二叉树中序遍历
{
	if (root == NULL)
	{
		return;
	}
	InOrder(root->left); //递归左子树
	printf("%c ", root->data); //打印根
	InOrder(root->right); //递归右子树
}

void PostOrder(BTNode* root) //二叉树后序遍历
{
	if (root == NULL)
	{
		return;
	}
	PostOrder(root->left); //递归左子树
	PostOrder(root->right); //递归右子树
	printf("%c ", root->data); //最后打印根
}

void LevelOrder(BTNode* root) //二叉树层序遍历(需要用到队列)
{
	Queue que;
	QueueInit(&que); //队列初始化
	if (root) //根不为空
		QueuePush(&que, root); //将根入队列
	while (!QueueEmpty(&que)) //当队列不为空时
	{
		BTNode* front = QueueFront(&que); //取出队头节点
		QueuePop(&que); //队头节点出队
		printf("%c ", front->data); //打印节点
		if (front->left != NULL) //节点的左子树不为空
			QueuePush(&que, front->left); //入队列
		if (front->right != NULL) //节点的右子树不为空
			QueuePush(&que, front->right); //入队列
	}
	QueueDestroy(&que);
}

int BTreeSize(BTNode* root) //求二叉树节点个数
{
	if (root == NULL) //空树返回0
		return 0;
	return BTreeSize(root->left) + BTreeSize(root->right) + 1; //左子树节点个数+右子树节点个数+自己=整棵树节点个数
}

int BTreeHeight(BTNode* root) //求二叉树的高度
{
	if (root == NULL) //空树返回0
		return 0;
	int leftHeight = BTreeHeight(root->left); //递归左子树求高度
	int rightHeight = BTreeHeight(root->right); //递归右子树求高度
	return leftHeight >= rightHeight ? leftHeight + 1 : rightHeight + 1; //左右子树选较高者+1=整棵树高度
}

int BTreeLevelKSize(BTNode* root, int k) //求二叉树第k层节点个数
{
	assert(k > 0); //断言，防止k非法
	if (root == NULL) //空树返回0
		return 0;
	int count = k - 1; //层数-1
	if (count == 0) //到达第k层，每个节点都返回1
		return 1;
	return BTreeLevelKSize(root->left, count) + BTreeLevelKSize(root->right, count); //左子树第k层节点个数+右子树第k层节点个数
}

int BTreeLeafSize(BTNode* root) //求二叉树叶子节点个数
{
	if (root == NULL) //空树返回0
		return 0;
	if (root->left == NULL && root->right == NULL) //左右子树都为空则为叶子节点，返回1
		return 1;
	return BTreeLeafSize(root->left) + BTreeLeafSize(root->right); //左子树叶子个数+右子树叶子个数=整棵树叶子个数
}

BTNode* BTreeFind(BTNode* root, BTDataType x) //在二叉树中查找值为x的节点
{
	if (root == NULL) //空树返回NULL
		return NULL;
	if (root->data == x) //找到，返回root
		return root;
	BTNode* left = BTreeFind(root->left, x); //在左子树中查找
	if (left) //不为空说明找到了
		return left;
	BTNode* right = BTreeFind(root->right, x); //在右子树中查找
	if (right) //不为空说明找到了
		return right;
	return NULL; //没找到，返回NULL
}

void BTreeDestroy(BTNode* root) //销毁二叉树(后序遍历，先释放左右子树最后释放根)
{
	if (root == NULL) //空树直接返回
		return;
	BTreeDestroy(root->left); //释放左子树
	BTreeDestroy(root->right); //释放右子树
	free(root); //释放根节点
}

bool BTreeComplete(BTNode* root) //判断是否为完全二叉树
{
	Queue que;
	QueueInit(&que); //初始化队列
	if (root)
		QueuePush(&que, root); //将根节点入队
	while (!QueueEmpty(&que)) //当队列不为空时
	{
		BTNode* front = QueueFront(&que); //取队头节点
		if (front == NULL) //若为空，退出循环，开始判断是否为完全二叉树
			break;
		QueuePop(&que); //队头节点出队
        //节点左右子树入队
		QueuePush(&que, front->left); 
		QueuePush(&que, front->right);
	}
	while (!QueueEmpty(&que)) 
	{
		BTNode* front = QueueFront(&que); //取队头
		QueuePop(&que); //队头出队
		if (front != NULL) //一旦出现不为空的情况，说明节点之间不连续
		{
			QueueDestroy(&que);
			return false; //返回false
		}
	}
	QueueDestroy(&que);
	return true; 
}