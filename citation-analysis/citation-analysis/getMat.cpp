#include "Head.h"
#include <boost/tokenizer.hpp>

extern vector<paperInfo> paperVec;

set<string> stemListSet;
vector<string> stemList;
vector<string> stopWords;				//ͣ�ôʼ���

unordered_map<string, int> stemCount;	//stem���ĵ���

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

inline bool compTFIDF(const stemInfo &a, const stemInfo &b){
	return a.tf_idf > b.tf_idf;
}

string str2Lower(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}


void tfidf2vecMN(){
	for (auto i = 0; i < paperVec.size(); ++i){
		vector<double> dataTemp(stemList.size(), 0.0);
		//int countTemp = 0;

		for (auto j = 0; j < paperVec[i].stemVec.size(); j++){

			size_t idx = find(stemList.begin(), stemList.end(), paperVec[i].stemVec[j].term) - stemList.begin();
			if (idx == stemList.size())
				continue;
			else{
				dataTemp.at(idx) = paperVec[i].stemVec[j].tf_idf;
				//countTemp++;
			}
		}
		dataTemp.swap(paperVec[i].dataMat);

		//int countT = 0;
		//for (int k = 0; k < paperVec[i].dataMat.size(); k++)
		//if (paperVec[i].dataMat[k] != 0.0)
		//	countT++;

		//cout << countTemp << endl;
		//cout << countT << endl;
		//getchar();
	}

}

void stemmingFunc(){
	for (int i = 0; i < paperVec.size(); ++i){
		//cout << paperVec[i].abstra << endl << endl;
		//cout << "��ȡ����." << endl << endl;
		boost::tokenizer<> tok(paperVec[i].abstra);

		boost::tokenizer<> tokTitle(paperVec[i].title);
		boost::tokenizer<> tokKeyword(paperVec[i].originalKeywords);
 
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
				stemListSet.insert(stem);
			}
		}

		for (boost::tokenizer<>::iterator beg = tokTitle.begin(); beg != tokTitle.end(); ++beg){
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
				stemListSet.insert(stem);

				paperVec[i].stemTile.insert(stem);
			}
		}


		for (boost::tokenizer<>::iterator beg = tokKeyword.begin(); beg != tokKeyword.end(); ++beg){
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
				stemListSet.insert(stem);

				paperVec[i].stemKeyword.insert(stem);
			}
		}


		//cout << "����Сд����ȥ���ദ��." << endl << endl;
		//cout << "���дʸɻ�ԭ." << endl << endl;
		//getchar();

		multimap<double, string> sortMap;
		for (unordered_map<string, int>::iterator it = paperVec[i].wordVec.begin(); it != paperVec[i].wordVec.end(); ++it){
			stemInfo stemTemp;
			double tempTf = ((double)(it->second)) / countWord;
			stemTemp.tf = tempTf;
			stemTemp.term = it->first;
			sortMap.insert(make_pair(tempTf, it->first));
			stemCount[it->first]++;
			paperVec[i].stemVec.push_back(stemTemp);
		}


		//for (multimap<double, string>::iterator it = sortMap.begin(); it != sortMap.end(); ++it)
		//	cout << it->second << ":" << it->first << endl;
		//cout << "�ܹ���" << sortMap.size() << " ����." << endl;
		//getchar();

		//unordered_map<string, int>::iterator iter;
		//for (iter = paperVec[i].wordVec.begin(); iter != paperVec[i].wordVec.end(); ++iter)
		//	cout << iter->first << ":" << iter->second << endl;
		//getchar();
	}

	copy(stemListSet.begin(), stemListSet.end(), back_inserter(stemList));
	//cout << stemList.size() << endl;
	cout << "�ܹ���" << stemCount.size() << "ά." << endl;

	//cout << "�ܹ���" << stemList.size() << "ά." << endl;
	//getchar();

	for (int i = 0; i < paperVec.size(); ++i){
		for (int j = 0; j < paperVec[i].stemVec.size(); ++j){
			paperVec[i].stemVec[j].idf = 1.0 / log(((double)paperVec.size() / (double)(stemCount[paperVec[i].stemVec[j].term])));
			paperVec[i].stemVec[j].tf_idf = paperVec[i].stemVec[j].tf * paperVec[i].stemVec[j].idf;

			double temp = paperVec[i].stemVec[j].tf_idf;
			set<string>::iterator iter;
			if ((iter = paperVec[i].stemTile.find(paperVec[i].stemVec[j].term)) != paperVec[i].stemTile.end())
				paperVec[i].stemVec[j].tf_idf = 1.5 * temp;

			if ((iter = paperVec[i].stemKeyword.find(paperVec[i].stemVec[j].term)) != paperVec[i].stemKeyword.end())
				paperVec[i].stemVec[j].tf_idf = 2.5 * temp;
		}

		sort(paperVec[i].stemVec.begin(), paperVec[i].stemVec.end(), compTFIDF);

		//for (int j = 0; j < paperVec[i].stemVec.size(); ++j){
		//	cout << paperVec[i].stemVec[j].term << ":" << paperVec[i].stemVec[j].tf_idf << endl;
		//}
		//getchar();
	}

	tfidf2vecMN();

}

void getMat(){
	cout << "Step3: ���tf_idf����." << endl;

	loadStopWords();
	stemmingFunc();
}