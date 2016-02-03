/**************************************************
文件名：		Head.h
创建人：		Mako Wan
加注日期：	2016-02-03
描述：		引文分析的主头文件
**************************************************/

#include "iostream"
#include "string"
#include "vector"
#include "map"

#include "CSVparser.hpp"

using namespace std;


//自定义变量区
typedef struct paperinfo
{
	string title = "";
	string abstract = "";
	string originalKeywords = "";
	string citeReference = "";
	string citeMeAs = "";

	vector<string> keywords;

}paperInfo;


/*
函数名：	readCSV
功能：	读取CSV文件，将数据load到内存中处理
输入：	无
返回：	无
*/
void readCSV();