#include "head.h"

double transactions::ewu(episodeMinOcc emo, episData projectDB) {
	vector<vector<string> > episode = emo.episode;
    list<minOcc> mos = emo.moSet;
    //为了计算一个精确一点的EWU，你要话费不少心思了；
    vector<string> lastElement = episode[episode.size() - 1];
    string lastEvent = lastElement[lastElement.size()-1];
    //实际的计算一个EWU发现现在的粗糙的方式，带来的更多是EWU的提高。并且没有Utiltiy的情况下，又是计算有误。
    double ewu = 0;
    for(list<minOcc>::iterator it = mos.begin(); it != mos.end(); it++) {
		minOcc mo =	*it;
		int start = mo.start;
		int end = mo.end;
		int mtdEnd = start + MTD;

        if(mtdEnd >= transSize) {
            mtdEnd = transSize;
        }

		for(int j = end; j< mtdEnd; j++) {
			map<string, int> simultEvent = projectDB[j]; //在计算的时候，通过判断此项为空来终止生成。应该有更好的方法
            //if(simultEvent.size() == 0) cout << "one "<< endl;
			for(map<string, int>::iterator it = simultEvent.begin(); it != simultEvent.end(); it++) {
                if(j == end && (it->first <= lastEvent )) { //大小符号出错。
                    continue;
                }
				ewu += externalUtility[it->first] * ( it->second );
			}
		}
	}
//    cout << "EWU:" << ewu + emo.utility << endl;
//    cout << emo.utility << endl;
//    cout << ewu << endl;
	return  (ewu + emo.utility) / ((double)totalU) ; //紧凑的上限 做了充分的工作
}

double transactions::ewuSerial(episodeMinOcc emo) {
	vector<vector<string> > episode = emo.episode;
    list<minOcc> mos = emo.moSet;
    //为了计算一个精确一点的EWU，你要话费不少心思了；
    vector<string> lastElement = episode[episode.size() - 1];
    string lastEvent = lastElement[lastElement.size()-1];
    //实际的计算一个EWU发现现在的粗糙的方式，带来的更多是EWU的提高。并且没有Utiltiy的情况下，又是计算有误。
	double ewu = 0;
    for(list<minOcc>::iterator it = mos.begin(); it != mos.end(); it++) {
		minOcc mo =	*it;
		int start = mo.start;
		int end = mo.end;
		int mtdEnd = start + MTD;

        if(mtdEnd >= transSize) {
            mtdEnd = transSize;
        }

		for(int j = end+1; j< mtdEnd; j++) {
			map<string, int> simultEvent = epis[j]; //在计算的时候，通过判断此项为空来终止生成。应该有更好的方法
            //if(simultEvent.size() == 0) cout << "one "<< endl;
			for(map<string, int>::iterator it = simultEvent.begin(); it != simultEvent.end(); it++) {
       //         if(j == end && (it->first <= lastEvent )) { //大小符号出错。
       //             continue;
       //         }
				ewu += externalUtility[it->first] * ( it->second );
			}
		}
	}
//    printEpisodeMinOcc(emo);
//    cout << "EWU:" << ewu + emo.utility << endl;
//    cout << emo.utility << endl;
//    cout << ewu << endl;
	return  (ewu + emo.utility) / ((double)totalU) ; //紧凑的上限 做了充分的工作
}

