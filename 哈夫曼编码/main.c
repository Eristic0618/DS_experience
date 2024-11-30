#include <stdio.h>
#include "Huffman.h"

int main()
{
    double arr[8] = {0.07, 0.19, 0.02, 0.06, 0.32, 0.03, 0.21, 0.10};
    HPDataType root = BuildHuffmanTree(arr, 8);
    int code[15];
    for (int i = 0; i < 8; i++)
    {
        if (OutputEncode(root, code, arr[i], 0))
        {
            printf("%c = ", 'a' + i);
            for (int i = 0; code[i] != -1; i++)
            {
                printf("%d", code[i]);
            }
            printf("\n");
        }
    }

    return 0;
}