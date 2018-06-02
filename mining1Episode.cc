#include "head.h"
void transactions::printUtility(episodeMinOcc* occs){
// oneEpisode Utility
	int oneEpisodeSize = itemList.size();
	for(int i = 0; i < oneEpisodeSize; i++) {
			episodeMinOcc mo = occs[i];
			string name = mo.episode[0][0];
			cout << name << ": ";
			list<minOcc> moSet = mo.moSet;
			int internalUtility = moSet.size();
			//cout << internalUtility << endl;
			double externalU = externalUtility.find(name)->second;
			cout << moSet.size() * externalU << endl;
	}
}
int transactions::mining1Episode()
{		
		int transSize = getSize();
		int oneEpisodeSize = itemList.size();
		set<string>::iterator itItem = itemList.begin();

		episodeMinOcc* oneEpisodeOccs = new episodeMinOcc[oneEpisodeSize];
		for(int e = 0; e < oneEpisodeSize; e++) {
			string eventItem = *itItem;
			vector<string> eventSet;
			eventSet.push_back(eventItem);
			oneEpisodeOccs[e].episode.push_back(eventSet);

			list<minOcc> mos;
			vector<vector<set<string> > >::iterator it = seqs.begin();
			
			for(int i = 0; i < transSize; i++) {
					vector<set<string> > simulEvent = *it;
					for(vector<set<string> >::iterator itEvent = simulEvent.begin(); itEvent != simulEvent.end(); itEvent++) {
							set<string> event = *itEvent;
							for(set<string>:: iterator itSetItem = event.begin(); itSetItem != event.end(); itSetItem++) {
									if(*itSetItem ==eventItem ) {
											mos.push_back(minOcc(i, i, 0));
									}
							}
					}
					it++;
			}
			oneEpisodeOccs[e].moSet = mos;
			itItem++;
		}
		printUtility(oneEpisodeOccs);
		return 0;
}

void transactions::printUtility(vector<episodeMinOcc> occs){
		int oneEpisodeSize = itemList.size();
		for(int i = 0; i < oneEpisodeSize; i++) {
			episodeMinOcc emo =	occs[i];
			cout << emo.episode[0][0] << " ";
			string event = emo.episode[0][0];
			list<minOcc> mos = emo.moSet;
			int internalUtility = 0;
			for(list<minOcc>::iterator it = mos.begin(); it!=mos.end(); it++) {
					minOcc mo = *it;
					int time = mo.start;
					int c = epis[time][event];
					internalUtility += c;
					//cout << internalUtility << endl;
			}
			cout << externalUtility[event] * internalUtility << endl;
		}
}

vector<episodeMinOcc> transactions::mining1Episode(episData epis) {
	int episSize = epis.size();
	vector<episodeMinOcc> oneEpisodes;

    double totalUtility = 0;
    double localUtility = 0;
    map<string, int> eventIndex;
    int upper = -1;

   	for(int j = 0; j < episSize; j++) {
   		map<string, int> simulEvent = epis[j];
   		for(map<string, int>::iterator it = simulEvent.begin(); it != simulEvent.end(); it++) {
            string event = it->first;
   			if(eventIndex.count(event) == 0) {
               upper++;
               eventIndex.insert(make_pair(event, upper));

               localUtility = it->second * externalUtility[event];
	           episodeMinOcc emo;
	           vector<string> eventSet;
    		   eventSet.push_back(event);
    		   emo.episode.push_back(eventSet);
               emo.moSet.push_back(minOcc(j,j,localUtility));
               emo.utility += localUtility;
               oneEpisodes.push_back(emo);
   			} else {
               int index = eventIndex[event];
               localUtility = it->second * externalUtility[event];
			   oneEpisodes[index].utility += localUtility; 
			   oneEpisodes[index].moSet.push_back(minOcc(j,j,localUtility));
            }
   		}
   	}

    int oneEpisodeSize = eventIndex.size();
    //cout << oneEpisodeSize << endl;
    for(int i = 0; i < oneEpisodeSize; i++) {
        //printEpisodeMinOcc(oneEpisodes[i]);
        //cout << oneEpisodes[i].utility << endl;
        
        totalUtility += oneEpisodes[i].utility;
    }
    totalU = totalUtility;
    //cout << "total utility: " <<totalUtility << endl;

	//printUtility(oneEpisodeOccs);
    return oneEpisodes;
}
