#ifndef __CHECK_TOOL_H__
#define __CHECK_TOOL_H__

#include <fstream>
#include <ctime>
#include <cstdlib>

constexpr int SCOPE = 1000000000;					//���ɷ�Χ



class CheckTool
{
public:
	CheckTool() {};
	~CheckTool() {};

	enum class sizeKind { oneW, fiveW, twentyW };			//������
	static void RandomDataMaker(int data[], sizeKind size);	//����������
	static bool OrderCheck(int data[], int size);		//˳������(С����)

};








#endif // !__CHECK_TOOL_H__

