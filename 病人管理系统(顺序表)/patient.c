#include <stdio.h>
#include <unistd.h>
#include "SeqList.h"

int main()
{
    SeqList sl;
    SeqListInit(&sl); //初始化
    for (int i = 0; i < 2; i++)
    {
        SeqListPushBack(&sl); //尾插两个病人信息
    }
    SeqListPrint(&sl); //打印一遍看看效果

    SeqListPushFront(&sl); //头插一个病人信息
    SeqListPrint(&sl); //打印一遍看看效果

    SeqListInsert(&sl, 1); //在下标1位置插入一个病人信息
    SeqListPrint(&sl); //打印一遍看看效果

    printf("顺序表大小:%d, 容量:%d\n", SeqListSize(&sl), SeqListCapacity(&sl));

    sleep(2);
    printf("开始运行SeqListFind\n");
    int pos = SeqListFind(&sl, "张三"); //查找名为张三的病人信息
    if(pos == -1)
    {
        printf("查找失败,该病人不存在\n");
        return 0;
    }
    printf("查找成功!\n");

    sleep(2);
    printf("开始运行SeqListErase\n");
    SeqListErase(&sl, pos); //删除名为张三的病人信息
    SeqListPrint(&sl); //打印一遍看看效果

    sleep(2);
    printf("开始运行SeqListPopBack\n");
    SeqListPopBack(&sl); //尾删
    SeqListPrint(&sl); //打印一遍看看效果

    sleep(2);
    printf("开始运行SeqListPopFront\n");
    SeqListPopFront(&sl); //头删
    SeqListPrint(&sl); //打印一遍看看效果

    return 0;
}