#include "Head.h"
#include <iomanip>
extern vector<paperInfo> paperVec;

extern string inputFile;

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
	ofstream out(resultFile);

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
				out << paperVec[i].scan << " " << paperVec[paperVec[i].citeRidx[j]].scan << " " << setiosflags(ios::fixed) << setprecision(7) << calSimi(paperVec[i].dataMat, paperVec[paperVec[i].citeRidx[j]].dataMat) << endl;

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

	out.close();
}