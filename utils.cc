#include "head.h"

string vector2String( vector<string> itemset){
	int size = itemset.size();
	string str;
	for(int i = 0; i < size; i++) {
		str.append(itemset[i]);
		str.append(" ");
	}
	return str;
}

void printEpisodeMinOcc(episodeMinOcc emo) {
    vector<vector<string> > episode = emo.episode;
    int epiSize = episode.size();
    for(int i = 0; i < epiSize; i++) {
        vector<string> element = episode[i];
        int elemSize = element.size();
        if( elemSize > 1)  {
            cout << "(";
        }
        for(int j = 0; j < elemSize; j++) {
            cout << element[j] ;
        }
        if(elemSize > 1) {
            cout << ")";
        }
    }
    cout << "\t";
    // ·Ö¸îepisode ÓëminOcc£»
    list<minOcc> mos = emo.moSet;
    for(list<minOcc>::iterator it = mos.begin(); it != mos.end(); it++) {
        minOcc cur = *it;
        cout << "{";  
        cout << cur.start << ", ";
        cout << cur.end<< ", ";
        cout << cur.utility ;
        cout << "} ";
    }
    cout << "U:" << emo.utility << endl;
}

void printHUE(vector<HUE> HUE_Set) {
    for(vector<HUE>::iterator it = HUE_Set.begin(); it != HUE_Set.end(); it++) {
        vector<vector<string> > episode = it->episode;
        int epiSize = episode.size();
        for(int i = 0; i < epiSize; i++) {
            vector<string> element = episode[i];
            int elemSize = element.size();
            if( elemSize > 1)  {
                cout << "(";
            }
            for(int j = 0; j < elemSize; j++) {
                cout << element[j] ;
            }
            if(elemSize > 1) {
                cout << ")";
            }
        }
        cout << "\t";
    
        list<minOcc> mos = it->moSet;
        for(list<minOcc>::iterator it1 = mos.begin(); it1 != mos.end(); it1++) {
            minOcc cur = *it1;
            cout << "{";  
            cout << cur.start << ", ";
            cout << cur.end << ", ";
            cout << cur.utility;
            cout << "} ";
        }
        cout << "\t";
    
        cout << it->u  << " " << it->ewu << endl;
    }
}