double transactions::ewu_old(episodeMinOcc emo) {
	vector<vector<string> > episode = emo.episode;
    list<minOcc> mos = emo.moSet;
    //为了计算一个精确一点的EWU，你要话费不少心思了；
    vector<string> lastElement = episode[episode.size() - 1];
    string lastEvent = lastElement[lastElement.size()-1];
    //实际的计算一个EWU发现现在的粗糙的方式，带来的更多是EWU的提高。并且没有Utiltiy的情况下，又是计算有误。
	double ewu = 0;
    for(list<minOcc>::iterator it = mos.begin(); it != mos.end(); it++) {
		minOcc mo =	*it;
		int start = mo.start;
		int end = mo.end;
		int mtdEnd = start + MTD;

        if(mtdEnd >= transSize) {
            mtdEnd = transSize;
        }

		for(int j = start; j< mtdEnd; j++) {
			map<string, int> simultEvent = epis[j]; //在计算的时候，通过判断此项为空来终止生成。应该有更好的方法(就是现在的直接使用原始数据)
            //if(simultEvent.size() == 0) cout << "one "<< endl;
			for(map<string, int>::iterator it = simultEvent.begin(); it != simultEvent.end(); it++) {
				ewu += externalUtility[it->first] * ( it->second );
			}
		}
	}
//    cout << "EWU:" << ewu + emo.utility << endl;
 //   cout << endl;
 //   cout << emo.utility << endl;
 //   cout << ewu << endl;
 //   cout << "end" << endl;
	return  (ewu + emo.utility) / ((double)totalU) ; //紧凑的上限 做了充分的工作
}

double transactions::ewu(episodeMinOcc emo) {
	vector<vector<string> > episode = emo.episode;
    list<minOcc> mos = emo.moSet;
    //为了计算一个精确一点的EWU，你要话费不少心思了；
    vector<string> lastElement = episode[episode.size() - 1];
    string lastEvent = lastElement[lastElement.size()-1];
    //实际的计算一个EWU发现现在的粗糙的方式，带来的更多是EWU的提高。并且没有Utiltiy的情况下，又是计算有误。
	double ewu = 0;
    for(list<minOcc>::iterator it = mos.begin(); it != mos.end(); it++) {
		minOcc mo =	*it;
		int start = mo.start;
		int end = mo.end;
		int mtdEnd = start + MTD;

        if(mtdEnd >= transSize) {
            mtdEnd = transSize;
        }

		for(int j = end; j< mtdEnd; j++) {
			map<string, int> simultEvent = epis[j]; //在计算的时候，通过判断此项为空来终止生成。应该有更好的方法(就是现在的直接使用原始数据)
            //if(simultEvent.size() == 0) cout << "one "<< endl;
			for(map<string, int>::iterator it = simultEvent.begin(); it != simultEvent.end(); it++) {
                if(j == end && (it->first <= lastEvent )) { //大小符号出错。
                    continue;
                }
				ewu += externalUtility[it->first] * ( it->second );
			}
		}
	}
//    cout << "EWU:" << ewu + emo.utility << endl;
 //   cout << endl;
 //   cout << emo.utility << endl;
 //   cout << ewu << endl;
 //   cout << "end" << endl;
	return  (ewu + emo.utility) / ((double)totalU) ; //紧凑的上限 做了充分的工作
}

