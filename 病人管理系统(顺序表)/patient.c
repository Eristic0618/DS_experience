#include <stdio.h>
#include <unistd.h>
#include "SeqList.h"

int main()
{
    SeqList sl;
    SeqListInit(&sl); //��ʼ��
    for (int i = 0; i < 2; i++)
    {
        SeqListPushBack(&sl); //β������������Ϣ
    }
    SeqListPrint(&sl); //��ӡһ�鿴��Ч��

    SeqListPushFront(&sl); //ͷ��һ��������Ϣ
    SeqListPrint(&sl); //��ӡһ�鿴��Ч��

    SeqListInsert(&sl, 1); //���±�1λ�ò���һ��������Ϣ
    SeqListPrint(&sl); //��ӡһ�鿴��Ч��

    printf("˳����С:%d, ����:%d\n", SeqListSize(&sl), SeqListCapacity(&sl));

    sleep(2);
    printf("��ʼ����SeqListFind\n");
    int pos = SeqListFind(&sl, "����"); //������Ϊ�����Ĳ�����Ϣ
    if(pos == -1)
    {
        printf("����ʧ��,�ò��˲�����\n");
        return 0;
    }
    printf("���ҳɹ�!\n");

    sleep(2);
    printf("��ʼ����SeqListErase\n");
    SeqListErase(&sl, pos); //ɾ����Ϊ�����Ĳ�����Ϣ
    SeqListPrint(&sl); //��ӡһ�鿴��Ч��

    sleep(2);
    printf("��ʼ����SeqListPopBack\n");
    SeqListPopBack(&sl); //βɾ
    SeqListPrint(&sl); //��ӡһ�鿴��Ч��

    sleep(2);
    printf("��ʼ����SeqListPopFront\n");
    SeqListPopFront(&sl); //ͷɾ
    SeqListPrint(&sl); //��ӡһ�鿴��Ч��

    return 0;
}