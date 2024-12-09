#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include "Stack.h" //�ǵݹ�ʵ�ֿ�����Ҫջ

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

//  ��������
// ��1��ֻ��һ��Ԫ��ʱĬ��������������������һ��Ԫ��
// ��2��ȡ����һ��Ԫ�أ����Ѿ��ź���������дӺ���ǰɨ�貢��ȡ����Ԫ�ضԱ�
// ��3�����ɨ�赽��Ԫ�ش���ȡ����Ԫ�أ����򣩣��ͽ�ɨ���Ԫ�������һλ
// ��4���ظ�����3��ֱ��ɨ�赽��Ԫ��С�ڻ����ȡ����Ԫ�أ���ȡ����Ԫ�ط�����������
// ��5���ظ�����2~5
void InsertSort(int* a, int n)
{
	for (int i = 1; i < n; i++)
	{
		int end = i - 1; //�������е�β��λ��
		int tmp = a[i]; //ȡ��������Ԫ��
		while (end >= 0) //ɨ����������
		{
			if (tmp < a[end]) //ɨ�赽��Ԫ�ش���ȡ����Ԫ��
			{
				a[end + 1] = a[end]; //���������һλ
				end--; //�Ӻ���ǰɨ��
			}
			else //�ҵ����ʵ�λ��
			{
				break;
			}
		}
		a[end + 1] = tmp; //��ȡ����Ԫ�ز���
	}
}

// ϣ������
// �趨һ��gap��������gap�����������зָ�����������У��������зֱ���в�������
// ��gap��С���ظ�����1����gap=1ʱ���ǲ�������
void ShellSort(int* a, int n) 
{
	//gap > 1 Ԥ����
	//gap = 1 ֱ�Ӳ�������
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

//  ѡ������
// ��1������δ����Ĳ����ҳ���Сֵ�����򣩣�������δ���򲿷ֵĵ�һ��Ԫ�ؽ���
// ��2���ظ�n-1���һ�������һ��Ԫ��һ�����������Բ������ˣ�
void SelectSort(int* a, int n) 
{
	int begin = 0, end = n - 1;
	int tmp = 0;
	while (begin < end)
	{
		int min = begin;
		int max = begin;
		for (int i = begin; i <= end; i++) //����Ѱ��������Сֵ
		{
			if (a[i] > a[max])
				max = i; //�������ֵ���±�
			if (a[i] < a[min])
				min = i; //������Сֵ���±�
		}
		tmp = a[begin]; //����Сֵ������ǰ��
		a[begin] = a[min];
		a[min] = tmp;
		if (max == begin) 
		{
            //���ֵ���ǡ����begin����ͨ�������͵���min��λ�ã���Ҫ�����±�
			max = min;
		}
		tmp = a[end]; //�����ֵ����������
		a[end] = a[max];
		a[max] = tmp;
		begin++; //����ͷ��λ��
		end--; //����β��λ��
	}
}

void AdjustDown(int* a, int n, int root) //���µ����㷨
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

//  ������
// ��1���Ƚ��ѣ����򽨴�ѣ�����С��
// ��2�����Ѷ�Ԫ�����βԪ�ػ��������ų�����
// ��3����ʱ�ѵ����ʱ����ƣ�ͨ�����µ����㷨����Ϊ�µĶѣ��ظ�����2ֱ����������
void HeapSort(int* a, int n) 
{
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i); //ͨ�����µ����㷨����
	}
	while (n > 1)
	{
		Swap(&a[0], &a[n - 1]); //���Ѷ�Ԫ�ؽ�������β
		n--; //�ų�ԭ�Ѷ�Ԫ��
		AdjustDown(a, n, 0); //���������ҵĶ�
	}
}

//  ð������
// ��1����ͷ��β�Ƚ�����Ԫ�أ������һ�����ڵڶ��������򣩾ͽ����߽���λ��
// ��2���ظ�n-1���һ�������һ��Ԫ��һ������С�����Բ������ˣ�
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
				flag = true; //�������Ԫ�ؽ�����flag��ֵΪtrue
			}
		}
		if (flag == false) //�������ð�ݺ�flagû�з����ı�˵���Ѿ�����
			break;
	}
}

// �ݹ�ʵ�ֿ�������

// ����ȡ���Ż�
// ���������������������߽ӽ����������ʱ��ѡ���key����ǡ��Ϊ��Сֵ��Ч�ʱȽϵ��£������һЩ����Ҫ�ĵݹ顣
// ���ݹ���ò�������ᵼ��ջ�����������������ǿ���ʹ������ȡ�еİ취����������������Ż���
// ����ȡ�У����ǶԱȴ���������ͷ����ֵ���в���ֵ��β����ֵ��ѡ�������мȲ������Ҳ������С��ֵ��Ϊkeyֵ�����ŵ�����ͷ��
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

//  ��������hoare�汾
// ��1��ѡ������������ͷ������β������Ԫ����Ϊkeyֵ�������±�
// ��2��ɨ����������У�һ��������Ѱ�ұ�key���ֵ����һ����������Ѱ�ұ�keyС��ֵ���ҵ��󽫶��߽�����
// ��3��������������ɨ������󣬽�����ͷ����key��leftλ�ô���Ԫ�ؽ�����������left����ʱleft��keyֵ���±꣩
int PartSort1(int* a, int left, int right) 
{
    //left�Ӵ���������ͷ������ߣ�right�Ӵ���������β����ǰ��
    int midi = GetMidIndex(a, left, right); //����ȡ��
	Swap(&a[left], &a[midi]);
	int key = left; //�����������еĵ�һ��Ԫ����Ϊkeyֵ
	while (left < right) //leftС��right˵����������û����
	{
		while (left < right && a[right] >= a[key]) //rightλ�õ�ֵ����keyСʱ��ǰ��
		{
			right--;
		}
		while (left < right && a[left] <= a[key]) //leftλ�õ�ֵ����key��ʱ�����
		{
			left++;
		}
		//��ʱrightλ�õ�ֵ��keyС��leftλ�õ�ֵ��key��
		Swap(&a[left], &a[right]); //���߽���
	}
	//������ͷ����Ϊkeyֵ��Ԫ�ؽ�����leftλ�ã���ɵ�������
	Swap(&a[key], &a[left]);
	return left; //����leftλ�ô�ŵ�keyֵ
}

