#include "head.h"
void printSeqsData(seqsData input) 
{
		int size = input.size();
		for(int i = 0; i < size; i++) {
				vector<set<string> > seq = input[i];
				int seqSize = seq.size();
				for(int j = 0; j < seqSize; j++) {
						set<string> event = seq[j];
						int eventSize = event.size();
						//cout << "eventSize : " << eventSize << endl;
						if(eventSize > 1) {
								cout << "(";
						}
						for(set<string>::iterator it = event.begin(); it != event.end(); it++) {
								cout << *it; 
						}
						if(eventSize > 1) {
								cout << ")";
						}
				}
				cout << endl;
		}
}

int main(int argc, char* argv[]) {
		transactions trans;
		ifstream in(argv[1]);
        if(argc < 3) {
            cout << "shorter arguments" << endl;
            exit(0);
        }
        trans.setMTD(atoi(argv[2]));
        trans.setMinU(atof(argv[3]));
        int k = 1;
	    clock_t start = clock();
		trans.initialize(in);
        trans.run();
	    clock_t end = clock();
        cout << trans.getMTD() << ":" << trans.getMinU() << endl;
	    cout << "It takes " << ((double)end - start)/CLOCKS_PER_SEC/k << " seconds" << endl;
		//trans.mining1Episode();
		//trans.mining1Episode(trans.getEpisData());
		//printSeqsData(input);
		return 0;
}
