#include "head.h"
episodeMinOcc simult_concat(episodeMinOcc alpha, string event) {
    episodeMinOcc beta;
    vector<vector<string> > episode =  alpha.episode;
    int size = episode.size();
    episode[size - 1].push_back(event);
    beta.episode = episode;
    beta.utility = 0; //每增加mo后添加新的元素。
    return beta;
}

int transactions::repair_moSetSimult(episodeMinOcc & beta, list<minOcc> alphaMos) {
    //05.28  现在骤然发现自己的repair在另外的serial扩展时已经做了。

    //扩展时，虽然匹配，也比须是在开始时刻之后。ERROR:只是针对最开始的简单
    //应该在倒数第一被匹配的元素的时间之后。如果在前面能够找的到，那么已经是更短的occurrence，不会被serial放置进来。
    //所有的潜在moset还是在未扩展的alpha的基础上
    list<minOcc> betaOcc = beta.moSet;
    vector<vector<string> > betaEpisode = beta.episode;
    int size = betaEpisode.size();
    vector<string> lastEvent = betaEpisode[size - 1];
    for(list<minOcc>::iterator it = alphaMos.begin(); it != alphaMos.end(); it++) {
        minOcc mo = *it;
        if( mo.existCount(betaOcc) == 1) {
            continue;
        } else {
            if(mo.existCount(betaOcc) > 1) {
                cout << "error" << endl;
            }
            int start = mo.start;
            int end = mo.end;
            int searchStart = end + 1; // 思考清楚
            if(searchStart >= transSize){
                continue; // 无法现有的基础上扩展
            }
            int searchEnd = start + MTD;
            if(searchEnd > transSize) {
                searchEnd = transSize;
            }
            for(int i = searchStart; i < searchEnd; i++) {
                bool hasOccurrence = true;
                map<string, int>simultEvent = epis[i];
                int lastEventSize = lastEvent.size();
                //cout << lastEventSize << endl;
                for( int j = 0; j < lastEventSize; j++) {
                    if(simultEvent.count(lastEvent[j]) == 0 ) {
                        //某个元素不存在，则说明这个lastEvent的occurrence不在
                        hasOccurrence = false;
                    }
                }
                if(hasOccurrence) {
                    //cout << "add extra occurrence" << endl;
                    //cout << vector2String(lastEvent) <<" " << start << " " << i << endl;
                    beta.moSet.push_back(minOcc(start, i, 0));
                    break; // 额外扩展搜寻多余的忽略, 也就是可以扩展，但是扩展范围是最大程度内，第一次的匹配。
               }
            }
        }
    }
    return 0;
}

int transactions::miningSimultHUE(episodeMinOcc alpha) {//, episData alphaPB) {
    candidateNum++;
    list<minOcc> mos = alpha.moSet;
    vector<vector<string> > alphaEpisode = alpha.episode;
    // 拼接的item需要在alpha之后，虽然在此此时是同时发生呢个，不必考虑。-》为了防止重复。比如一个元素的时候，这个现象最明显
    // 你在计划要单独处理，因为只要alpha中存在，再扩展则会丢掉前面的occurrence
    vector<string> lastElement = alphaEpisode[alphaEpisode.size() - 1];
    string lastEvent = lastElement[lastElement.size()-1];
    // moSet的记录仍然是 episodeMinOcc这样的二元组；序号用map单独记录。
    // map<vector<string>, int> betaupper;
    map<string, int> betaIndex;
    vector<episodeMinOcc> betaSet;
    int upper = -1;
    for(list<minOcc>::iterator it = mos.begin(); it != mos.end(); it++) {
        minOcc mo = *it;
        map<string, int> SE = epis[mo.end];
        for(map<string, int>::iterator itSE = SE.begin(); itSE != SE.end(); itSE++) {
            string betaEvent = itSE->first;

            if(lastEvent >= betaEvent) {
                continue; //虽然不是序列，靠字母顺序保证不重复。
            }  // project 之后也可能存在冗余, 所以必须判断才可扩展(s1 s2 e1 e2)；e2里面的元素已经被e1时填充满

            //cout << "OK"  << " " << betaEvent << endl;
            if( count(lastElement.begin(), lastElement.end(), betaEvent) == 0) {
                // 真正的simultaneous event set, 只是遍历一次，所以不必预处理
                // 会存在非最小的occuren出现在序列中吗？ 在simult的情况下不会。
                if(betaIndex.count(betaEvent) == 0) {
                    episodeMinOcc beta = simult_concat(alpha, betaEvent);
                    //cout << vector2String(beta.episode[0]) << " " << mo.start << mo.end << endl;
                    //mo.utility += itSE->second * externalUtility[betaEvent];  // 这种写法导致mo的值累加，在信的元素添加之后；
                    minOcc betaMo = mo;
                    betaMo.utility += itSE->second * externalUtility[betaEvent]; 
                    beta.moSet.push_back(betaMo);
                    beta.utility += betaMo.utility;
                    upper++;
                    betaIndex.insert(make_pair(betaEvent, upper));
                    betaSet.push_back(beta);
                } else {
                    int index = betaIndex[betaEvent];
                    minOcc betaMo = mo;
                    betaMo.utility += itSE->second * externalUtility[betaEvent];
                    betaSet[index].moSet.push_back(betaMo);
                    betaSet[index].utility += betaMo.utility;
                }
            }
        } // intialize beta's moSet
    }

    int betaSize = betaIndex.size();
//    // add the potential extra set;
//    for(int i = 0; i < betaSize; i++) {
//        //本来单项的如果扩展会有飘逸成空项； 不扩展修改的情况下，已经将simult的情况全部包括。
//        printEpisodeMinOcc(betaSet[i]);
//        if(betaSet[i].episode.size() == 1) {
//            continue;
//        }
//        repair_moSetSimult(betaSet[i], mos);   // miningSerial也有扩展到这里的可能，不过肯定会先放之前的重复了once的元素。
//        cout << "after repair" << endl;
//        printEpisodeMinOcc(betaSet[i]);   //打印部分，还包括了其他的打印在utils.cc中
//        //cout << endl;
//        return 2;
//    }

    // 在使用map差重的时候，已经保证是扩展集中的event集合不重复。所以没有了在simultset中列举的麻烦。等价与直接在simultEent item set中进行。
    
    for(int i = 0; i < betaSize; i++) {
        episodeMinOcc candidate = betaSet[i];
        double ewuValue ;
//        if( candidate.episode.size() == 2 && candidate.episode[1].size() == 2 && candidate.episode[0][0]=="a"  && candidate.episode[1][0]=="b"&& candidate.episode[1][1]=="c") {
//            printEpisodeMinOcc(candidate);
//        
//        ewuValue = ewu(candidate, project(candidate));
//        cout << ewuValue << "ewu" << endl;
//        }
        //if( (ewuValue = ewu(candidate)) >= min_utility) {
        if( (ewuValue = ewu_optimized(candidate)) >= min_utility) {
        //if( (ewuValue = ewu_old(candidate)) >= min_utility) {
            //cout << ewu(candidate) << endl;
            //exit(0);
           double u = candidate.utility;
           double value = u / (double)(totalU);
           //cout << value << endl;
            if( value> min_utility) {
                HUE hue(candidate.episode, candidate.moSet, u, ewuValue);
                HUE_Set.push_back(hue); 
            }
            miningHUE(candidate);
        }
    }
}
