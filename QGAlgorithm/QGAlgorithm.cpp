#include "QGAlgorithm.h"



void QGAlgorithm::CountSort(int data[], int size)
{
	int min, max;
	min = max = data[0];
	//ͳ�������С
	for (int i = 0; i < size; i++)
	{
		if (min > data[i])
			min = data[i];
		if (max < data[i])
			max = data[i];
	}

	//Ϊ�м��������ռ�
	int* tdata = new int[max - min + 1];
	int* mdata = new int[size];

	//��ʼ��
	for (int i = 0; i <= max - min; i++)
		tdata[i] = 0;


	//�ռ�
	for (int i = 0; i < size; i++)
		tdata[data[i] - min]++;

	//ͳ��
	int count = 0;
	for (int i = 0; i <= max - min; i++)
	{
		count += tdata[i];
		tdata[i] = count;
	}

	//����
	for (int i = size - 1; i >= 0; i--)
		mdata[--tdata[data[i] - min]] = data[i];

	//����
	for (int i = 0; i < size; i++)
		data[i] = mdata[i];

	//��������
	delete tdata;
	delete mdata;
}

void QGAlgorithm::RadixCountSort(int data[], int size)
{
	std::queue<int>  count[10];	//�����������б�
	int tenCount = 1;			//λ������
	int max = data[0];			//���ֵ
	int order = 0;				//���λ��

	//�����ֵ
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
		//������ȡ
		for (int j = 0; j < size; j++)
			count[data[j] % (10 * tenCount) / tenCount].push(data[j]);
		
		int k = 0;//�±����
		//��������
		for (int j = 0; j < 10; j++)
		{
			//��������
			while (count[j].size() > 0)
			{
				int t = count[j].front();
				count[j].pop();
				data[k++] = t;
			}
		}
		//������һλ
		tenCount *= 10;
	}
}

