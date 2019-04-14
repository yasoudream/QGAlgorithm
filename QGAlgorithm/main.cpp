#include "QGAlgorithm.h"
#include "CheckTool.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>

constexpr auto MAX_LEN = 1000;
int input_int()
{
	char ch[MAX_LEN];
	gets_s(ch);
	if (strlen(ch) != 2)
		return 0;
	return (ch[0] - '0') * 10 + ch[1] - '0';
}


int main()
{
	system("color F0");
	int size = 0;
	int command = 0;
	int* data = nullptr;
	float ot;//����ǰʱ��
	float nt;//�����ʱ��
	bool noty;
	while (1)
	{
		ot = nt = 0;
		noty = false;
		system("cls");
		std::cout << "\n\n      ���Ǹ��㷨���Գ���\n\
      �㷨��1.��������    2.�鲢����    3.��������\n\
	    4.��ѭ������  5.��������    6.��������\n\n\
	  ��������   1��1W     2��5W    3��20W\n\n\
	  ������������������ֱ�ʾ�㷨��������\n\
	        ���磺��������1W������ Ӧ���� 11\n\
	  ����77�˳�������Ҫû��\n\n\
		���������";
		command = input_int();
		if (command == 77)
			break;
		switch (command % 10)
		{
		case 1:
			data = new int[10000];
			CheckTool::RandomDataMaker(data, CheckTool::sizeKind::oneW);
			size = 10000;
			break;
		case 2:
			data = new int[50000];
			CheckTool::RandomDataMaker(data, CheckTool::sizeKind::fiveW);
			size = 50000;
			break;
		case 3:
			data = new int[200000];
			CheckTool::RandomDataMaker(data, CheckTool::sizeKind::twentyW);
			size = 200000;
			break;
		default:
			std::cout << "      δʶ������\n\n";
			noty = true;
			system("pause>nul");
			break;
		}
		if (noty)
			continue;
		switch (command / 10)
		{
		case 1:
			if (command % 10 == 3)
			{
				std::cout << "       ��Ҫ3min���ң�ȷ����yȷ��\n\n";
				if (_getch() != 'y')
				{
					noty = true;
					break;
				}
			}
			ot = clock();
			QGAlgorithm::InsertSort(data, size);
			nt = clock();
			break;

		case 2:
			ot = clock();
			QGAlgorithm::MergeSort(data, size);
			nt = clock();
			break;

		case 3:
			ot = clock();
			QGAlgorithm::QuickSort(data, size);
			nt = clock();
			break;

		case 4:
			ot = clock();
			QGAlgorithm::QuickSort_pureCycle(data, size);
			nt = clock();
			break;

		case 5:
			ot = clock();
			QGAlgorithm::CountSort(data, size);
			nt = clock();
			break;

		case 6:
			ot = clock();
			QGAlgorithm::RadixCountSort(data, size);
			nt = clock();
			break;

		default:
			std::cout << "      δʶ������\n\n";
			break;
		}

		if (noty)
		{
			delete data;
			std::cout << "         �ɹ�ȡ��\n\n";
			continue;
		}
		
		if (!noty && CheckTool::OrderCheck(data, size))
			std::cout << "\n         ����ɹ�����\n\n";
		else
			std::cout << "         ������������ʧ��\n\n";
		delete data;
			
		std::cout << "         ����ʱ�䣺" << nt - ot << "ms\n\n";
		
		system("pause");
	}
	
	std::cout << "      ���Ѿ��˳�\n\n";
	system("pause>nul");
	return 0;
}