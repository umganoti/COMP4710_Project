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

void insert_to_map(map<string, int> &aMap, string key, int value){
	if (aMap.find(key) == aMap.end() ) {
		//not in map yet...create it
		aMap[key] = value;
	} else {
		//is already in map... add to it
		aMap[key] += value;
	}
}
//iterates through entire hashmap and prints out contents
void print_map(map<string, int> &aMap){
	for( map<string, int>::iterator ii=aMap.begin(); ii!=aMap.end(); ++ii) {
		cout << (*ii).first << ": " << (*ii).second << "\n";
	}
}
void resetDataFile(ifstream &file, string fileName){
	file.close();
	file.open(fileName);
	file.ignore(256,'\n');
}
//**************************************************************
//**************************M A I N*****************************
//**************************************************************

//Main here opens a file and reads individual characters
int main(int argc, char* argv[]) {

	string fileName;   //name of the desired input file
	char xcts[256];
	int xctcount = 0;
	float minShare;
	int min_lmv = 0;
	map<string, int> candidates;
	map<string, int> next_can; 
	map<string, int> tmv_map;

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

	}

	min_lmv = ceil(minShare * total_tmv);  //rounds up min_lmv
		
	resetDataFile(dataFile, fileName.c_str());
	
	for (int k = 1; k < 11; k++) {
		for(int i=0; i<xctcount; i++){

			dataFile.getline(xcts, 256);
			
			string transaction = xcts;
			if (k==1) {
				for(int	j= 1; j < transaction.size(); j++) {
					if ( isupper(transaction.at(j))) {  //found a transaction item
						string current_item = transaction.substr(j,1);
						insert_to_map(candidates, current_item, find_count(transaction.substr(j+2)));
						
						//find transactions for k+1
						string rem_trans = transaction.substr(j+2);
						for (int l = 0; l < rem_trans.size(); l++) {
							if ( isupper(rem_trans.at(l))) {  //found a transaction item
								insert_to_map(tmv_map, current_item + rem_trans.substr(l,1), tmvxcts[i]);
							}
						}
					}
				}
			} else {
				for( map<string, int>::iterator ii=candidates.begin(); ii!=candidates.end(); ++ii) {
					int lmv = 0;
					bool found;
					bool exit = false;
					for(int l = 0; l < (*ii).first.size() && !exit; l++) {
						found = false;
						for (int j = 1; j < transaction.size() && !found; j++) {
							if (isupper(transaction.at(j)) && transaction.at(j) == (*ii).first.at(l)) {
								found = true;
								lmv += find_count(transaction.substr(j+2));
							} 	
						}
						if(!found){
							exit = true;
						}
					}
					if (found){
						candidates[(*ii).first] += lmv;
						
						int start_pos = transaction.find(*((*ii).first).rbegin()); //start after the last character in key
						if (start_pos == string::npos) { break; }	
						//check to see if tmv needs to be added to at this point.
						for (int j = start_pos; j < transaction.size(); j++) {
							if(isupper(transaction.at(j)) && (*ii).first.find(transaction.at(j)) == string::npos) {
								insert_to_map(tmv_map, (*ii).first + transaction.substr(j,1), tmvxcts[i]);
							}
						}
					}
				}
			}
		
		}


		
		cout << "candidates: "<<"\n\n";
		print_map(candidates);

		//iterates through entire hashmap and prints out contents
		cout << "tmv values: "<<"\n\n";
		for( map<string, int>::iterator ii=tmv_map.begin(); ii!=tmv_map.end(); ++ii) {
		
			cout << (*ii).first << ": " << (*ii).second << "\n";
			if ((*ii).second >= min_lmv) {
				next_can[(*ii).first] = 0;	
			}
		}
		cout << "next candidates: "<<"\n\n";		
		print_map(next_can);
		
		if (next_can.empty()) {
			break;
		}
		candidates = next_can;
		next_can.clear();
		tmv_map.clear();
		resetDataFile(dataFile, fileName.c_str());
	}	
	
	dataFile.close();

  	return(1);
}
