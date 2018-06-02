#include "head.h"
episodeMinOcc serial_concat(episodeMinOcc alpha, string betaEvent) {
    // 在扩展的时候，occurrence自然会补全；
    episodeMinOcc beta;
    vector<vector<string> > episode =  alpha.episode;
    vector<string> lastElement;
    lastElement.push_back(betaEvent);
    episode.push_back(lastElement);
    beta.episode = episode;

    beta.utility = 0; // beta Utility的初始化还要在实际扩展moSet的时候的
    return beta;
}

bool updateMoSet(episodeMinOcc & beta, minOcc betaMo) {
    bool illegal = false;
    list<minOcc> moSet = beta.moSet;   //逻辑和实际的内存没有对应起来。使用整个对象时，知修改至能运行不对的
    for(list<minOcc>::iterator it =moSet.begin(); it != moSet.end();) {
        minOcc cur = *it;
        if(cur.start >= betaMo.start && cur.end <= betaMo.end){
            illegal = true;
            break;
            //contains min occ in the list; shall not insert;
        }else if(cur.start <= betaMo.start && cur.end >= betaMo.end) {
            //cout << "sdf" << endl;
            it = moSet.erase(it);
            beta.utility -= cur.utility;
        }else {
            it++;
        }
    }
    beta.moSet = moSet;

    if(!illegal) {
        beta.moSet.push_back(betaMo);
        beta.utility += betaMo.utility;
        return true;
    }
    return false;
}

int transactions::miningSerialHUE(episodeMinOcc alpha) {
    list<minOcc> mos = alpha.moSet;
    vector<vector<string> > alphaEpisode = alpha.episode;
    bool hook = false;

    candidateNum++;

    // moSet的记录仍然是 episodeMinOcc这样的二元组；序号用map单独记录。
    // map<vector<string>, int> betaupper;
    map<string, int> betaIndex;
    vector<episodeMinOcc> betaSet;
    int upper = -1; // 记录betaset的位置，放置多项mo；
    for(list<minOcc>::iterator it = mos.begin(); it != mos.end(); it++) {
        minOcc mo = *it;
        int start = mo.start;
        int end = mo.end;
        minOcc betaMo;
        betaMo.start = start;
        int serialStart = end + 1;
        int serialEnd = start + MTD;
        if(serialEnd > transSize) {
            serialEnd = transSize;
        }
        //直接的扩展，果真会引进大量的非minOcc，在MTD = 4的时候很容易； 
        //不长记性最不好，上次的错误在这次测试的时候还是遇到了的。
        for(int time = serialStart; time < serialEnd; time++) {
            map<string, int> NSE = epis[time];
            betaMo.end = time;
            for(map<string, int>::iterator itNSE = NSE.begin(); itNSE != NSE.end(); itNSE++) {
                // prefix span方式扩展，minOcc以此保障；
                string betaEvent = itNSE->first;
                betaMo.utility = mo.utility;
                if(betaIndex.count(betaEvent) == 0) {
                    episodeMinOcc beta = serial_concat(alpha, betaEvent);
                    betaMo.utility += itNSE->second * externalUtility[betaEvent];
                    //cout << vector2String(beta.episode[0]) << " " << mo.start << mo.end << endl;
                    beta.moSet.push_back(betaMo);
                    beta.utility += betaMo.utility;
                    upper++;
                    betaIndex.insert(make_pair(betaEvent, upper));
                    betaSet.push_back(beta);
                } else {
                    int index = betaIndex[betaEvent];
                    double oldU = betaMo.utility;
                    betaMo.utility += itNSE->second * externalUtility[betaEvent];
                    if(updateMoSet(betaSet[index], betaMo)) {
                        //if(alphaEpisode[0][0] == "f" && betaSet[index].episode[1][0] == "a") {
                        //cout << oldU <<" " << itNSE->second * externalUtility[betaEvent]<<"  " << start << time << endl;
                        //}
                    }
                }
            } //initialize beta's moSet
        }
    }

    int betaSize = betaIndex.size();
    //for(map<string, int>::iterator it = betaIndex.begin(); it != betaIndex.end(); it++){
    // add the potential extra set;
    for(int i = 0; i < betaSize; i++) {
        //本来单项的如果扩展 repair 会有飘逸成空项； 不扩展修改的情况下，已经将simult的情况全部包括。
        //printEpisodeMinOcc(betaSet[i]);
        if(betaSet[i].episode.size() == 1) {
            continue;
        }
        //repair_moSetSimult(betaSet[i], mos);
        //cout << "after repair" << endl;
        //printEpisodeMinOcc(betaSet[i]);   //打印部分，还包括了其他的打印在utils.cc中
        //cout << endl;
    }
    // 在使用map差重的时候，已经保证是扩展集中的event集合不重复。所以没有了在simultset中列举的麻烦。等价与直接在simultEent item set中进行。
    for(int i = 0; i < betaSize; i++) {
        episodeMinOcc candidate = betaSet[i];
        double ewuValue;
        //if( (ewuValue = ewu(candidate)) >= min_utility) {
        if( (ewuValue = ewu_optimized(candidate)) >= min_utility) {
        //if( (ewuValue = ewu_old(candidate)) >= min_utility) {
//        printEpisodeMinOcc(candidate);
//        cout << ewuValue ;
//        ewuValue = ewu_optimized(candidate);
//        cout << "optimized: "<<ewuValue << endl;
        //    cout << ewuValue;
           // cout << ewuValue << endl;
            double u = candidate.utility;
            double value = u / (double)(totalU); 
            if(value > min_utility) {
            //cout << "candidate: "<<candidate.utility << endl;
            //if((u = utility(candidate)) > min_utility) {
                HUE hue(candidate.episode, candidate.moSet, u, ewuValue);
                HUE_Set.push_back(hue); 
            }
            miningHUE(candidate);
        }
    }
}
