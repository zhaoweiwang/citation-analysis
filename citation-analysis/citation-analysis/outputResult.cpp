#include "Head.h"
#include <iomanip>
extern vector<paperInfo> paperVec;

extern string inputFile;

unordered_map<string, int> cheackTable;

double calSimi(vector<double> &v1, vector<double> &v2){
	double d1 = 0.0, d2 = 0.0, d3 = 0.0;
	unsigned int len = v1.size();
	for (unsigned int i = 0; i < len; ++i){
		d1 += (v1[i] * v2[i]);
		d2 += (v1[i] * v1[i]);
		d3 += (v2[i] * v2[i]);
	}
	//cout << d1 << " " << d2 << " " << d3 << endl;
	//cout << d1 / (sqrt(d2) * sqrt(d3)) << endl;
	//getchar();
	return d1 / (sqrt(d2) * sqrt(d3));
}

double calVector(vector<double> &a){
	double result = 0.0;
	for (unsigned int i = 0; i < a.size(); ++i)
		result += (a[i] * a[i]);
	return result;
}

void outputResult(){
	string resultFile = inputFile.substr(0, inputFile.find_last_of('.')) + "-result.txt";
	ofstream out(resultFile.c_str());

	int countScan = 0;
	int countEdge = 0;
	for (auto i = 0; i < paperVec.size(); ++i){
		if (paperVec[i].citeFlag){
			paperVec[i].scan = ++countScan;
			if (!paperVec[i].citeRidx.empty())
				countEdge += paperVec[i].citeRidx.size();
		}
	}

	out << "*Vertices " << countScan << endl;
	for (auto i = 0; i < paperVec.size(); ++i){
		if (paperVec[i].citeFlag)
			out << paperVec[i].scan << " " <<  "\"" << paperVec[i].title << "\"" << endl;
	}

	out << "*Edges " << countEdge << endl;
	for (auto i = 0; i < paperVec.size(); ++i){
		if (!paperVec[i].citeRidx.empty()){
			for (auto j = 0; j < paperVec[i].citeRidx.size(); ++j){
				out << paperVec[i].scan << " " << paperVec[paperVec[i].citeRidx[j]].scan << " " << setiosflags(ios::fixed) << setprecision(14) << calSimi(paperVec[i].dataMat, paperVec[paperVec[i].citeRidx[j]].dataMat) << endl;

				string temp1 = paperVec[i].title + paperVec[paperVec[i].citeRidx[j]].title;
				string temp2 = paperVec[paperVec[i].citeRidx[j]].title + paperVec[i].title;
				cheackTable[temp1] = 2;
				cheackTable[temp2] = 2;
				//paperVec[i].trueCiteFlag = true;
				//paperVec[paperVec[i].citeRidx[j]].trueCiteFlag = true;

				if (calVector(paperVec[paperVec[i].citeRidx[j]].dataMat) == 0.0){
					cout << calVector(paperVec[i].dataMat) << endl;
					cout << paperVec[paperVec[i].citeRidx[j]].stemVec.size() << endl;
					cout << paperVec[paperVec[i].citeRidx[j]].title << endl;
					cout << paperVec[paperVec[i].citeRidx[j]].abstra << endl;
					//for (int i )
					getchar();
					
				}
			}
		}
	}


	out << "===========耦合情况===========" << endl;
	//耦合情况输出
	for (auto i = 0; i < paperVec.size(); ++i){
		for (auto j = 0; j < paperVec[i].citeRidx.size(); ++j){
			for (auto k = i+1; k < paperVec.size(); ++k){
				if (k == i)
					continue;
				else{
					if (!paperVec[k].citeRidx.empty()){
						for (auto t = 0; t < paperVec[k].citeRidx.size(); ++t){
							if (paperVec[paperVec[i].citeRidx[j]].title == paperVec[paperVec[k].citeRidx[t]].title){
								string temp = paperVec[i].title + paperVec[k].title;
								if (cheackTable[temp] == 2) break;
								if (calSimi(paperVec[i].dataMat, paperVec[k].dataMat) - 0.3 > 0){
									out << paperVec[i].scan << " " << paperVec[k].scan << " " << setiosflags(ios::fixed) << setprecision(7) << calSimi(paperVec[i].dataMat, paperVec[k].dataMat) << endl;
								}
								break;
							}
						}
					}
				}
			}
		}
	}

	out.close();
}