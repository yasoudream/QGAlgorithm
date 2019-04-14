#ifndef __CHECK_TOOL_H__
#define __CHECK_TOOL_H__

#include <fstream>
#include <ctime>
#include <cstdlib>

constexpr int SCOPE = 1000000000;					//生成范围



class CheckTool
{
public:
	CheckTool() {};
	~CheckTool() {};

	enum class sizeKind { oneW, fiveW, twentyW };			//数据量
	static void RandomDataMaker(int data[], sizeKind size);	//数据生成器
	static bool OrderCheck(int data[], int size);		//顺序检测器(小到大)

};








#endif // !__CHECK_TOOL_H__

