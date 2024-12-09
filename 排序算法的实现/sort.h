#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include "Stack.h" //非递归实现快排需要栈

typedef int HPDataType;

typedef struct Heap
{
	HPDataType* arr;
	int size;
	int capacity;
}Heap;

void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//  插入排序
// （1）只有一个元素时默认有序，所以我们跳过第一个元素
// （2）取出下一个元素，在已经排好序的序列中从后向前扫描并与取出的元素对比
// （3）如果扫描到的元素大于取出的元素（升序），就将扫描的元素向后移一位
// （4）重复步骤3，直到扫描到的元素小于或等于取出的元素，将取出的元素放入有序数列
// （5）重复步骤2~5
void InsertSort(int* a, int n)
{
	for (int i = 1; i < n; i++)
	{
		int end = i - 1; //有序序列的尾部位置
		int tmp = a[i]; //取出待排序元素
		while (end >= 0) //扫描有序序列
		{
			if (tmp < a[end]) //扫描到的元素大于取出的元素
			{
				a[end + 1] = a[end]; //将其向后移一位
				end--; //从后向前扫描
			}
			else //找到合适的位置
			{
				break;
			}
		}
		a[end + 1] = tmp; //将取出的元素插入
	}
}

// 希尔排序
// 设定一个gap，并按照gap将待排序数列分割成若干子序列，对子序列分别进行插入排序
// 将gap缩小，重复步骤1，当gap=1时就是插入排序
void ShellSort(int* a, int n) 
{
	//gap > 1 预排序
	//gap = 1 直接插入排序
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (a[end] > tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
					break;
			}
			a[end + gap] = tmp;
		}
	}
}

//  选择排序
// （1）遍历未排序的部分找出最小值（升序），将其与未排序部分的第一个元素交换
// （2）重复n-1遍第一步（最后一个元素一定是最大的所以不用排了）
void SelectSort(int* a, int n) 
{
	int begin = 0, end = n - 1;
	int tmp = 0;
	while (begin < end)
	{
		int min = begin;
		int max = begin;
		for (int i = begin; i <= end; i++) //遍历寻找最大和最小值
		{
			if (a[i] > a[max])
				max = i; //保存最大值的下标
			if (a[i] < a[min])
				min = i; //保存最小值的下标
		}
		tmp = a[begin]; //将最小值交换到前面
		a[begin] = a[min];
		a[min] = tmp;
		if (max == begin) 
		{
            //最大值如果恰好在begin处，通过交换就到了min的位置，需要更新下标
			max = min;
		}
		tmp = a[end]; //将最大值交换到后面
		a[end] = a[max];
		a[max] = tmp;
		begin++; //更新头部位置
		end--; //更新尾部位置
	}
}

void AdjustDown(int* a, int n, int root) //向下调整算法
{
	int child = root * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && a[child + 1] > a[child])
		{
			child = child + 1;
		}
		if (a[child] > a[root])
		{
			HPDataType tmp = a[child];
			a[child] = a[root];
			a[root] = tmp;
			root = child;
			child = root * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//  堆排序
// （1）先建堆，升序建大堆，降序建小堆
// （2）将堆顶元素与堆尾元素互换，并排除出堆
// （3）此时堆的性质被打破，通过向下调整算法调整为新的堆，重复操作2直至序列有序
void HeapSort(int* a, int n) 
{
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i); //通过向下调整算法建堆
	}
	while (n > 1)
	{
		Swap(&a[0], &a[n - 1]); //将堆顶元素交换到堆尾
		n--; //排除原堆顶元素
		AdjustDown(a, n, 0); //调整被打乱的堆
	}
}

//  冒泡排序
// （1）从头到尾比较相邻元素，如果第一个大于第二个（升序）就将二者交换位置
// （2）重复n-1遍第一步（最后一个元素一定是最小的所以不用排了）
void BubbleSort(int* a, int n) 
{
	for (int i = 0; i < n; i++)
	{
		bool flag = false;
		for (int j = 1; j < n - i; j++)
		{
			if (a[j - 1] > a[j])
			{
				Swap(&a[j - 1], &a[j]);
				flag = true; //如果发生元素交换，flag赋值为true
			}
		}
		if (flag == false) //如果单趟冒泡后flag没有发生改变说明已经有序
			break;
	}
}

// 递归实现快速排序

// 三数取中优化
// 当快排在排序大量有序或者接近有序的序列时，选择的key容易恰好为最小值，效率比较低下，会进行一些不必要的递归。
// 当递归调用层数过深，会导致栈溢出的情况，这里我们可以使用三数取中的办法来对这种情况进行优化。
// 三数取中，就是对比待排序序列头部的值、中部的值和尾部的值，选出三者中既不是最大也不是最小的值作为key值，并放到序列头部
int GetMidIndex(int* a, int left, int right)
{
	int mid = (left + right) / 2;
	if (a[left] > a[mid])
	{
		if (a[mid] > a[right])
			return mid;
		else if (a[left] > a[right])
			return right;
		else
			return left;
	}
	else
	{
		if (a[mid] < a[right])
			return mid;
		else if (a[left] < a[right])
			return right;
		else
			return left;
	}
}

