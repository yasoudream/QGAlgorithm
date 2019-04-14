#ifndef __QG_ALGORITHM_H__
#define __QG_ALGORITHM_H__

//Ϊʵ�֣�͵������������Ŀ�
#include <queue>

//�������飬Ĭ����С��������
class QGAlgorithm
{
private:
	template <typename T>
	static bool defaultComparator(T a, T b) { return a < b; };	//Ĭ�ϱȽ���

public:
	QGAlgorithm() {};
	~QGAlgorithm() {};


	//��������
	template <typename T>
	static void InsertSort(T data[], int size, bool(*func)(T a, T b) = defaultComparator);

	//�鲢����
	template <typename T>
	static void MergeSort(T data[], int size, bool(*func)(T a, T b) = defaultComparator);

	//��������
	template <typename T>
	static void QuickSort(T data[], int size, bool(*func)(T a, T b) = defaultComparator);

	//��ѭ������
	template <typename T>
	static void QuickSort_pureCycle(T data[], int size, bool(*func)(T a, T b) = defaultComparator);

	//��������int�޶�
	static void CountSort(int data[], int size);

	//������������int�޶�
	static void RadixCountSort(int data[], int size);


private:
	//�鲢�������㷨��headΪǰ��ţ�endΪ�����
	template <typename T>
	static void MergeSort_main(T data[], T tdata[], int head, int end, bool(*func)(T a, T b));

	//�ݹ��������㷨��headΪǰ��ţ�endΪ�����
	template <typename T>
	static void QuickSort_main(T data[], int head, int end, bool(*func)(T a, T b));

};

template<typename T>
void QGAlgorithm::InsertSort(T data[], int size, bool(*func)(T a, T b))
{
	if (size <= 1)
		return;
	int j = 1;//for�ñ���
	for (int i = 1; i < size; i++)
	{
		T t = data[i];
		//�Ա��ǰ��Ԫ�ؽ�������ƴ������ҵ�����λ��
		for (j = i; j > 0 && func(t, data[j - 1]); j--)
			data[j] = data[j - 1];
		data[j] = t;
	}
}

template<typename T>
void QGAlgorithm::MergeSort(T data[], int size, bool(*func)(T a, T b))
{
	//�м�����
	T* tdata = new T[size];
	QGAlgorithm::MergeSort_main(data, tdata, 0, size - 1, func);
	delete tdata;
}

template<typename T>
void QGAlgorithm::QuickSort(T data[], int size, bool(*func)(T a, T b))
{
	/*QGAlgorithm::QuickSort_main(data, 0, size - 1, func);*/
	QuickSort_main(data, 0, size - 1, func);
}

template<typename T>
inline void QGAlgorithm::QuickSort_pureCycle(T data[], int size, bool(*func)(T a, T b))
{
	std::queue<std::pair<int, int>> record;//��ż�¼��
	record.push({ 0, size - 1 });
	while (record.size() > 0)
	{
		int i = record.front().first;
		int j = record.front().second;
		record.pop();
		if (i >= j)
			continue;
		int head = i;//��¼�����
		int end = j;//��¼β���
		T temp = data[i];//��¼��һ����Ϊ�м�
		while (i < j)
		{
			while (i < j && !func(data[j], temp))
				j--;
			if (i < j)
			{
				data[i] = data[j];
				i++;
			}

			while (i < j && func(data[i], temp))
				i++;
			if (i < j)
			{
				data[j] = data[i];
				j--;
			}
		}
		data[i] = temp;
		record.push({ head, i - 1 });
		record.push({ i + 1, end });
	}
}

template<typename T>
void QGAlgorithm::MergeSort_main(T data[], T tdata[], int head, int end, bool(*func)(T a, T b))
{
	if (head == end)
		return;
	//�����
	int m = (head + end) / 2;

	//��ұ�ݹ�
	MergeSort_main(data, tdata, head, m, func);
	MergeSort_main(data, tdata, m + 1, end, func);

	//�鲢
	int i = head, j = m + 1, k = head;
	while (j <= end || i <= m)
	{
		if (j > end || i <= m && func(data[i], data[j]))
			tdata[k++] = data[i++];
		else
			tdata[k++] = data[j++];
	}
	//���ƻ�ԭ����
	for (i = head; i <= end; i++)
		data[i] = tdata[i];
}

template<typename T>
void QGAlgorithm::QuickSort_main(T data[], int head, int end, bool(*func)(T a, T b))
{
	if (head >= end)
		return;
	//�±���
	int i, j;
	i = head + 1;
	j = end;
	//�����м����
	T t;

	while (1)
	{
		//�ҵ����������Ľ�������
		while (func(data[i], data[head]) && i < j)
			i++;
		while (func(data[head], data[j]) && i < j)
			j--;
		//�жϽ�����ʽ
		if (i < j)
		{
			t = data[i];
			data[i] = data[j];
			data[j] = t;
			i++;
			j--;
		}
		else if (func(data[i], data[head]))
		{
			t = data[head];
			data[head] = data[i];
			data[i] = t;
			break;
		}
		else
		{
			t = data[head];
			data[head] = data[i - 1];
			data[i - 1] = t;
			i--;
			break;
		}
	}
	//�ݹ�
	QGAlgorithm::QuickSort_main(data, head, i - 1, func);
	QGAlgorithm::QuickSort_main(data, i + 1, end, func);
}


//template <typename T>
//void QGAlgorithm::QuickSort_main(T data[], int head, int end, bool(*func)(T a, T b))
//{
//	if (head >= end)
//		return;
//	int i = head;
//	int j = end;
//	T temp = data[i];//��¼��һ����Ϊ�м�
//
//	while (i < j)
//	{
//		while (i < j && !func(data[j], temp))
//			j--;
//		if (i < j)
//		{
//			data[i] = data[j];
//			i++;
//		}
//
//		while (i < j && func(data[i], temp))
//			i++;
//		if (i < j)
//		{
//			data[j] = data[i];
//			j--;
//		}
//
//	}
//	//�ѻ�׼���ŵ�iλ��
//	data[i] = temp;
//	//�ݹ鷽��
//	QGAlgorithm::QuickSort_main(data, head, i - 1, func);
//	QGAlgorithm::QuickSort_main(data, i + 1, end, func);
//
//}
#endif