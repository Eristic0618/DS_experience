#include <stdio.h>

int Add(int n) //�ۼ�
{
    if(n == 1)
        return n;
    return n + Add(n - 1);
}

int ReBinary_Search(int* a, int l, int r, int x) //�ݹ�����
{
    int mid = l + (r - l) / 2; //���е㣨ע��߽������
    if(a[mid] == x) //�ҵ�
        return mid;
    if(l == r) //û�ҵ���l==r
        return -1;
    if(a[mid] > x) //�е�ֵ����x��x������
        return ReBinary_Search(a, l, mid, x);
    else if(a[mid] < x) //�е�ֵС����x��x���Ұ��
        return ReBinary_Search(a, mid+1, r, x);
}

int Binary_Search(int* a, int sz, int x) //ѭ�������
{
    int l = 0, r = sz - 1;
    while(l <= r)
    {
        int mid = l + (r - l) / 2;
        if(a[mid] > x)
            r = mid - 1;
        else if(a[mid] < x)
            l = mid + 1;
        else
            return mid;
    }
    return -1;
}

int Disassemble(int n) //����ֽ�ʽ����
{
    int cnt = 0;
    if(n == 1)
        return 1;
    for (int i = 2; i <= n; i++) //��������������
    {
        if(n % i == 0) //�ܹ�����
            cnt += Disassemble(n / i); //�ֽ�n
    }
    return cnt;
}

int main()
{
    int sum = Add(4);
    printf("sum = %d\n", sum);

    int arr[6] = {1, 3, 5, 7, 8, 10};
    int idx = ReBinary_Search(arr, 0, 5, 7);
    printf("flag = %d\n", idx);

    idx = Binary_Search(arr, 6, 10);
    printf("flag = %d\n", idx);

    int cnt = Disassemble(12);
    printf("cnt = %d\n", cnt);
    return 0;
}