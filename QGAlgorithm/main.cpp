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
	float ot;//排序前时间
	float nt;//排序后时间
	bool noty;
	while (1)
	{
		ot = nt = 0;
		noty = false;
		system("cls");
		std::cout << "\n\n      这是个算法测试程序\n\
      算法：1.插入排序    2.归并排序    3.快速排序\n\
	    4.纯循环快排  5.计数排序    6.基数计排\n\n\
	  数据量：   1：1W     2：5W    3：20W\n\n\
	  命令：输入两个连续数字表示算法和数据量\n\
	        例如：插入排序1W数据量 应输入 11\n\
	  输入77退出（程序要没）\n\n\
		请输入命令：";
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
			std::cout << "      未识别命令\n\n";
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
				std::cout << "       需要3min左右，确定？y确定\n\n";
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
			std::cout << "      未识别命令\n\n";
			break;
		}

		if (noty)
		{
			delete data;
			std::cout << "         成功取消\n\n";
			continue;
		}
		
		if (!noty && CheckTool::OrderCheck(data, size))
			std::cout << "\n         排序成功！！\n\n";
		else
			std::cout << "         出现意外排序失败\n\n";
		delete data;
			
		std::cout << "         花费时间：" << nt - ot << "ms\n\n";
		
		system("pause");
	}
	
	std::cout << "      您已经退出\n\n";
	system("pause>nul");
	return 0;
}