#include <stdio.h>

int Add(int n) //累加
{
    if(n == 1)
        return n;
    return n + Add(n - 1);
}

int ReBinary_Search(int* a, int l, int r, int x) //递归版二分
{
    int mid = l + (r - l) / 2; //找中点（注意边界情况）
    if(a[mid] == x) //找到
        return mid;
    if(l == r) //没找到且l==r
        return -1;
    if(a[mid] > x) //中点值大于x：x在左半侧
        return ReBinary_Search(a, l, mid, x);
    else if(a[mid] < x) //中点值小于于x：x在右半侧
        return ReBinary_Search(a, mid+1, r, x);
}

int Binary_Search(int* a, int sz, int x) //循环版二分
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

int Disassemble(int n) //计算分解式数量
{
    int cnt = 0;
    if(n == 1)
        return 1;
    for (int i = 2; i <= n; i++) //遍历区间所有数
    {
        if(n % i == 0) //能够整除
            cnt += Disassemble(n / i); //分解n
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