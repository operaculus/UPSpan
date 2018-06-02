#include "head.h"
bool transactions::validateData() {
		int size = itemList.size();
        //cout << size << " " << externalUtility.size() << endl;
		if(size != externalUtility.size()) {
				return false;
		}
		set<string>::iterator it = itemList.begin();
		for(int i = 0; i < size; i++) {
			if(externalUtility.count(*it) != 1) {
				return false;
			}
			it++;
		}
		return true;
}
