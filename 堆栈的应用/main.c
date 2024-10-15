#include <stdio.h>
#include <string.h>
#include "Stack.h"

void DeToOther(int a, int n) // 十进制转n进制
{
    Stack st;
    StackInit(&st);
    int tmp = a;
    while (a) // a不为0则一直循环
    {
        int i = a % n; // 求余数
        a /= n;
        StackPush(&st, i); // 余数入栈
    }
    printf("%d转%d进制结果: ", tmp, n);
    while (!StackEmpty(&st))
    {
        int i = StackTop(&st);
        if (i < 10)          // 只有16进制会出现字母
            printf("%d", i); // 余数出栈
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
        if (StackEmpty(&st) && (s[i] == ')' || s[i] == ']')) // 如果栈为空，但遇到了右括号，则不匹配
            return false;
        if (s[i] == '(' || s[i] == '[') // 左括号入栈
            StackPush(&st, s[i]);
        // 遇到右括号判断是否匹配并出栈
        if ((s[i] == ')' && StackTop(&st) == '(') || (s[i] == ']' && StackTop(&st) == '['))
            StackPop(&st);
    }
    if (!StackEmpty(&st)) // 遍历字符串完毕，栈不为空，说明不匹配
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
        printf("括号匹配\n");
    else
        printf("括号不匹配\n");
    if (IsMatch("[(1+2)*3-1]+[(1+2)*3-1]"))
        printf("括号匹配\n");
    else
        printf("括号不匹配\n");
    return 0;
}