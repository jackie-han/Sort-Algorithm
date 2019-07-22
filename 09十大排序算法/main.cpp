#include<iostream>
using namespace std;

//打印数组
void printArr(int A[], int N)
{
	for (int i = 0; i < N; ++i)
		cout << A[i] << " ";
	cout << endl;
}

//交换两值
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

//1.冒泡排序
void BubbleSort(int A[], int N)
{
	int i, j;
	for (i = 0; i < N - 1; ++i)	//共排序N-1趟
		for (j = 0; j < N - i - 1; j++)
			if (A[j] > A[j + 1])
				swap(A[j], A[j + 1]);
}

//冒泡排序--优化1：在每轮中增加一个标记，若发生了交换就将标记记为1
void BubbleSort_V1(int A[], int N)
{
	int i, j;
	for (i = 0; i < N - 1; ++i)	//共排序N-1趟
	{
		int flag = 0;
		for (j = 0; j < N - i - 1; j++)
			if (A[j] > A[j + 1])
			{
				flag = 1;
				swap(A[j], A[j + 1]);
			}
		if (flag == 0)
			break;
	}	
}


//2.直接插入排序
void InsertSort(int A[], int N)
{
	int i, j, tmp;
	for (i = 1; i < N; ++i)
	{
		tmp = A[i];
		//当A[i]小于前边的值时，就将前边的值依次后移
		for (j = i; j > 0 && tmp < A[j - 1]; --j)
			A[j] = A[j - 1];
		A[j] = tmp;
	}
}

//3.选择排序
void SelectSort(int A[], int N)
{
	int i, j, min;
	for (i = 0; i < N - 1; i++)
	{
		min = i;
		//从序列中选择一个最小的，与当前位置交换
		for (j = i + 1; j < N; j++)
			if (A[j] < A[min])
				min = j;
		swap(A[i], A[min]);
	}
}

//4.希尔排序---直接排序改进版
void ShellSort(int A[], int N)
{
	int i, j, tmp;
	int Increment;	//增量序列
	for (Increment = N / 2; Increment > 0; Increment /= 2)
	{
		for (i = Increment; i < N; ++i)
		{
			tmp = A[i];
			for (j = i; j >= Increment&&tmp < A[j - Increment]; j -= Increment)
				A[j] = A[j - Increment];
			A[j] = tmp;
		}
	}
}

