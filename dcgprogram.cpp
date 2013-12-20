#include <iostream>  //stream IO
#include <fstream>   //file IO
#include <string>    //strings
#include <sstream> //stringstreams for converting data.
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <map>

using namespace std;


//--------------------------------------------------------
// NAME		      : Noel Ganotisi and Ian Armit
// STUDENT NUMBER : 6721898
// COURSE		  : COMP4710
// INSTRUCTOR	  : Carson K. Leung
//
// REMARKS:
//
// INPUT:
// A simple file of text
//
// OUTPUT:
//
//


int calculate_tmvT(const char *s)
{
	string str = s;
	string substr;
	int tmv = 0;
	unsigned found = str.find_last_of("\t");
	substr = str.substr(found+1);
	for(int j=0; j<substr.size(); j++){
		if(substr.compare(j,1, " ") != 0)
			tmv += atoi(&substr.at(j));

	}
	return tmv;
}

//given a string that starts with an item in the form "A:12 ..." finds the count (12)
//...specifically for if the count is more than one character.
int find_count(string transaction) {
	int first_space = transaction.find_first_of(' ');
	return atoi(transaction.substr(0,first_space).c_str());
}
//**************************************************************
//**************************M A I N*****************************
//**************************************************************

//Main here opens a file and reads individual characters
//int main(void) {
int main(int argc, char* argv[]) {

	string fileName;   //name of the desired input file
	char xcts[256];
	int xctcount = 0;
	int tmv = 0;
	int num = 0;
	float minShare;
	int tmv_total = 0;
	int min_lmv = 0;
	int lmv = 0;
	map<string, int> candidates;
	map<string, int> next_can; 
	map<string, int> tmv_map;
	string str;

	if (argc < 3) {
        cerr << "Usage: " << argv[0] << "--FILENAME MINSHARE" << endl;
        return 1;
    }

	fileName = argv[1];
	minShare = atof(argv[2]);

	//open the file
	ifstream dataFile(fileName.c_str());

	if(dataFile.is_open()){
		dataFile.getline(xcts,256);

	}
	else {
		cout << "File does not exist." <<endl;
		return 0;
	}

	xctcount = atoi(xcts);		//transaction count

	int tmvxcts[xctcount]; 		//array that stores TMV for each transaction
	int total_tmv = 0;
	for (int i=0; i<xctcount; i++) {
		dataFile.getline(xcts, 256);
		tmvxcts[i] = calculate_tmvT(xcts);
		total_tmv += tmvxcts[i];

		cout << "tmv of transaction " << i+1 <<": "<< tmvxcts[i] << "\n";
	}

	min_lmv = ceil(minShare * total_tmv);  //rounds up min_lmv
	
	cout << "Total tmv: " << total_tmv << " min_lmv: " << min_lmv << "\n";

	
	dataFile.close();
	dataFile.open(fileName.c_str());
	dataFile.ignore(256,'\n');

	for (int k = 1; k < 11; k++) {
		for(int i=0; i<xctcount; i++){

			dataFile.getline(xcts, 256);
			
			string transaction = xcts;
			if (k==1) {
				for(int	j= 1; j < transaction.size(); j++) {
					if ( isupper(transaction.at(j))) {  //found a transaction item
						string current_item = transaction.substr(j,1);
						if (candidates.find(current_item) == candidates.end() ) {
							//not in map yet...create it
							candidates[current_item] = find_count(transaction.substr(j+2));
						} else {
							//is already in map... add to it
							candidates[current_item] += find_count(transaction.substr(j+2));
						}
						//find transactions for k+1
						string rem_trans = transaction.substr(j+2);
						for (int l = 0; l < rem_trans.size(); l++) {
							if ( isupper(rem_trans.at(l))) {  //found a transaction item
								if (tmv_map.find(current_item + rem_trans.substr(l,1)) == tmv_map.end() ) {
									//not found make...
									tmv_map[current_item + rem_trans.substr(l,1)] = tmvxcts[i];
								} else {
									tmv_map[current_item + rem_trans.substr(l,1)] += tmvxcts[i];
								}
							}
						}
					}
				}
			} else {
				for( map<string, int>::iterator ii=candidates.begin(); ii!=candidates.end(); ++ii) {
					int running_count = 0;
					bool all_found = true;
					for(int l = 0; l < (*ii).first.size(); l++) {
						bool found = false;
						for (int j = 1; j < transaction.size(); j++) {
							if (isupper(transaction.at(j)) && transaction.at(j) == (*ii).first.at(l)) {
								found = true;
								running_count += find_count(transaction.substr(j+2));
								break;
							} 	
						}
						if (!found) {
							all_found = false;
							break;
						}
					}
					if (all_found) {
						candidates[(*ii).first] += running_count;
						
						int start_pos = transaction.find(*((*ii).first).rbegin()); //start after the last character in key
						if (start_pos == string::npos) { break; }	
						//check to see if tmv needs to be added to at this point.
						for (int j = start_pos; j < transaction.size(); j++) {
							if(isupper(transaction.at(j)) && (*ii).first.find(transaction.at(j)) == string::npos) {
								cout << "For " << (*ii).first << " we found a: " << transaction.at(j) << "\n";
								if (tmv_map.find((*ii).first + transaction.substr(j,1)) == tmv_map.end() ) {
									//not found make...
									cout << "\n\nHERE\n\n";
									tmv_map[(*ii).first + transaction.substr(j,1)] = tmvxcts[i];
								} else {
									cout << "\n\nDAEWFDS\n\n";
									tmv_map[(*ii).first + transaction.substr(j,1)] += tmvxcts[i];
								}
							}
						}
					}
				}
			}
		
		}


		//iterates through entire hashmap and prints out contents
		for( map<string, int>::iterator ii=candidates.begin(); ii!=candidates.end(); ++ii) {
			cout << (*ii).first << ": " << (*ii).second << "\n";
		}

		//iterates through entire hashmap and prints out contents
		for( map<string, int>::iterator ii=tmv_map.begin(); ii!=tmv_map.end(); ++ii) {
		
			cout << (*ii).first << ": " << (*ii).second << "\n";
			if ((*ii).second >= min_lmv) {
				next_can[(*ii).first] = 0;	
			}
		}

		for( map<string, int>::iterator ii=next_can.begin(); ii!=next_can.end(); ++ii) {
			cout << (*ii).first << ": " << (*ii).second << "\n";
		}

		if (next_can.empty()) {
			break;
		}
		candidates = next_can;
		next_can.clear();
		tmv_map.clear();
	
		dataFile.close();
		dataFile.open(fileName.c_str());
		dataFile.ignore(256,'\n');

	}	
	
	dataFile.close();

  	return(1);
}
