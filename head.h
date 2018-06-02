#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <list>
#include <map>

#include <algorithm>

#include <cstring>
#include <cstdlib>
//#define	minSup 3 

#define SHIFT 6
#define MASK 0x3f
//#define min_utility 0.3
//#define MTD 2

using namespace std;

class minOcc{
	public:
		int start;
		int end;
        double utility;
		minOcc(int s, int e, double u) {
            utility = u;
			start = s;
			end = e;
		}
        minOcc(){

        }

        int existCount(list<minOcc> mos) {
            int count = 0;
            for(list<minOcc>::iterator it = mos.begin(); it != mos.end(); it++) {
                if(it->start == this->start && it->end == this->end) {
                    count++;
                }
            }
            return count;
        }
};

class episodeMinOcc {
		public:
		vector<vector<string> > episode; // 不能使用set作为里层容器。此问题下存在顺序；
		list<minOcc> moSet;
        double utility; //本来也是应该在这里计算utility的。
        episodeMinOcc() {
            utility  = 0;
        }
};

class HUE {
    public:
		vector<vector<string> > episode; // 不能使用set作为里层容器。此问题下存在顺序；
		list<minOcc> moSet;
        double u;
        double ewu;
        HUE(vector<vector<string> > e, list<minOcc> mos, double utility) {
            episode = e;
            moSet = mos;
            u = utility;
        }
        HUE(vector<vector<string> > e, list<minOcc> mos, double utility, double ewuValue) {
            episode = e;
            moSet = mos;
            u = utility;
            ewu = ewuValue;
        }
};

typedef vector<vector<set<string> > > seqsData;
typedef vector<map<string, int> > episData;

/*
class alphaPB {
    public:
    int alphaU; //本来可以记录映射之后原来部分的alphaUtility；在映射之前计算似乎更自然。姑且在这里计算吧；// 如果在映射时计算，还是会产生大量的重复计算，所以原来的方式更好，虽然要每次迭代更新
    episData alphadb;
};
*/

class dataFormatConvert {
	public:
	episData seqs2Episode(seqsData seqs);
};

class transactions {

	int transSize;
    int MTD;
	double min_utility;
	seqsData seqs;
	episData epis;
    double totalU;
	set<string> itemList;
	map<string, double> externalUtility;
    vector<HUE> HUE_Set;

    //map<episodeMinOcc, int> HUE;

    int candidateNum;

	bool validateData();
	set<string> eventSplit(string str, string pattern);
	int itemListInitial();
	int utilityInitial(string utilities);
	seqsData readSeqsData(ifstream & in);
	episData readSyntheticData(ifstream & in);
	episData readRetailData(ifstream & in);
    episData readFoodMartData(ifstream& in);
	void printUtility(episodeMinOcc * occs);	
	void printUtility(vector<episodeMinOcc> occs);
	dataFormatConvert dataConvert;

	double ewu(episodeMinOcc emo, episData PB);
	double ewu(episodeMinOcc emo);
	double ewuSerial(episodeMinOcc emo);
    double ewu_old(episodeMinOcc emo);
    double ewu_optimized(episodeMinOcc emo);

    double utility(episodeMinOcc emo);
    episData project(episodeMinOcc alpha);
    int repair_moSetSimult(episodeMinOcc & beta, list<minOcc> alphaMos);
	public:
		int getSize() {
				return transSize;
		}
		int setSize(int size) {
				transSize = size;
		}

		episData getEpisData() {
				return epis;
		}

        void printEpisData(episData epis);

		int initialize(ifstream &in) {
//			seqs = readSeqsData(in);
//
//			if(validateData() != true) {
//					cout << "input dataset not correct in format" << endl;
//					exit(-1);
//			}
//			epis = dataConvert.seqs2Episode(seqs);
		        
         //       epis = readSyntheticData(in);
		        //epis = readRetailData(in);
                 epis = readFoodMartData(in);
                //printEpisData(epis);
		}

		int setMTD(int m) {
			MTD = m;
		}
		int getMTD() {
            return MTD;
        }
		int setMinU(double min) {
			min_utility = min;
            return 0;
		}
		double getMinU() {
            return min_utility;
        }

		set<string> episodeMining();
		set<string> episodeMining(episData epis);

		int mining1Episode();
		vector<episodeMinOcc> mining1Episode(episData epis);
        int run();
        int miningHUE(episodeMinOcc alpha);
        int miningSimultHUE(episodeMinOcc alpha);
        int miningSerialHUE(episodeMinOcc alpha);
		~transactions(){
		}
};

class quickSort {
    int swap(vector<double> &num, int i, int j)
    {
        double t = num[i];
        num[i] = num[j];
        num[j] = t;
        return 0;
    }
    
    int partition(vector<double>& num, int start, int end)
    {
        double pivot = num[end];
        int i = start - 1;
        for(int j = start; j < end; j++)
        {
            if(num[j] < pivot){
                i++;
                swap(num, i, j);
            }
        }
        swap(num, ++i, end);
        return i;
    }

   public: 
    int qsort( vector<double> & num, int start, int end)
    {
        int q;
        if(start < end) 
        {
    	q = partition(num, start, end);
        	qsort(num, start, q - 1);
        	qsort(num, q + 1, end);
        }
        return 0;
    }
};

string vector2String( vector<int> itemset);
string vector2String( vector<string> itemset);

void printEpisodeMinOcc(episodeMinOcc emo);
void printHUE(vector<HUE> HUE_Set);
