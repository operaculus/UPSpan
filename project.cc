#include "head.h"
episData transactions::project(episodeMinOcc alpha) {
    //return epis;
    list<minOcc> mos = alpha.moSet;
    vector<vector<string> > alphaEpisode = alpha.episode;
    // vector map的方式在构造projectDB的时候现实出不足。
    episData projectDB;
    //vector<string> lastElement = alphaEpisode[alphaEpisode.size() - 1];
    //string lastEvent = lastElement[lastElement.size()-1];  //这里的截断的逻辑在哪里做？这里更合适？可是存在可能的重叠occ导致失效；
    for(list<minOcc>::iterator it = mos.begin(); it != mos.end(); it++) {
        minOcc mo = *it;
        int start = mo.start;
        int end = mo.end;
        int projectEnd = start + MTD;
        int transSize = getSize();
        //跟上次结果一样
        if(projectEnd > transSize) {
            projectEnd = transSize;
        }
        map<string, int> SE = epis[end];
        int dbSize = projectDB.size();
        if(dbSize < end) {
            // size = start 然后依次填充对应的episode 的值；
            int interval = end - dbSize;
            int i = 0;
            while(i < interval) {
                map<string, int> empty;
                projectDB.push_back(empty);
                i++;
            }
            for(int i = end; i < projectEnd; i++) {
                projectDB.push_back(epis[i]);
            }
        } else {
            for(int i = dbSize; i < projectEnd; i++) {
                projectDB.push_back(epis[i]);
            }
        }//  project中min_occurrence的在此体现 上一次映射的dbSize必然小于现在的projectEnd；
        
    }
    return projectDB;
}
