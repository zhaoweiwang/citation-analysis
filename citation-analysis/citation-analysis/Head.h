/**************************************************
�ļ�����		Head.h
�����ˣ�		Mako Wan
��ע���ڣ�	2016-02-03
������		���ķ�������ͷ�ļ�
**************************************************/

#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include <algorithm>
#include "unordered_map"
#include "map"

#include "CSVparser.hpp"
#include "english_stem.h"

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
	unordered_map<string, int> wordVec;		//δȥ���ࡢ��ϣ��Ƶ

}paperInfo;


/*
��������	readCSV
���ܣ�	��ȡCSV�ļ���������load���ڴ��д���
���룺	��
���أ�	��
*/
void readCSV();


/*
��������	doc2Word
���ܣ�	�ִ�
���룺	��
���أ�	��
*/
void doc2Word();