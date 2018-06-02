#include "head.h"
void transactions::printEpisData(episData epis) {
    int i = 0;
    totalU = 0;
	for(vector<map<string, int> >::iterator it = epis.begin(); it != epis.end(); it++) {
		map<string, int> episode = *it;
        cout << i <<"\t:";
        double localUtility = 0;
		for(map<string, int>::iterator it = episode.begin(); it!= episode.end(); it++) {
			cout << it->first << " " << it->second << " ";
            localUtility += it->second * externalUtility[it->first];
		}
        i++;
		cout << " " << localUtility << endl;
        totalU += localUtility;
	}
    cout << "totalU =" << totalU << endl;
}
episData dataFormatConvert::seqs2Episode(seqsData seqs) {
		int size = seqs.size();
		vector<vector<set<string> > >::iterator it = seqs.begin();
		episData epis;
		for(int i = 0; i < size; i++) {
			vector<set<string> > seq = *it;
			map<string, int> epi;
			vector<set<string> >::iterator simulEventIt = seq.begin();
			int simulEventSize = seq.size();
			for(int j = 0; j < simulEventSize; j++) {
				set<string> simulEvent = *simulEventIt;
				for(set<string>::iterator eventIt = simulEvent.begin(); eventIt!=simulEvent.end(); eventIt++) {
					string event = *eventIt;
					if(epi.count(event) == 0) {
							epi.insert(make_pair(event, 1));
					} else {
							epi[event]++;
					}
				}
				simulEventIt++;
			}
			epis.push_back(epi);
			it++;
		}
		return epis;
}
