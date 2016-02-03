/**************************************************
�ļ�����		Head.h
�����ˣ�		Mako Wan
��ע���ڣ�	2016-02-03
������		���ķ�������ͷ�ļ�
**************************************************/

#include "iostream"
#include "string"
#include "vector"
#include "map"

#include "CSVparser.hpp"

using namespace std;


//�Զ��������
typedef struct paperinfo
{
	string title = "";
	string abstra = "";
	string originalKeywords = "";
	string citeReference = "";
	string citeMeAs = "";

	vector<string> keywords;

}paperInfo;


/*
��������	readCSV
���ܣ�	��ȡCSV�ļ���������load���ڴ��д���
���룺	��
���أ�	��
*/
void readCSV();