//  ���������ڿӷ�
// ��1��������������ͷ����Ԫ�ش�ŵ�һ����ʱ��������Ϊkeyֵ����keyֵԭ�ȵ�λ����Ϊ��λ
// ��2����������Ѱ�ұ�keyС��ֵ���ҵ�����������У�������ԭ����λ�ó�Ϊ�µĿ�
// ��3����������Ѱ�ұ�key���ֵ���ҵ�����������У�������ԭ����λ�ó�Ϊ�µĿ�
// ��4���ظ�����2~3ֱ������������ɨ�����
// ��5�����keyֵ������У�����keyֵ�±�
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

//  ��������ǰ��ָ�뷨
// ��1��prevָ��ָ����������п�ͷ��curָ��ָ��prev����һ��λ�ã�������ͷ��Ԫ����Ϊkeyֵ
// ��2��cur�����Ѱ�ұ�keyС��ֵ������ҵ���prev++��������Ԫ��
// ��3���ظ�����2ֱ��cur�ߵ���β����keyֵ��prevλ�õ�ֵ����������keyֵ��ʱ���±�
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

void QuickSort(int* a, int left, int right) //�ݹ�����
{
	if (left >= right)
		return;
	int key = PartSort2(a, left, right);
	QuickSort(a, left, key - 1);
	QuickSort(a, key + 1, right);
}

// С�����Ż������
// ����������һ��������Ϊ100�����������ʱֻ��Ҫ�ݹ�20�㣬������һ��8�����ݵ���������ʱ��Ҫ�ݹ�3�㡣
// �ڵݹ���Ķ������ṹ�У���ײ�������ĵݹ������Ȼռ����ȫ���ݹ������87.5%!
// ������ǿ��ԶԵݹ�ʵ�ֿ��ŵĴ�������Ż������������������Сʱ��תΪʹ�������������㷨
// ��������Ϊ�˼��ٵݹ���ô��������Ч��
// �������ǿ���ʹ�ò���������������������С������
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

// ��·���ְ����
// ��Ȼ����ȡ�з��ܽ�����������������ӽ�������������������������д�����Ԫ�غ�key��ȣ�����������������Ԫ�ض����ʱ������ȡ��Ҳ�޷�����������
// ��ʱ��Ҫʹ����·���ֵ�˼��
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

//  �ǵݹ�ʵ�ֿ�������(ջ)
// ��1�����Ƚ�����������β�����±�ѹ��ջ�У��ٽ�ͷ�����±�ѹ��ջ�У���Ϊ�����ջҪ��ȡ��ͷ����ȡ��β����ջ�������Ǻ���ȳ���
// ��2��ȡ����ջ��Ԫ�أ��ֱ�ȡ������ͷ����β�����±꣬����һ������е���������ȡkeyֵ���±�
// ��3����keyֵ����ԭ����ͷ����β������ʱ����keyֵΪ�ֽ罫��ǰ�������ֳ������֣��ֱ�ѹ��ջ��
// ��4���ظ�����2~3ֱ��ջΪ��
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

//  �ݹ�ʵ�ֹ鲢����
// ��1��ͨ���ݹ齫���������в��ϵĶ԰�֣�ֱ���ֳ�����������ֻ��һ��Ԫ��
// ��2�������������������������ı߽磬�Զ��߽��й鲢
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

//  �ǵݹ�ʵ�ֹ鲢����
// ��1���趨һ����ʼֵΪ1��gap
// ��2��ͨ��gap���ָ������С�ÿ�ηָ���������ڵ������н��й鲢���鲢��һ��ͽ��串�ǵ�ԭ������
// ��3���ظ�����2ֱ����һ�ֹ鲢����
// ��4��gap��2���ظ�����2~3��ֱ��gap����ԭ���еĴ�С
// �ǵݹ�汾�����ѽ�����Ǳ߽�����,�����ڵ����������ж�Խ��ʱ�����ǾͲ������ǽ��й鲢�ˣ�����ԭ�����оͺ�.��ֻ�еڶ���������Խ��ʱ�����Ƕ�Խ��������Ҳ������������
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

//  ��������
// ��1�����ȱ��������������ҳ����ֵ����Сֵ���������Ԫ�صķ�Χ��С
// ��2����������ķ�Χ����һ��ռ䣬�������ͳ�Ƴ���Ԫ�ظ���
// ��Ϊ������Ԫ�صķ�Χ��һ����0��ʼ�����ʹ�þ���ӳ�䣨��Ԫ�ص���ʵ��ֵ��Ϊ�±꣩�ͻ��˷Ѵ����ռ䡣�������ҳ����ֵ����Сֵ�󣬽�Ԫ�ؼ�ȥ��Сֵ�����������λ��
// ��3���������������У���ÿ��Ԫ�س��ֵĴ�������ͳ��
// ��4������ͳ�ƵĽ��������˳�����ԭ����
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