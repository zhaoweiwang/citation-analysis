/**************************************************
文件名：		Head.h
创建人：		Mako Wan
加注日期：	2016-02-03
描述：		引文分析的主头文件
**************************************************/

#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include <algorithm>
#include "unordered_map"
#include "map"
#include "set"

#include "CSVparser.hpp"
#include "english_stem.h"

using namespace std;


//自定义变量区
typedef struct steminfo{

	string term = "";
	double tf  = 0.0;
	double idf = 0.0;
	double tf_idf = 0.0;

}stemInfo;

typedef struct paperinfo{

	string title = "";
	string abstra = "";
	string originalKeywords = "";
	string citeReference = "";
	string citeMeAs = "";

	set<string> stemTile;
	set<string> stemKeyword;
	vector<string> keywords;
	unordered_map<string, int> wordVec;		//未去冗余、哈希词频

	vector<stemInfo> stemVec;
	vector<double> dataMat;

	set<string> reference;
	vector<int> citeRidx;

	int scan = 0;
	bool citeFlag = false;

}paperInfo;


/*
函数名：	readCSV
功能：	读取CSV文件，将数据load到内存中处理
输入：	无
返回：	无
*/
void readCSV();

/*
函数名：	calCite
功能：	计算引用与被引用情况
输入：	无
返回：	无
*/
void calCite();

/*
函数名：	getMat
功能：	获得权重矩阵
输入：	无
返回：	无
*/
void getMat();

/*
函数名：	outputResult
功能：	输出无权重结果
输入：	无
返回：	无
*/
void outputResult();


/*
函数名：	doc2Word
功能：	分词
输入：	无
返回：	无
*/
void doc2Word();