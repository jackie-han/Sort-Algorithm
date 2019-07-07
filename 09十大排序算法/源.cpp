#include<iostream>
using namespace std;

//��ӡ����
void printArr(int A[], int N)
{
	for (int i = 0; i < N; ++i)
		cout << A[i] << " ";
	cout << endl;
}

//������ֵ
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

//1.ð������
void BubbleSort(int A[], int N)
{
	int i, j;
	for (i = 0; i < N - 1; ++i)	//������N-1��
		for (j = 0; j < N - i - 1; j++)
			if (A[j] > A[j + 1])
				swap(A[j], A[j + 1]);
}

//ð������--�Ż�1����ÿ��������һ����ǣ��������˽����ͽ���Ǽ�Ϊ1
void BubbleSort_V1(int A[], int N)
{
	int i, j;
	for (i = 0; i < N - 1; ++i)	//������N-1��
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


//2.ֱ�Ӳ�������
void InsertSort(int A[], int N)
{
	int i, j, tmp;
	for (i = 1; i < N; ++i)
	{
		tmp = A[i];
		//��A[i]С��ǰ�ߵ�ֵʱ���ͽ�ǰ�ߵ�ֵ���κ���
		for (j = i; j > 0 && tmp < A[j - 1]; --j)
			A[j] = A[j - 1];
		A[j] = tmp;
	}
}

//3.ѡ������
void SelectSort(int A[], int N)
{
	int i, j, min;
	for (i = 0; i < N - 1; i++)
	{
		min = i;
		//��������ѡ��һ����С�ģ��뵱ǰλ�ý���
		for (j = i + 1; j < N; j++)
			if (A[j] < A[min])
				min = j;
		swap(A[i], A[min]);
	}
}

//4.ϣ������---ֱ������Ľ���
void ShellSort(int A[], int N)
{
	int i, j, tmp;
	int Increment;	//��������
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

//5.�鲢����
void Merge(int A[], int TmpArray[], int Left, int Right, int RightEnd)
{
	int LeftEnd = Right - 1;
	int TmpPos = Left;	//TmpArray�е��±�
	int NumElements = RightEnd - Left + 1;	//Ԫ�ظ���
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

//6.��������
int Median3(int A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;
	if (A[Left] > A[Center])
		swap(A[Left], A[Center]);
	if (A[Left] > A[Right])
		swap(A[Left], A[Right]);
	if (A[Center] > A[Right])
		swap(A[Center], A[Right]);

	//����Ԫ���ڵ����ڶ���λ��
	swap(A[Center], A[Right - 1]);

	return A[Right - 1];
}

void QSort(int A[], int Left, int Right)
{
	int i, j;
	int Pivot;
	if (Left + 2 <= Right)		//��������Ԫ��ʱ����ִ�еݹ飬��ֻ������Ԫ��ʱ�˳�
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
	else if (A[Left] > A[Right])	//��ֻ������Ԫ������ߴ����ұ�ʱ������
		swap(A[Left], A[Right]);
}

void QuickSort(int A[], int N)
{
	QSort(A, 0, N - 1);
}

//7.������--�����
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

//8.��������--Ҫ����������ݱ�������ȷ����Χ������
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

//ð���������
void test_BubbleSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "ð��������ԣ�" << endl;
	cout << "����ǰ�� ";
	printArr(A, 20);

	BubbleSort(A, 20);
	cout << "����� ";
	printArr(A, 20);
	cout << endl;
}

//ð���������--�Ż�1
void test_BubbleSort_V1()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "ð�������Ż�1���ԣ�" << endl;
	cout << "����ǰ�� ";
	printArr(A, 20);

	BubbleSort_V1(A, 20);
	cout << "����� ";
	printArr(A, 20);
	cout << endl;
}

//ֱ�Ӳ����������
void test_InsertSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "ֱ�Ӳ���������ԣ�" << endl;
	cout << "����ǰ�� ";
	printArr(A, 20);

	InsertSort(A, 20);
	cout << "����� ";
	printArr(A, 20);
	cout << endl;
}

//ѡ���������
void test_SelectSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "ѡ��������ԣ�" << endl;
	cout << "����ǰ�� ";
	printArr(A, 20);

	SelectSort(A, 20);
	cout << "����� ";
	printArr(A, 20);
	cout << endl;
}

//ϣ���������
void test_ShellSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "ϣ��������ԣ�" << endl;
	cout << "����ǰ�� ";
	printArr(A, 20);

	ShellSort(A, 20);
	cout << "����� ";
	printArr(A, 20);
	cout << endl;
}

//�鲢�������
void test_MergeSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "�鲢������ԣ�" << endl;
	cout << "����ǰ�� ";
	printArr(A, 20);

	MergeSort(A, 20);
	cout << "����� ";
	printArr(A, 20);
	cout << endl;
}

//�����������
void test_QuickSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "����������ԣ�" << endl;
	cout << "����ǰ�� ";
	printArr(A, 20);

	QuickSort(A, 20);
	cout << "����� ";
	printArr(A, 20);
	cout << endl;
}

//���������
void test_HeapSort()
{
	int A[20] = { 9,19,1,16,2,4,0,8,7,15,3,6,17,10,5,11,18,14,12,13 };
	cout << "��������ԣ�" << endl;
	cout << "����ǰ�� ";
	printArr(A, 20);

	HeapSort(A, 20);
	cout << "����� ";
	printArr(A, 20);
	cout << endl;
}

int main()
{
	test_BubbleSort();	//ð������
	test_BubbleSort_V1();	//ð�������Ż�V1
	test_InsertSort();	//��������
	test_SelectSort();	//ѡ������
	test_ShellSort();		//ϣ������
	test_MergeSort();		//�鲢����
	test_QuickSort();		//��������
	test_HeapSort();		//������

	return 0;
}
