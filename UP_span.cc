#include "head.h"
int transactions::run() {
/*******************************************
 Find all the associate 1-episode golbal event
 * *****************************************/
    candidateNum = 0;
    totalU = 10;
    vector<episodeMinOcc> oneEpisodes = mining1Episode(epis);
    int oneEpisodeSize = oneEpisodes.size();   
    //cout << oneEpisodeSize << endl;
    int u;
    // can't elinimate length-1 episode as sequential pattern mining
    for(int i = 0; i < oneEpisodeSize; i++) {
        episodeMinOcc candidate = oneEpisodes[i];
        //cout << ewu(candidate, project(candidate)) << endl;
        //cout << "EWU of " ;
        //printEpisodeMinOcc(candidate) ;
        //if(ewu(candidate, project(candidate)) >= min_utility){
        if(ewu_optimized(candidate) >= min_utility){
        //if(ewu_old(candidate) >= min_utility){
            //cout << ewu(candidate) << endl;
            //cout << ewu_optimized(candidate) << endl;
            candidateNum++;
            int u = candidate.utility;
            double value = u / (double)(totalU);
            //cout << value << endl;
            if( value > min_utility) {
            //if( (u = utility(candidate)) > min_utility) {
                HUE_Set.push_back(HUE(candidate.episode, candidate.moSet, u));
            }
            miningHUE(candidate);
        }
        //cout << "HUE size:" << HUE_Set.size() << "candidate Size" << candidateNum << endl;
    }
    cout << "HUE size:" << HUE_Set.size() << "candidate Size" << candidateNum << endl;
    //printHUE(HUE_Set);
}

int transactions::miningHUE(episodeMinOcc alpha) {
		miningSimultHUE(alpha);
        double ewuValue;
        if( (ewuValue = ewuSerial(alpha)) >= min_utility) {
		    miningSerialHUE(alpha);
        }
}
