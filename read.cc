#include "head.h"
set<string> transactions::eventSplit(string str, string pattern) 
{
     std::string::size_type pos;
     std::set<std::string> result;
     str+=pattern;//扩展字符串以方便操作,这个扩展使得pos的值在最后一次匹配的时候是size的大小-1，i在被赋值后自动终止。
     int size=str.size();
 
     for(int i=0; i<size; i++)
     {
         pos=str.find(pattern,i);
         if(pos<size)
         {
             std::string s=str.substr(i,pos-i);
			 if(itemList.count(s) == 0){
				 itemList.insert(s);
			 }
             result.insert(s);
             i=pos+pattern.size()-1;
         }
     }
     return result;
}
   
int transactions::utilityInitial(string utilityList) {
		string::size_type pos;
		string::size_type colon;
		utilityList +=" ";
		int size = utilityList.size();
		for(int i = 0; i < size; i++) {
				pos = utilityList.find(" ", i);
				if(pos < size) {
						string s = utilityList.substr(i, pos-i);
						colon  = s.find(":");
						string item = s.substr(0, colon);
						string utility = s.substr(colon+1, s.size()-colon-1);
						double u = atof(utility.c_str());
                       // cout << item << " " << u << endl;
						externalUtility.insert(make_pair(item, u));
						i = pos + 1 - 1;
				}
		}
        //cout << externalUtility.size() << endl;
		return 0;
}


episData transactions::readRetailData(ifstream& in) {
	episData epis;
	string line;
	stringstream ss;
	map<string, int> epi;
    int max = 0;
	while(!in.eof()) {
		bool hasData = true;
		if(NULL != getline(in, line)) {
			//return seqs;
			ss << line;

            //cout << line << endl;
			//cout << line << endl;
			if(line.length() == 0 || line[0] == '@') {
					hasData = false;
					if(line[0]=='@') {
						string utilityList = line.substr(1, line.length()-1);
                        //cout << utilityList << endl;
						utilityInitial(utilityList);
					}
                    continue;
            }
			while(!ss.eof()) {
				string item;
				ss >> item;
                if(item == "") {
                    continue;
                }
                if(atoi(item.c_str())> max) {
                    max = atoi(item.c_str());
                }
                epi.insert(make_pair(item, rand()%5 + 1));
            }
            epis.push_back(epi);
            epi.clear();
			ss.str("");
			ss.clear();
        }
    }
    setSize(epis.size());
//    cout <<"max:" << max << endl;
    return epis;
}

episData transactions::readFoodMartData(ifstream& in) {
	episData epis;
    string line;
    stringstream ss;
    int max = 10;
    string lastCust="1-";
    set<string> dupSet;
    string product;
    string count;
	map<string, int> epi;
	while(!in.eof()) {
		bool hasData = true;
        if(NULL != getline(in, line)) {
			ss << line;
			if(line.length() == 0 || line[0] == '@') {
				hasData = false;
				if(line[0]=='@') {
					string utilityList = line.substr(1, line.length()-1);
                    //cout << utilityList << endl;
					utilityInitial(utilityList);
				}
                continue;
			}
         }

         while(!ss.eof()) {
			string customerId;
            string time;
			ss >> customerId;
            if(customerId != lastCust) {
                lastCust = customerId;
                epis.push_back(epi);
                epi.clear();
            }
            ss >> time;
            ss >> product;
            //if(max > atoi(product.c_str())) {
            //    max = atoi(product.c_str());
            //}
            ss >> count;
            int c = (int) atof(count.c_str());
            //cout<< c << endl;
            epi.insert(make_pair(product, c));
        }

    	ss.str("");
		ss.clear();
    }
    //cout << epis.size() << endl;
    //cout <<"max:" << max << endl;
    setSize(epis.size());
    return epis;
}

episData transactions::readSyntheticData(ifstream& in) {
	episData epis;
    string lastItem = "1";
	string line;
	stringstream ss;
	map<string, int> epi;
	while(!in.eof()) {
	//if(!in.eof()) {
		bool hasData = true;
		if(NULL != getline(in, line)) {
			//return seqs;
			ss << line;

            //cout << line << endl;
			//cout << line << endl;
			if(line.length() == 0 || line[0] == '@') {
					hasData = false;
					if(line[0]=='@') {
						string utilityList = line.substr(1, line.length()-1);
                        //cout << utilityList << endl;
						utilityInitial(utilityList);
					}
					break;
            }
			while(!ss.eof()) {
				string item;
                string itemNum;
				ss >> item;
                ss >> itemNum;
                ss >> item;
                if(item == "") {
                    continue;
                }
                if(itemNum == lastItem) {
	//				if(itemList.count(item) == 0){
	//					itemList.insert(item);
	//				}
                    epi.insert(make_pair(item, rand()%5 + 1));
                }
                if(itemNum != lastItem) {
                    lastItem = itemNum;
                    epis.push_back(epi);
                    epi.clear();
	//				if(itemList.count(item) == 0){
	//					 itemList.insert(item);
	//				}
                    epi.insert(make_pair(item, rand()%5 + 1));
                }
            }
			ss.str("");
			ss.clear();
        }
    }
    epis.push_back(epi);
    setSize(epis.size());
    return epis;
}

seqsData transactions::readSeqsData(ifstream& in)
{
	vector<vector<set<string> > > seqs;
	string line;
	stringstream ss;
	while(!in.eof()) {
			vector<set<string> > seq;
			bool hasData = true;
			if(NULL != getline(in, line)) {
					//return seqs;
					ss << line;
					//cout << line << endl;
					if(line.length() == 0 || line[0] == '@') {
							hasData = false;
							if(line[0]=='@') {
								string utilityList = line.substr(1, line.length()-1);
								utilityInitial(utilityList);
							}
							break;
					}
					while(!ss.eof()) {
						string item;
						set<string> event;
						ss >> item;
						if(item[0] == '(' && item[item.length() - 1] == ')') {
								string itemList = item.substr(1, item.length()-2);
								string pattern(",");
								event = eventSplit(itemList, pattern);
						} else {
								event.insert(item);
								 if(itemList.count(item) == 0){
									 itemList.insert(item);
								 }
						}
						seq.push_back(event);
					}
			}
			if(hasData == true) {
				seqs.push_back(seq);
			}
			ss.str("");
			ss.clear();
	}
	setSize(seqs.size());
	return seqs;
}
