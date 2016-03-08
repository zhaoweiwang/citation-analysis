#include "Head.h"
#include <boost/tokenizer.hpp>

extern vector<paperInfo> paperVec;

extern int countDoc;
extern unordered_map<string, int> stemIdfCount;

set<string> stemListSet;
vector<string> stemList;
vector<string> stopWords;				//停用词集合

unordered_map<string, int> stemCount;	//stem的文档数

void loadStopWords()
{
	cout << endl << "3.1 首先获取停用词、介词等常用无效词词库..." << endl << endl;
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

	ofstream outTok("E:\\肖雪个人文档\\硕士毕业论文\\source\\citation-analysis\\citation-analysis\\数据结果\\token-paper.txt");
	ofstream outStem("E:\\肖雪个人文档\\硕士毕业论文\\source\\citation-analysis\\citation-analysis\\数据结果\\stem-paper.txt");
	cout << "3.2 进行小写化处理..." << endl;

	cout << endl << "3.3 对引文标题、摘要、关键词进行分词操作，提取词项（同时进行停用词过滤）..." << endl;

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
			stemTemp.tf = tempTf;
			stemTemp.term = it->first;
			sortMap.insert(make_pair(tempTf, it->first));
			//stemCount[it->first]++;
			paperVec[i].stemVec.push_back(stemTemp);
		}


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

	
	
	cout << endl << "3.4 进行词项词干提取操作..." << endl;

	cout << endl << "3.5 计算词项的相对TF值..." << endl;

	copy(stemListSet.begin(), stemListSet.end(), back_inserter(stemList));
	//cout << stemList.size() << endl;
	

	//cout << "总共：" << stemList.size() << "维." << endl;
	//getchar();
	cout << endl << "3.6 计算词项的TF-IDF值，并取前50名作为引文特征..." << endl;

	ofstream outStem25("E:\\肖雪个人文档\\硕士毕业论文\\source\\citation-analysis\\citation-analysis\\数据结果\\Stem50-paper.txt");
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
	//cout << endl << "3.6 向量空间总共有：" << stemCount.size() << "维..." << endl;
	tfidf2vecMN();

}

void getMat(){

	cout <<endl<<endl<< "第三步：计算TF_IDF进行引文特征提取..." << endl;

	loadStopWords();

	stemmingFunc();
}