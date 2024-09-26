#include "SList.h"

int main()
{
    ListNode *head = NULL;
    SListInit(&head);

    SListInsert(head, 1);
    Print(head);

    SListInsert(head, 8);
    Print(head);

    SListInsert(head, 5);
    Print(head);

    SListInsert(head, 12);
    Print(head);

    SListInsert(head, -3);
    Print(head);

    SListDelete(head, 5);
    Print(head);

    SListDelete(head, -3);
    Print(head);

    Destroy(head);
    return 0;
}