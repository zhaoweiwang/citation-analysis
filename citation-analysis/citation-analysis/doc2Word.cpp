//#include "Head.h"
//#include <boost/tokenizer.hpp>
//
//extern vector<paperInfo> paperVec;
//vector<string> stopWords;				//停用词集合
//
//unordered_map<string, int> stemCount;	//stem的文档数
//
//inline bool compTFIDF(const stemInfo &a, const stemInfo &b){
//	return a.tf_idf > b.tf_idf;
//}
//
//string str2Lower(string str)
//{
//	transform(str.begin(), str.end(), str.begin(), ::tolower);
//	return str;
//}
//
//void loadStopWords()
//{
//	cout << "获取停用词." << endl << endl;
//	ifstream in("stop_words.txt");
//	string tmp;
//	while (!in.eof()) {
//		getline(in, tmp, '\n');
//		stopWords.push_back(tmp);
//		tmp.clear();
//	}
//	std::sort(stopWords.begin(), stopWords.end());
//}
//
//void stemmingFunc(){
//	for (int i = 0; i < paperVec.size(); ++i){
//		//cout << paperVec[i].abstra << endl << endl;
//		//cout << "提取词条." << endl << endl;
//		boost::tokenizer<> tok(paperVec[i].abstra);
//		double countWord = 0.0;
//		for (boost::tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg){
//			countWord++;
//
//			string strTemp = str2Lower(*beg);
//			wstring w(strTemp.size(), ' ');
//			copy(strTemp.begin(), strTemp.end(), w.begin());
//			stemming::english_stem<> english_stemmer;
//			english_stemmer(w);
//			string stem(strTemp.size(), ' ');
//			copy(w.begin(), w.end(), stem.begin());
//			stem = stem.substr(0, stem.find(' '));
//			if (!(std::binary_search(stopWords.begin(), stopWords.end(), stem))){
//				paperVec[i].wordVec[stem]++;
//			}
//		}
//		
//		
//		//cout << "词条小写化、去冗余处理." << endl << endl;
//		//cout << "进行词干还原." << endl << endl;
//		//getchar();
//
//		multimap<double, string> sortMap;
//		for (unordered_map<string, int>::iterator it = paperVec[i].wordVec.begin(); it != paperVec[i].wordVec.end(); ++it){
//			stemInfo stemTemp;
//			double tempTf = ((double)(it->second)) / countWord;
//			stemTemp.tf = tempTf;
//			stemTemp.term = it->first;
//			sortMap.insert(make_pair(tempTf, it->first));
//			stemCount[it->first]++;
//			paperVec[i].stemVec.push_back(stemTemp);
//		}
//		
//
//		for (multimap<double, string>::iterator it = sortMap.begin(); it != sortMap.end(); ++it)
//			cout << it->second << ":" << it->first << endl;
//		cout << "总共：" << sortMap.size() << " 个词." << endl;
//		getchar();
//
//		//unordered_map<string, int>::iterator iter;
//		//for (iter = paperVec[i].wordVec.begin(); iter != paperVec[i].wordVec.end(); ++iter)
//		//	cout << iter->first << ":" << iter->second << endl;
//		//getchar();
//	}
//
//	cout << "总共：" << stemCount.size() << "维." << endl;
//	getchar();
//
//	for (int i = 0; i < paperVec.size(); ++i){
//		for (int j = 0; j < paperVec[i].stemVec.size(); ++j){
//			paperVec[i].stemVec[j].idf = 1.0 / log(((double)paperVec.size() / (double)(stemCount[paperVec[i].stemVec[j].term])));
//			paperVec[i].stemVec[j].tf_idf = paperVec[i].stemVec[j].tf * paperVec[i].stemVec[j].idf;
//		}
//
//		sort(paperVec[i].stemVec.begin(), paperVec[i].stemVec.end(), compTFIDF);
//
//		for (int j = 0; j < paperVec[i].stemVec.size(); ++j){
//			cout << paperVec[i].stemVec[j].term << ":" << paperVec[i].stemVec[j].tf_idf << endl;
//		}
//		getchar();
//	}
//
//
//}
//
//void doc2Word(){
//	loadStopWords();
//	stemmingFunc(); 
//}