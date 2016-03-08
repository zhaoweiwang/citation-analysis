#include "Head.h"
#include <boost/tokenizer.hpp>

extern vector<paperInfo> paperVec;

extern int countDoc;
extern unordered_map<string, int> stemIdfCount;

set<string> stemListSet;
vector<string> stemList;
vector<string> stopWords;				//ͣ�ôʼ���

unordered_map<string, int> stemCount;	//stem���ĵ���

void loadStopWords()
{
	cout << endl << "3.1 ���Ȼ�ȡͣ�ôʡ���ʵȳ�����Ч�ʴʿ�..." << endl << endl;
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

	ofstream outTok("E:\\Фѩ�����ĵ�\\˶ʿ��ҵ����\\source\\citation-analysis\\citation-analysis\\���ݽ��\\token-paper.txt");
	ofstream outStem("E:\\Фѩ�����ĵ�\\˶ʿ��ҵ����\\source\\citation-analysis\\citation-analysis\\���ݽ��\\stem-paper.txt");
	cout << "3.2 ����Сд������..." << endl;

	cout << endl << "3.3 �����ı��⡢ժҪ���ؼ��ʽ��зִʲ�������ȡ���ͬʱ����ͣ�ôʹ��ˣ�..." << endl;

	for (int i = 0; i < paperVec.size(); ++i){
		//cout << paperVec[i].abstra << endl << endl;
		//cout << "��ȡ����." << endl << endl;
		boost::tokenizer<> tok(paperVec[i].abstra);

		boost::tokenizer<> tokTitle(paperVec[i].title);
		boost::tokenizer<> tokKeyword(paperVec[i].originalKeywords);

		//2016-3-3
 
		double countWord = 0.0;
		outTok << "Title: " << paperVec[i].title << endl;
		outStem << "Title: " << paperVec[i].title << endl;
		outTok << "token:";
		outStem << "stem:";

		for (boost::tokenizer<>::iterator beg = tokTitle.begin(); beg != tokTitle.end(); ++beg){
			countWord++;

			string strTemp = str2Lower(*beg);

			if (!(std::binary_search(stopWords.begin(), stopWords.end(), strTemp))){
				outTok << " " << strTemp;
			}

			wstring w(strTemp.size(), ' ');
			copy(strTemp.begin(), strTemp.end(), w.begin());
			stemming::english_stem<> english_stemmer;
			english_stemmer(w);
			string stem(strTemp.size(), ' ');
			copy(w.begin(), w.end(), stem.begin());
			stem = stem.substr(0, stem.find(' '));
			if (!(std::binary_search(stopWords.begin(), stopWords.end(), stem))){
				if (stem.length() > 5){
					paperVec[i].wordVec[stem]++;
					stemListSet.insert(stem);

					paperVec[i].stemTile.insert(stem);


					outStem << " " << stem;
				}

			}
		}


		outTok << endl << "Keywords: " << paperVec[i].originalKeywords << endl;
		outStem << endl << "Keywords: " << paperVec[i].originalKeywords << endl;
		outTok << "token:";
		outStem << "stem:";

		for (boost::tokenizer<>::iterator beg = tokKeyword.begin(); beg != tokKeyword.end(); ++beg){
			countWord++;

			string strTemp = str2Lower(*beg);

			if (!(std::binary_search(stopWords.begin(), stopWords.end(), strTemp))){
				outTok << " " << strTemp;
			}

			wstring w(strTemp.size(), ' ');
			copy(strTemp.begin(), strTemp.end(), w.begin());
			stemming::english_stem<> english_stemmer;
			english_stemmer(w);
			string stem(strTemp.size(), ' ');
			copy(w.begin(), w.end(), stem.begin());
			stem = stem.substr(0, stem.find(' '));
			if (!(std::binary_search(stopWords.begin(), stopWords.end(), stem))){
				if (stem.length() > 5){
					paperVec[i].wordVec[stem]++;
					stemListSet.insert(stem);

					paperVec[i].stemKeyword.insert(stem);

					outStem << " " << stem;
				}
			}
		}



		outTok << endl << "Abstract: " << paperVec[i].abstra << endl;
		outStem << endl << "Abstract: " << paperVec[i].abstra << endl;
		outTok << "token:";
		outStem << "stem:";

		for (boost::tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg){
			countWord++;

			string strTemp = str2Lower(*beg);

			if (!(std::binary_search(stopWords.begin(), stopWords.end(), strTemp))){
				outTok << " " << strTemp;
			}

			wstring w(strTemp.size(), ' ');
			copy(strTemp.begin(), strTemp.end(), w.begin());
			stemming::english_stem<> english_stemmer;
			english_stemmer(w);
			string stem(strTemp.size(), ' ');
			copy(w.begin(), w.end(), stem.begin());
			stem = stem.substr(0, stem.find(' '));
			if (!(std::binary_search(stopWords.begin(), stopWords.end(), stem))){
				if (stem.length() > 5){
					paperVec[i].wordVec[stem]++;
					stemListSet.insert(stem);

					outStem << " " << stem;
				}
			}
		}



		outStem << endl;
		outTok << endl;


		//cout << "����Сд����ȥ���ദ��." << endl << endl;
		//cout << "���дʸɻ�ԭ." << endl << endl;
		//getchar();

		multimap<double, string> sortMap;
		for (unordered_map<string, int>::iterator it = paperVec[i].wordVec.begin(); it != paperVec[i].wordVec.end(); ++it){
			stemInfo stemTemp;
			//double tempTf = ((double)(it->second)) / countWord;
			double tempTf = log10((double)(it->second)) + 1.0;
			stemTemp.tf = tempTf;
			stemTemp.term = it->first;
			sortMap.insert(make_pair(tempTf, it->first));
			//stemCount[it->first]++;
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
	outTok.close();
	outStem.close();

	
	
	cout << endl << "3.4 ���д���ʸ���ȡ����..." << endl;

	cout << endl << "3.5 �����������TFֵ..." << endl;

	copy(stemListSet.begin(), stemListSet.end(), back_inserter(stemList));
	//cout << stemList.size() << endl;
	

	//cout << "�ܹ���" << stemList.size() << "ά." << endl;
	//getchar();
	cout << endl << "3.6 ��������TF-IDFֵ����ȡǰ50����Ϊ��������..." << endl;

	ofstream outStem25("E:\\Фѩ�����ĵ�\\˶ʿ��ҵ����\\source\\citation-analysis\\citation-analysis\\���ݽ��\\Stem50-paper.txt");
	for (int i = 0; i < paperVec.size(); ++i){
		for (int j = 0; j < paperVec[i].stemVec.size(); ++j){

			if (stemIdfCount[paperVec[i].stemVec[j].term] != 0)
				paperVec[i].stemVec[j].idf = (log10(((double)countDoc / (double)(stemIdfCount[paperVec[i].stemVec[j].term]))));
			else
				paperVec[i].stemVec[j].idf = (log10(((double)countDoc / (double)(1 + stemIdfCount[paperVec[i].stemVec[j].term]))));

			//paperVec[i].stemVec[j].idf = 1 / log(((double)paperVec.size() / (double)(stemCount[paperVec[i].stemVec[j].term])));
			paperVec[i].stemVec[j].tf_idf = paperVec[i].stemVec[j].tf * paperVec[i].stemVec[j].idf;

			double temp = paperVec[i].stemVec[j].tf_idf;
			paperVec[i].stemVec[j].tf_idf = 1 * temp;
			set<string>::iterator iter;
			if ((iter = paperVec[i].stemTile.find(paperVec[i].stemVec[j].term)) != paperVec[i].stemTile.end())
				paperVec[i].stemVec[j].tf_idf = 1.5 * temp;

			if ((iter = paperVec[i].stemKeyword.find(paperVec[i].stemVec[j].term)) != paperVec[i].stemKeyword.end())
				paperVec[i].stemVec[j].tf_idf = 2.5 * temp;
		}

		sort(paperVec[i].stemVec.begin(), paperVec[i].stemVec.end(), compTFIDF);

		int Top = 50;
		int count = 0;
		vector<stemInfo>::iterator iter = paperVec[i].stemVec.begin();
		while (iter != paperVec[i].stemVec.end()){
			count++;
			if (count <= Top)
				iter++;
			else
				iter = paperVec[i].stemVec.erase(iter);
		}

		
		//cout << paperVec[i].stemVec.size() << endl;
		outStem25 << "Title: " << paperVec[i].title << endl;
		outStem25 << "Stem_Top25\ttf_idf" << endl;
		for (int j = 0; j < paperVec[i].stemVec.size(); ++j){
			outStem25 << paperVec[i].stemVec[j].term << "\t" << paperVec[i].stemVec[j].tf_idf << endl;
		}
		//getchar();
	}
	outStem25.close();
	//cout << endl << "3.6 �����ռ��ܹ��У�" << stemCount.size() << "ά..." << endl;
	tfidf2vecMN();

}

void getMat(){

	cout <<endl<<endl<< "������������TF_IDF��������������ȡ..." << endl;

	loadStopWords();

	stemmingFunc();
}