#include <stdio.h>
#include <string.h>
#include "Stack.h"

void DeToOther(int a, int n) // ʮ����תn����
{
    Stack st;
    StackInit(&st);
    int tmp = a;
    while (a) // a��Ϊ0��һֱѭ��
    {
        int i = a % n; // ������
        a /= n;
        StackPush(&st, i); // ������ջ
    }
    printf("%dת%d���ƽ��: ", tmp, n);
    while (!StackEmpty(&st))
    {
        int i = StackTop(&st);
        if (i < 10)          // ֻ��16���ƻ������ĸ
            printf("%d", i); // ������ջ
        else if (i >= 10)
            printf("%c", i + 55);
        StackPop(&st);
    }
    printf("\n");
}

bool IsMatch(const char *s)
{
    Stack st;
    StackInit(&st);
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        if (StackEmpty(&st) && (s[i] == ')' || s[i] == ']')) // ���ջΪ�գ��������������ţ���ƥ��
            return false;
        if (s[i] == '(' || s[i] == '[') // ��������ջ
            StackPush(&st, s[i]);
        // �����������ж��Ƿ�ƥ�䲢��ջ
        if ((s[i] == ')' && StackTop(&st) == '(') || (s[i] == ']' && StackTop(&st) == '['))
            StackPop(&st);
    }
    if (!StackEmpty(&st)) // �����ַ�����ϣ�ջ��Ϊ�գ�˵����ƥ��
        return false;
    else
        return true;
}

int main()
{
    // DeToOther(58, 2);
    // DeToOther(58, 8);
    // DeToOther(58, 16);
    if (IsMatch("[(1+2)*3-1]+[((1+2]*3)-1]"))
        printf("����ƥ��\n");
    else
        printf("���Ų�ƥ��\n");
    if (IsMatch("[(1+2)*3-1]+[(1+2)*3-1]"))
        printf("����ƥ��\n");
    else
        printf("���Ų�ƥ��\n");
    return 0;
}