//  单趟排序hoare版本
// （1）选定待排序序列头部（或尾部）的元素作为key值，保存下标
// （2）扫描待排序序列，一个从左到右寻找比key大的值，另一个从右向左寻找比key小的值，找到后将二者交换。
// （3）当待排序序列扫描结束后，将序列头部的key与left位置处的元素交换，并返回left（此时left是key值的下标）
int PartSort1(int* a, int left, int right) 
{
    //left从待排序序列头部向后走，right从待排序序列尾部向前走
    int midi = GetMidIndex(a, left, right); //三数取中
	Swap(&a[left], &a[midi]);
	int key = left; //将待排序序列的第一个元素作为key值
	while (left < right) //left小于right说明单趟排序没结束
	{
		while (left < right && a[right] >= a[key]) //right位置的值不比key小时向前走
		{
			right--;
		}
		while (left < right && a[left] <= a[key]) //left位置的值不比key大时向后走
		{
			left++;
		}
		//此时right位置的值比key小，left位置的值比key大
		Swap(&a[left], &a[right]); //二者交换
	}
	//把序列头部作为key值的元素交换到left位置，完成单趟排序
	Swap(&a[key], &a[left]);
	return left; //返回left位置存放的key值
}

//  单轮排序挖坑法
// （1）将待排序序列头部的元素存放到一个临时变量中作为key值，将key值原先的位置作为坑位
// （2）从右往左寻找比key小的值，找到后将其填入坑中，并且其原来的位置成为新的坑
// （3）从左往右寻找比key大的值，找到后将其填入坑中，并且其原来的位置成为新的坑
// （4）重复步骤2~3直到待排序序列扫描完毕
// （5）最后将key值填入坑中，返回key值下标
int PartSort2(int* a, int left, int right) 
{
	int midi = GetMidIndex(a, left, right);
	Swap(&a[left], &a[midi]);
	int tmp = a[left];
	int hole = left;
	while (left < right)
	{
		while (left < right && a[right] >= tmp)
		{
			right--;
		}
		a[hole] = a[right];
		hole = right;
		while (left < right && a[left] <= tmp)
		{
			left++;
		}
		a[hole] = a[left];
		hole = left;
	}
	a[hole] = tmp;
	return left;
}

//  单轮排序前后指针法
// （1）prev指针指向待排序序列开头，cur指针指向prev的下一个位置，将序列头部元素作为key值
// （2）cur向后走寻找比key小的值，如果找到则prev++，并交换元素
// （3）重复步骤2直到cur走到结尾，将key值与prev位置的值交换并返回key值此时的下标
int PartSort3(int* a, int left, int right) 
{
	int midi = GetMidIndex(a, left, right);
	Swap(&a[left], &a[midi]);
	int key = left;
	int prev = left;
	int cur = left + 1;
	while (cur < right + 1)
	{
		if (a[cur] < a[key])
		{
			prev++;
			Swap(&a[cur], &a[prev]);
		}
		cur++;
	}
	Swap(&a[key], &a[prev]);
	return prev;
}

void QuickSort(int* a, int left, int right) //递归版快排
{
	if (left >= right)
		return;
	int key = PartSort2(a, left, right);
	QuickSort(a, left, key - 1);
	QuickSort(a, key + 1, right);
}

// 小区间优化版快排
// 快排在排序一个数据量为100万的无序序列时只需要递归20层，但排序一个8个数据的无序序列时就要递归3层。
// 在递归出的二叉树结构中，最底部的三层的递归次数竟然占用了全部递归次数的87.5%!
// 因此我们可以对递归实现快排的代码进行优化，当区间的数据量较小时，转为使用其他的排序算法
// 本质上是为了减少递归调用次数来提高效率
// 这里我们可以使用插入排序来排序数据量较小的区间
void QuickSort2(int* a, int left, int right) 
{
	if (left >= right)
		return;
	if (right - left + 1 < 10)
	{
		InsertSort(a + left, right - left + 1);
		return;
	}
	int key = PartSort2(a, left, right);
	QuickSort(a, left, key - 1);
	QuickSort(a, key + 1, right);
}

// 三路划分版快排
// 虽然三数取中法能解决待排序序列有序或接近有序的情况，但是如果序列中有大量的元素和key相等，甚至整个序列所有元素都相等时，三数取中也无法解决这种情况
// 这时需要使用三路划分的思想
void QuickSortThreeWay(int* a, int left, int right)
{
	if (left >= right)
		return;
	int begin = left;
	int end = right;
	int cur = begin + 1;
	int key = a[left];
	while (cur <= end)
	{
		if (a[cur] < key)
		{
			Swap(&a[cur], &a[begin]);
			cur++;
			begin++;
		}
		else if (a[cur] > key)
		{
			Swap(&a[cur], &a[end]);
			end--;
		}
		else
		{
			cur++;
		}
	}
	QuickSort(a, left, begin - 1);
	QuickSort(a, end + 1, right);
}

