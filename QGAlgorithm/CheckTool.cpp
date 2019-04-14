#include "CheckTool.h"

void CheckTool::RandomDataMaker(int data[], sizeKind size)
{
	std::ofstream film;	//�ļ�
	int realsize;		//int��size

	//��֧����
	switch (size)
	{
	case sizeKind::oneW:
		film.open(".\\1wData.txt");
		realsize = 10000;
		break;
	case sizeKind::fiveW:
		film.open(".\\5wData.txt");
		realsize = 50000;
		break;
	case sizeKind::twentyW:
		film.open(".\\20wData.txt");
		realsize = 200000;
		break;
	default:
		return;
	}

	srand(time(NULL));

	//���ɴ���
	int num;
	for (int i = 0; i < realsize; i++)
	{
		num = rand() % SCOPE;		//����
		data[i] = num;				//���
		film << num << '\t';	//д���ļ�
		if ((i + 1) % 10 == 0)
			film << std::endl;
	}

	film.close();
}

bool CheckTool::OrderCheck(int data[], int size)
{
	for (int i = 0; i < size - 1; i++)
		if (data[i] > data[i + 1])
			return false;
	return true;
}
