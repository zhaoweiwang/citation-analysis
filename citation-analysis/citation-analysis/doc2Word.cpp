#include "Head.h"
#include <boost/tokenizer.hpp>

extern vector<paperInfo> paperVec;
vector<string> stopWords;				//ͣ�ôʼ���

string str2Lower(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

void loadStopWords()
{
	cout << "��ȡͣ�ô�." << endl << endl;
	ifstream in("stop_words.txt");
	string tmp;
	while (!in.eof()) {
		getline(in, tmp, '\n');
		stopWords.push_back(tmp);
		tmp.clear();
	}
	std::sort(stopWords.begin(), stopWords.end());
}

void stemmingFunc(){
	for (int i = 0; i < paperVec.size(); ++i){
		cout << paperVec[i].abstra << endl << endl;
		cout << "��ȡ����." << endl << endl;
		boost::tokenizer<> tok(paperVec[i].abstra);
		double countWord = 0.0;
		for (boost::tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg){
			countWord++;

			string strTemp = str2Lower(*beg);
			wstring w(strTemp.size(), ' ');
			copy(strTemp.begin(), strTemp.end(), w.begin());
			stemming::english_stem<> english_stemmer;
			english_stemmer(w);
			string stem(strTemp.size(), ' ');
			copy(w.begin(), w.end(), stem.begin());
			stem = stem.substr(0, stem.find(' '));
			if (!(std::binary_search(stopWords.begin(), stopWords.end(), stem))){
				paperVec[i].wordVec[stem]++;
			}
		}
		
		
		cout << "����Сд����ȥ���ദ��." << endl << endl;
		cout << "���дʸɻ�ԭ." << endl << endl;
		getchar();

		multimap<double, string> sortMap;
		for (unordered_map<string, int>::iterator it = paperVec[i].wordVec.begin(); it != paperVec[i].wordVec.end(); ++it){
			double tempTf = ((double)(it->second)) / countWord;
			sortMap.insert(make_pair(tempTf, it->first));
		}
		
		for (multimap<double, string>::iterator it = sortMap.begin(); it != sortMap.end(); ++it)
			cout << it->second << ":" << it->first << endl;
		getchar();

		//unordered_map<string, int>::iterator iter;
		//for (iter = paperVec[i].wordVec.begin(); iter != paperVec[i].wordVec.end(); ++iter)
		//	cout << iter->first << ":" << iter->second << endl;
		//getchar();
	}
}

void doc2Word(){
	loadStopWords();
	stemmingFunc(); 
}