//  非递归实现快速排序(栈)
// （1）首先将待排序序列尾部的下标压入栈中，再将头部的下标压入栈中（因为后面出栈要先取出头部再取出尾部，栈的特性是后进先出）
// （2）取两次栈顶元素，分别取出序列头部和尾部的下标，对这一区间进行单趟排序后获取key值的下标
// （3）当key值不与原区间头部或尾部相邻时，以key值为分界将先前的区间拆分成两部分，分别压入栈中
// （4）重复步骤2~3直到栈为空
void QuickSortNonR(int* a, int left, int right)
{
	Stack st;
	StackInit(&st);
	StackPush(&st, right);
	StackPush(&st, left);
	while (!StackEmpty(&st))
	{
		int begin = StackTop(&st);
		StackPop(&st);
		int end = StackTop(&st);
		StackPop(&st);
		int keyi = PartSort2(a, begin, end);
		if (keyi + 1 < end)
		{
			StackPush(&st, end);
			StackPush(&st, keyi + 1);
		}
		if (begin < keyi - 1)
		{
			StackPush(&st, keyi - 1);
			StackPush(&st, begin);
		}
	}
}

//  递归实现归并排序
// （1）通过递归将待排序序列不断的对半分，直到分出的子序列中只有一个元素
// （2）计算出相邻两个子序列区间的边界，对二者进行归并
void _MergeSort(int* a, int begin, int end, int* tmp)
{
	if (begin == end)
		return;
	int midi = (begin + end) / 2;
	_MergeSort(a, begin, midi, tmp);
	_MergeSort(a, midi + 1, end, tmp);
	int begin1 = begin, end1 = midi;
	int begin2 = midi + 1, end2 = end;
	int i = begin;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
		{
			tmp[i++] = a[begin1++];
		}
		else
		{
			tmp[i++] = a[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		tmp[i++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[i++] = a[begin2++];
	}
	memcpy(a + begin, tmp + begin, sizeof(int) * (end - begin + 1));
}

void MergeSort(int* a, int n)
{
	int* tmp = malloc(sizeof(int) * n);
	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);
}

//  非递归实现归并排序
// （1）设定一个初始值为1的gap
// （2）通过gap来分割子序列。每次分割出两个相邻的子序列进行归并，归并好一组就将其覆盖到原序列中
// （3）重复步骤2直到第一轮归并结束
// （4）gap乘2，重复步骤2~3，直到gap超过原序列的大小
// 非递归版本中最难解决的是边界问题,当相邻的两个子序列都越界时，我们就不对它们进行归并了，放在原序列中就好.当只有第二个子序列越界时，我们对越界的序列右侧进行修正即可
void MergeSortNonR(int* a, int n)
{
	int* tmp = malloc(sizeof(int) * n);
	int gap = 1;
	while (gap < n)
	{
		for (int i = 0; i < n; i += 2 * gap)
		{
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			int j = i;
			if (end1 >= n || begin2 >= n)
			{
				break;
			}
			if (end2 >= n)
			{
				end2 = n - 1;
			}
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] < a[begin2])
				{
					tmp[j++] = a[begin1++];
				}
				else
				{
					tmp[j++] = a[begin2++];
				}
			}
			while (begin1 <= end1)
			{
				tmp[j++] = a[begin1++];
			}
			while (begin2 <= end2)
			{
				tmp[j++] = a[begin2++];
			}
			memcpy(a + i, tmp + i, sizeof(int) * (end2 - i + 1));
		}
		gap *= 2;
	}
	free(tmp);
}

//  计数排序
// （1）首先遍历待排序序列找出最大值和最小值，算出序列元素的范围大小
// （2）按照算出的范围开辟一块空间，用来存放统计出的元素个数
// 因为序列中元素的范围不一定从0开始，如果使用绝对映射（以元素的真实数值作为下标）就会浪费大量空间。当我们找出最大值和最小值后，将元素减去最小值就是它的相对位置
// （3）遍历待排序序列，对每种元素出现的次数进行统计
// （4）根据统计的结果，按照顺序放入原序列
void CountSort(int* a, int n) 
{
	int max = a[0], min = a[0];
	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
		if (a[i] < min)
		{
			min = a[i];
		}
	}
	int range = max - min + 1;
	int* tmp = (int*)malloc(sizeof(int) * range);
	memset(tmp, 0, sizeof(int) * range);
	for (int i = 0; i < n; i++)
	{
		tmp[a[i] - min]++;
	}
	int k = 0;
	for (int i = 0; i < range; i++)
	{
		while (tmp[i]--)
		{
			a[k++] = i + min;
		}
	}
}