//5.归并排序
void Merge(int A[], int TmpArray[], int Left, int Right, int RightEnd)
{
	int LeftEnd = Right - 1;
	int TmpPos = Left;	//TmpArray中的下标
	int NumElements = RightEnd - Left + 1;	//元素个数
	while (Left <= LeftEnd&&Right <= RightEnd)
	{
		if (A[Left] <= A[Right])
			TmpArray[TmpPos++] = A[Left++];
		else
			TmpArray[TmpPos++] = A[Right++];
	}
	while (Left <= LeftEnd)
		TmpArray[TmpPos++] = A[Left++];
	while (Right <= RightEnd)
		TmpArray[TmpPos++] = A[Right++];

	for (int i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpArray[RightEnd];
}

void MSort(int A[], int TmpArray[], int Left, int Right)
{
	int Center;
	if (Left < Right)
	{
		Center = (Left + Right) / 2;
		MSort(A, TmpArray, Left, Center);
		MSort(A, TmpArray, Center + 1, Right);
		Merge(A, TmpArray, Left, Center + 1, Right);
	}
}
void MergeSort(int A[], int N)
{
	int *TmpArray = (int*)malloc(N * sizeof(int));
	if (TmpArray)
		MSort(A, TmpArray, 0, N - 1);
	else
		cout << "Out of space!" << endl;
}

//6.快速排序
int Median3(int A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;
	if (A[Left] > A[Center])
		swap(A[Left], A[Center]);
	if (A[Left] > A[Right])
		swap(A[Left], A[Right]);
	if (A[Center] > A[Right])
		swap(A[Center], A[Right]);

	//将主元放在倒数第二个位置
	swap(A[Center], A[Right - 1]);

	return A[Right - 1];
}

void QSort(int A[], int Left, int Right)
{
	int i, j;
	int Pivot;
	if (Left + 2 <= Right)		//当有三个元素时继续执行递归，当只有两个元素时退出
	{
		Pivot = Median3(A, Left, Right);
		i = Left, j = Right - 1;
		for (;;)
		{
			while (A[++i] < Pivot) {}
			while (A[--j] > Pivot) {}
			if (i < j)
				swap(A[i], A[j]);
			else
				break;
		}
		swap(A[i], A[Right - 1]);
		QSort(A, Left, i - 1);
		QSort(A, i + 1, Right);
	}
	else if (A[Left] > A[Right])	//当只有两个元素且左边大于右边时，交换
		swap(A[Left], A[Right]);
}

void QuickSort(int A[], int N)
{
	QSort(A, 0, N - 1);
}

//7.堆排序--大根堆
void PercDown(int A[], int i, int N)
{
	int Child;
	int Tmp;
	for (Tmp = A[i]; 2 * i + 1 < N; i = Child)
	{
		Child = 2 * i + 1;
		if (Child != N - 1 && A[Child + 1] > A[Child])
			Child++;
		if (Tmp < A[Child])
			A[i] = A[Child];
		else
			break;
	}
	A[i] = Tmp;
}

void HeapSort(int A[], int N)
{
	int i;
	for (i = N / 2; i >= 0; i--)
		PercDown(A, i, N);
	for (i = N - 1; i > 0; i--)
	{
		swap(A[0], A[i]);
		PercDown(A, 0, i);
	}
}

//8.计数排序--要求输入的数据必须是有确定范围的整数
void CountingSort(int A[], int N)
{
	int bias, min = A[0], max = A[0];
	for (int i = 1; i < N; i++)
	{
		if (A[i] > max)
			max = A[i];
		if (A[i] < min)
			min = A[i];
	}
	bias = 0 - min;
	int* bucket = new int[max - min + 1];
	fill(bucket, bucket + max - min, 0);
	for (int i = 0; i < N; i++)
		bucket[A[i] + bias]++;

	int Pos = 0, i = 0;
	while (i < N)
	{
		if (bucket[i] != 0)
		{
			A[Pos++] = i - bias;
			bucket[i]--;
		}
		else
			i++;	
	}
}

//冒泡排序测试
void test_BubbleSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "冒泡排序测试：" << endl;
	cout << "排序前： ";
	printArr(A, 20);

	BubbleSort(A, 20);
	cout << "排序后： ";
	printArr(A, 20);
	cout << endl;
}

//冒泡排序测试--优化1
void test_BubbleSort_V1()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "冒泡排序优化1测试：" << endl;
	cout << "排序前： ";
	printArr(A, 20);

	BubbleSort_V1(A, 20);
	cout << "排序后： ";
	printArr(A, 20);
	cout << endl;
}

//直接插入排序测试
void test_InsertSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "直接插入排序测试：" << endl;
	cout << "排序前： ";
	printArr(A, 20);

	InsertSort(A, 20);
	cout << "排序后： ";
	printArr(A, 20);
	cout << endl;
}

//选择排序测试
void test_SelectSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "选择排序测试：" << endl;
	cout << "排序前： ";
	printArr(A, 20);

	SelectSort(A, 20);
	cout << "排序后： ";
	printArr(A, 20);
	cout << endl;
}

//希尔排序测试
void test_ShellSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "希尔排序测试：" << endl;
	cout << "排序前： ";
	printArr(A, 20);

	ShellSort(A, 20);
	cout << "排序后： ";
	printArr(A, 20);
	cout << endl;
}

//归并排序测试
void test_MergeSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "归并排序测试：" << endl;
	cout << "排序前： ";
	printArr(A, 20);

	MergeSort(A, 20);
	cout << "排序后： ";
	printArr(A, 20);
	cout << endl;
}

//快速排序测试
void test_QuickSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "快速排序测试：" << endl;
	cout << "排序前： ";
	printArr(A, 20);

	QuickSort(A, 20);
	cout << "排序后： ";
	printArr(A, 20);
	cout << endl;
}

//堆排序测试
void test_HeapSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "堆排序测试：" << endl;
	cout << "排序前： ";
	printArr(A, 20);

	HeapSort(A, 20);
	cout << "排序后： ";
	printArr(A, 20);
	cout << endl;
}

int main()
{
	test_BubbleSort();	//冒泡排序
	test_BubbleSort_V1();	//冒泡排序优化V1
	test_InsertSort();	//插入排序
	test_SelectSort();	//选择排序
	test_ShellSort();		//希尔排序
	test_MergeSort();		//归并排序
	test_QuickSort();		//快速排序
	test_HeapSort();		//堆排序

	return 0;
}
