#ifndef __QG_ALGORITHM_H__
#define __QG_ALGORITHM_H__

//为实现（偷懒）基数排序的库
#include <queue>

//输入数组，默认由小到大排序
class QGAlgorithm
{
private:
	template <typename T>
	static bool defaultComparator(T a, T b) { return a < b; };	//默认比较器

public:
	QGAlgorithm() {};
	~QGAlgorithm() {};


	//插入排序
	template <typename T>
	static void InsertSort(T data[], int size, bool(*func)(T a, T b) = defaultComparator);

	//归并排序
	template <typename T>
	static void MergeSort(T data[], int size, bool(*func)(T a, T b) = defaultComparator);

	//快速排序
	template <typename T>
	static void QuickSort(T data[], int size, bool(*func)(T a, T b) = defaultComparator);

	//纯循环快排
	template <typename T>
	static void QuickSort_pureCycle(T data[], int size, bool(*func)(T a, T b) = defaultComparator);

	//计数排序，int限定
	static void CountSort(int data[], int size);

	//基数计数排序，int限定
	static void RadixCountSort(int data[], int size);


private:
	//归并排序主算法，head为前序号，end为后序号
	template <typename T>
	static void MergeSort_main(T data[], T tdata[], int head, int end, bool(*func)(T a, T b));

	//递归版快排主算法，head为前序号，end为后序号
	template <typename T>
	static void QuickSort_main(T data[], int head, int end, bool(*func)(T a, T b));

};

template<typename T>
void QGAlgorithm::InsertSort(T data[], int size, bool(*func)(T a, T b))
{
	if (size <= 1)
		return;
	int j = 1;//for用变量
	for (int i = 1; i < size; i++)
	{
		T t = data[i];
		//对标记前的元素进行向后复制处理至找到合适位置
		for (j = i; j > 0 && func(t, data[j - 1]); j--)
			data[j] = data[j - 1];
		data[j] = t;
	}
}

template<typename T>
void QGAlgorithm::MergeSort(T data[], int size, bool(*func)(T a, T b))
{
	//中间数组
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
	std::queue<std::pair<int, int>> record;//序号记录器
	record.push({ 0, size - 1 });
	while (record.size() > 0)
	{
		int i = record.front().first;
		int j = record.front().second;
		record.pop();
		if (i >= j)
			continue;
		int head = i;//记录首序号
		int end = j;//记录尾序号
		T temp = data[i];//记录第一个作为中间
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
	//中序号
	int m = (head + end) / 2;

	//分冶递归
	MergeSort_main(data, tdata, head, m, func);
	MergeSort_main(data, tdata, m + 1, end, func);

	//归并
	int i = head, j = m + 1, k = head;
	while (j <= end || i <= m)
	{
		if (j > end || i <= m && func(data[i], data[j]))
			tdata[k++] = data[i++];
		else
			tdata[k++] = data[j++];
	}
	//复制回原数组
	for (i = head; i <= end; i++)
		data[i] = tdata[i];
}

template<typename T>
void QGAlgorithm::QuickSort_main(T data[], int head, int end, bool(*func)(T a, T b))
{
	if (head >= end)
		return;
	//下标标记
	int i, j;
	i = head + 1;
	j = end;
	//交换中间变量
	T t;

	while (1)
	{
		//找到符合条件的交换对象
		while (func(data[i], data[head]) && i < j)
			i++;
		while (func(data[head], data[j]) && i < j)
			j--;
		//判断交换方式
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
	//递归
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
//	T temp = data[i];//记录第一个作为中间
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
//	//把基准数放到i位置
//	data[i] = temp;
//	//递归方法
//	QGAlgorithm::QuickSort_main(data, head, i - 1, func);
//	QGAlgorithm::QuickSort_main(data, i + 1, end, func);
//
//}
#endif