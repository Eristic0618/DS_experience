#include "BTree.h"

void test1()
{
	BTNode* tree = CreateBinaryTree();
    printf("ǰ�����:");
    PreOrder(tree);
	printf("\n");

    printf("�������:");
	InOrder(tree);
	printf("\n");

    printf("�������:");
	PostOrder(tree);
	printf("\n");

    printf("�������:");
	LevelOrder(tree);
	printf("\n");

	printf("�ڵ����:%d\n", BTreeSize(tree));
	printf("���ĸ߶�:%d\n", BTreeHeight(tree));
	printf("Ҷ�ӽڵ����:%d\n", BTreeLeafSize(tree));

	if (BTreeComplete(tree))
		printf("��ȫ������\n");
	else
		printf("����ȫ������\n");

	BTreeDestroy(tree);
}

int main()
{
    test1();
    return 0;
}