double transactions::ewu_optimized(episodeMinOcc emo ) {
    //中间部分的event是处于第几个时间点无法计算，所以无法优化。 //从这个言论看出你还是没理解prefixSpan的具体过程。//另外一个问题是在映射database时，结果已经保证不会存在不良结果。计算的足够精简。
    //projected database 中计算ewu要继而增加原来的alpha的utility.
    //以上都是之前的做法，现在的优化方式 磊哥的最大化simult扩展；
    //分成更多的部分，也是serial的上限；
	vector<vector<string> > episode = emo.episode;
    list<minOcc> mos = emo.moSet;
    quickSort sort;

    vector<string> lastElement = episode[episode.size() - 1];
    string lastEvent = lastElement[lastElement.size()-1];

    vector<vector<double> > simultSpan;
    /*****************************
     * 潜在同时扩展项部分的提取；
     * ***************************/
    int maxSize = 0;
    for(list<minOcc>::iterator it = mos.begin(); it != mos.end(); it++) {
		minOcc mo =	*it;
        int end  = mo.end;
        map<string, int> simultEvent = epis[end];
        vector<double> span;
        for(map<string, int>::iterator it = simultEvent.begin(); it != simultEvent.end(); it++) {
            string event = it->first;
            if(event > lastEvent ) {
                span.push_back(it->second * externalUtility[event]);
            }
        }
        int spanSize = span.size();
//        for(int i = 0; i < spanSize; i++) {
//            cout <<"a" << span[i] << endl;
//        }
        sort.qsort(span, 0, spanSize - 1);
//        for(int i = 0; i < spanSize; i++) {
//            cout <<"b" <<span[i] << endl;
//        }
        if(spanSize > 0) {
            if(spanSize > maxSize) {
                maxSize = spanSize;
            }
            simultSpan.push_back(span);
        }
    }
    /***********************
     * 计算扩展项的紧上界
    * ********************/
    double simultBound = 0;
    //cout << maxSize << endl;
    for(int i = 1; i <= maxSize; i++) {
        double candidate = 0;
        for(vector<vector<double> >::iterator it = simultSpan.begin(); it != simultSpan.end(); it++){
            vector<double> uList = *it;
            //cout << "span size:" << uList.size() << endl;
            if(uList.size() >= i) { //已经有了判断。
                vector<double>::reverse_iterator start = uList.rbegin();
                for(int j = 0; j < i; j++) {
                    candidate += *start;
                    start++;
                }
            }
        }
        //cout << "candidate:" << candidate << endl;
        if(candidate > simultBound) {
            simultBound = candidate;
        }
    }

	double ewu = 0;
    for(list<minOcc>::iterator it = mos.begin(); it != mos.end(); it++) {
		minOcc mo =	*it;
		int start = mo.start;
        int end  = mo.end;

		int mtdEnd = start + MTD;

        if(mtdEnd >= transSize) {
            mtdEnd = transSize;
        }
		for(int j = end + 1; j< mtdEnd; j++) {
			map<string, int> simultEvent = epis[j];
			for(map<string, int>::iterator it = simultEvent.begin(); it != simultEvent.end(); it++) {
					ewu += externalUtility[it->first] * ( it->second );					
			}
		}
	}
  //  cout << endl;
//    printEpisodeMinOcc(emo);
//    cout << "optimized ewu:" << ewu << endl;
//    cout << "optimized utility:"<< emo.utility << " " << simultBound << endl;
	//cout << (ewu + emo.utility + simultBound) / ((double)totalU) << endl;
	return (ewu + emo.utility + simultBound) / ((double)totalU);
}


//Error exists. Deprecated
double transactions::utility(episodeMinOcc emo) {
    vector<vector<string> > episode = emo.episode;
    list<minOcc> mos = emo.moSet;
    double utility = 0;
	for(list<minOcc>::iterator it = mos.begin(); it!=mos.end(); it++) {
        minOcc mo = *it;
        int start = mo.start;
        int end = mo.end;
        // 之前程序确保了不会出现越界的错误。每个simultEent都是能够找到对应的episode的
        int epiSize = episode.size();
        for(int i = 0; i < epiSize; i++) {
            double localUtility = 0; 
            vector<string> simultEvent = episode[i];
            for(vector<string>::iterator itEvent = simultEvent.begin(); itEvent!=simultEvent.end(); itEvent++) {
                string event = *itEvent;
                while (epis[start].count(event) == 0) {  //写成while就连你自己都感觉奇怪(其实不奇怪，只是要到找对应的epis位置)。是为了从新计算一个utility 可惜放的地方不对。
                    // 上述的假设在某些情况下也是不成里的，特别是发现自己min occurrence 完全不争确的情况下
                    start++;  //最后更换utility的访问方式得到如何处理的情况。现在的做法明显启发式的不够精确，没有给每个元素的对应记录对应起来。
                    itEvent = simultEvent.begin(); //确保依次访问。
                    event = *itEvent;
                    localUtility = 0;
                }
                localUtility += epis[start][event] * externalUtility[event]; //怎么会越界呢？到时会有些不足的地方呢。
           }
           //cout << localUtility << endl;
           utility += localUtility;
        }
    }
    return utility;
}
