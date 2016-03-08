#include "Head.h"
#include "io.h"
#include <direct.h> 
#include "boost/tokenizer.hpp"

int countDoc = 0;
unordered_map<string, int> stemIdfCount;

//vector<set<string>> DocVec;

string path = "E:\\肖雪个人文档\\硕士毕业论文\\source\\citation-analysis\\citation-analysis\\data";
vector<string> files;

void getFiles(){
	long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	//cout << p.assign(path).append("\\*") << endl;
	//getchar();
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1){
		do{
			if ((fileinfo.attrib & _A_SUBDIR)){
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles();
			}else{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	//cout << files.size() << endl;
	for (int i = 0; i < files.size(); ++i){
		files[i].at(files[i].find_last_of('/')) = '\\';
	}
	//for (int i = 0; i < files.size(); ++i)
	//	cout << files[i] << endl;
	cout << "获得语料库信息..." << endl << endl;
}

void loadData(){

	for (auto i = 0; i < files.size(); ++i){
		ifstream inputCur;
		inputCur.open(files[i].c_str(), ios::binary);
		if (!inputCur.is_open()){
			cout << "Failed to open " << files[i] << " File." << endl;
		}
		
		string tempDe = "";
		string paper = "";
		getline(inputCur, tempDe);
		getline(inputCur, tempDe);
		
		printf("语料库构建中: %.2lf%%\r", i * 100.0 / files.size());

		while (!inputCur.eof()){
			getline(inputCur, tempDe);

			if (!tempDe.empty()){
				paper += (tempDe + " ");
			}
			else{
				//cout << paper << endl;
				//paper.clear();
				//getchar();
				set<string> stemDoc;
				boost::tokenizer<> tokTemp(paper);
				string stemTemp = "";
				for (boost::tokenizer<>::iterator beg = tokTemp.begin(); beg != tokTemp.end(); ++beg){
					stemTemp = *beg;
					transform(stemTemp.begin(), stemTemp.end(), stemTemp.begin(), ::tolower);

					wstring w(stemTemp.size(), ' ');
					copy(stemTemp.begin(), stemTemp.end(), w.begin());
					stemming::english_stem<> english_stemmer;
					english_stemmer(w);
					string stem(stemTemp.size(), ' ');
					copy(w.begin(), w.end(), stem.begin());
					stem = stem.substr(0, stem.find(' '));
					stemDoc.insert(stem);
					//cout << stem << endl;
					//getchar();
				}
				for (set<string>::iterator it = stemDoc.begin(); it != stemDoc.end(); ++it)
					stemIdfCount[*it]++;
				
				//DocVec.push_back(stemDoc);
				countDoc++;
				paper = "";
				continue;
			}
		}
		//cout << "第 " << i << " 个语料库完成读取..." << endl;
		//getchar();

		inputCur.close();
	}
	cout << "语料库共有：" << countDoc << " 篇文档..." << endl << endl << endl;
}

void loadCorpus(){
	
	getFiles();

	loadData();

}