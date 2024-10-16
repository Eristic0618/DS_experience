#include <stdio.h>
#include "queue.h"

void triangle() //�������
{
    queue q;
    QueueInitiate(&q);
    QueueAppend(&q, 1);
    printf("%d\n", 1);
    int cnt = 8;
    while(cnt--) //���ն����������Ʋ���
    {
        int size = q.size_;
        int cur = 0, next = 0;
        QueueDelete(&q, &next);
        printf("%d ", 1);
        QueueAppend(&q, 1);
        for (int i = 0; i < size-1;i++)
        {
            cur = next;
            QueueDelete(&q, &next);
            printf("%d ", cur + next);
            QueueAppend(&q, cur + next);
        }
        printf("%d\n", 1);
        QueueAppend(&q, 1);
    }
}

int main()
{
    printf("ѭ�����в���\n");
    queue q;
    QueueInitiate(&q);
    for (int i = 1; i < 10;i++)
    {
        QueueAppend(&q, i);
    }
    while(QueueNotEmpty(&q))
    {
        int a = 0;
        printf("head-%d:", q.head_);
        QueueDelete(&q, &a);
        printf("%d\n", a);
    }
    for (int i = 1; i < 6;i++)
    {
        QueueAppend(&q, i);
    }
    while(QueueNotEmpty(&q))
    {
        int a = 0;
        printf("head-%d:", q.head_);
        QueueDelete(&q, &a);
        printf("%d\n", a);
    }

    printf("\n�������\n");
    triangle();
    return 0;
}

