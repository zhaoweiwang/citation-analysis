/**************************************************
文件名：		main.cpp
创建人：		Mako Wan
加注日期：	2016-02-03
描述：		引文分析的主函数
**************************************************/

#include "Head.h"

int main(){

	//testCal();
	//前期操作: 语料库构建
	loadCorpus();
	//Step1: 读取CSV文件，把每一条引文记录load到内存
	readCSV();
	//Step2: 计算引用与被引情况
	calCite();
	//Step3: getMat；
	getMat();
	//Step4 输出无权重统计结果
	outputResult();
	//Step4: 分词、去无效词
	//doc2Word();
	//Step5: 计算分类效果
	calSSE();

	return 0;
}