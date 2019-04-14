#include "QGAlgorithm.h"



void QGAlgorithm::CountSort(int data[], int size)
{
	int min, max;
	min = max = data[0];
	//统计最大最小
	for (int i = 0; i < size; i++)
	{
		if (min > data[i])
			min = data[i];
		if (max < data[i])
			max = data[i];
	}

	//为中间数组分配空间
	int* tdata = new int[max - min + 1];
	int* mdata = new int[size];

	//初始化
	for (int i = 0; i <= max - min; i++)
		tdata[i] = 0;


	//收集
	for (int i = 0; i < size; i++)
		tdata[data[i] - min]++;

	//统计
	int count = 0;
	for (int i = 0; i <= max - min; i++)
	{
		count += tdata[i];
		tdata[i] = count;
	}

	//分配
	for (int i = size - 1; i >= 0; i--)
		mdata[--tdata[data[i] - min]] = data[i];

	//复制
	for (int i = 0; i < size; i++)
		data[i] = mdata[i];

	//垃圾处理
	delete tdata;
	delete mdata;
}

void QGAlgorithm::RadixCountSort(int data[], int size)
{
	std::queue<int>  count[10];	//基数计数队列表
	int tenCount = 1;			//位数计数
	int max = data[0];			//最大值
	int order = 0;				//最大位数

	//找最大值
	for (int i = 0; i < size; i++)
		if (max < data[i])
			max = data[i];

	while (max > 0)
	{
		max /= 10;
		order++;
	}



	for (int i = 0; i < order; i++)
	{
		//基数提取
		for (int j = 0; j < size; j++)
			count[data[j] % (10 * tenCount) / tenCount].push(data[j]);
		
		int k = 0;//下标计数
		//遍历队列
		for (int j = 0; j < 10; j++)
		{
			//置入数组
			while (count[j].size() > 0)
			{
				int t = count[j].front();
				count[j].pop();
				data[k++] = t;
			}
		}
		//进入下一位
		tenCount *= 10;
	}
}

