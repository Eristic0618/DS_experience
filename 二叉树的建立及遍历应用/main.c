#include "BTree.h"

void test1()
{
	BTNode* tree = CreateBinaryTree();
    printf("前序遍历:");
    PreOrder(tree);
	printf("\n");

    printf("中序遍历:");
	InOrder(tree);
	printf("\n");

    printf("后序遍历:");
	PostOrder(tree);
	printf("\n");

    printf("层序遍历:");
	LevelOrder(tree);
	printf("\n");

	printf("节点个数:%d\n", BTreeSize(tree));
	printf("树的高度:%d\n", BTreeHeight(tree));
	printf("叶子节点个数:%d\n", BTreeLeafSize(tree));

	if (BTreeComplete(tree))
		printf("完全二叉树\n");
	else
		printf("非完全二叉树\n");

	BTreeDestroy(tree);
}

int main()
{
    test1();
    return 0;
}