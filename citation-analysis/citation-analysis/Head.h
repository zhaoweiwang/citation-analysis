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
#include "set"

#include "CSVparser.hpp"
#include "english_stem.h"

using namespace std;


//�Զ��������
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
	unordered_map<string, int> wordVec;		//δȥ���ࡢ��ϣ��Ƶ

	vector<stemInfo> stemVec;
	vector<double> dataMat;

	set<string> reference;
	vector<int> citeRidx;

	int scan = 0;
	bool citeFlag = false;

}paperInfo;


/*
��������	readCSV
���ܣ�	��ȡCSV�ļ���������load���ڴ��д���
���룺	��
���أ�	��
*/
void readCSV();

/*
��������	calCite
���ܣ�	���������뱻�������
���룺	��
���أ�	��
*/
void calCite();

/*
��������	getMat
���ܣ�	���Ȩ�ؾ���
���룺	��
���أ�	��
*/
void getMat();

/*
��������	outputResult
���ܣ�	�����Ȩ�ؽ��
���룺	��
���أ�	��
*/
void outputResult();


/*
��������	doc2Word
���ܣ�	�ִ�
���룺	��
���أ�	��
*/
void doc2Word();