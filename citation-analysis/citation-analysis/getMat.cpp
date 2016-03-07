#include "Head.h"
#include "boost/tokenizer.hpp"

extern vector<paperInfo> paperVec;
extern int countDoc;
extern unordered_map<string, int> stemIdfCount;
//extern vector<set<string>> DocVec;

set<string> stemListSet;
vector<string> stemList;
vector<string> stopWords;				//停用词集合

//unordered_map<string, int> stemCount;	//stem的文档数

void loadStopWords()
{
	cout << "获取停用词." << endl << endl;
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

	ofstream outTok("token-paper.txt");
	ofstream outStem("stem-paper.txt");


	//ofstream outCorpus("Corpus.txt");
	for (int i = 0; i < paperVec.size(); ++i){
		//cout << paperVec[i].abstra << endl << endl;
		//cout << "提取词条." << endl << endl;
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


		//cout << "词条小写化、去冗余处理." << endl << endl;
		//cout << "进行词干还原." << endl << endl;
		//getchar();

		multimap<double, string> sortMap;
		for (unordered_map<string, int>::iterator it = paperVec[i].wordVec.begin(); it != paperVec[i].wordVec.end(); ++it){
			stemInfo stemTemp;
			//double tempTf = ((double)(it->second)) / countWord;
			double tempTf = log10((double)(it->second)) + 1.0;
			//cout << it->first <<" " << it->second <<" "<< tempTf << endl;
			//getchar();
			stemTemp.tf = tempTf;
			stemTemp.term = it->first;
			sortMap.insert(make_pair(tempTf, it->first));
			//stemCount[it->first]++;
			paperVec[i].stemVec.push_back(stemTemp);
		}

		
		//printf("计算每个特征的IDF中: %.2lf%%\r", i * 100.0 / paperVec.size());
		//for (unordered_map<string, int>::iterator it = paperVec[i].wordVec.begin(); it != paperVec[i].wordVec.end(); ++it){
		//	
		//	int count_doc = 0;
		//	for (auto j = 0; j < DocVec.size(); ++j){
		//		
		//		if (DocVec[j].find(it->first) != DocVec[j].end())
		//			count_doc++;
		//	}
		//	if (count_doc == 0)
		//		count_doc = 1;
		//	stemCount[it->first] = count_doc;
		//	outCorpus << it->first << " " << stemCount[it->first] << endl;
		//	//cout << it->first << ": " << count_doc << endl;
		//	//getchar();
		//}


		//for (multimap<double, string>::iterator it = sortMap.begin(); it != sortMap.end(); ++it)
		//	cout << it->second << ":" << it->first << endl;
		//cout << "总共：" << sortMap.size() << " 个词." << endl;
		//getchar();

		//unordered_map<string, int>::iterator iter;
		//for (iter = paperVec[i].wordVec.begin(); iter != paperVec[i].wordVec.end(); ++iter)
		//	cout << iter->first << ":" << iter->second << endl;
		//getchar();
	}
	outTok.close();
	outStem.close();
	//outCorpus.close();
	cout << endl;

	copy(stemListSet.begin(), stemListSet.end(), back_inserter(stemList));
	//cout << stemList.size() << endl;
	//cout << "总共：" << stemCount.size() << "维." << endl;

	//cout << "总共：" << stemList.size() << "维." << endl;
	//getchar();

	for (int i = 0; i < paperVec.size(); ++i){
		for (int j = 0; j < paperVec[i].stemVec.size(); ++j){
			if (stemIdfCount[paperVec[i].stemVec[j].term] != 0)
				paperVec[i].stemVec[j].idf = (log10(((double)countDoc / (double)(stemIdfCount[paperVec[i].stemVec[j].term]))));
			else
				paperVec[i].stemVec[j].idf = (log10(((double)countDoc / (double)(1+stemIdfCount[paperVec[i].stemVec[j].term]))));
			//cout << paperVec[i].stemVec[j].term << " " << stemIdfCount[paperVec[i].stemVec[j].term] << " " << paperVec[i].stemVec[j].idf << endl;
			//getchar();
			paperVec[i].stemVec[j].tf_idf = paperVec[i].stemVec[j].tf * paperVec[i].stemVec[j].idf;

			double temp = paperVec[i].stemVec[j].tf_idf;

			paperVec[i].stemVec[j].tf_idf = 0.2 * temp;
			set<string>::iterator iter;
			if ((iter = paperVec[i].stemTile.find(paperVec[i].stemVec[j].term)) != paperVec[i].stemTile.end())
				paperVec[i].stemVec[j].tf_idf = 0.3 * temp;

			if ((iter = paperVec[i].stemKeyword.find(paperVec[i].stemVec[j].term)) != paperVec[i].stemKeyword.end())
				paperVec[i].stemVec[j].tf_idf = 0.5 * temp;

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
		//for (int j = 0; j < paperVec[i].stemVec.size(); ++j){
		//	cout << paperVec[i].stemVec[j].term << ":" << paperVec[i].stemVec[j].tf_idf << endl;
		//}
		//getchar();
	}
	tfidf2vecMN();

}

void getMat(){
	cout << "Step3: 获得tf_idf矩阵." << endl;

	loadStopWords();
	stemmingFunc();
}