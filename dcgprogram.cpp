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
void ignore_col(ifstream *dFile)
{
	for(int i=0; i<2; i++){
		dFile->ignore(256,'\t');
	}
	
}
int calculate_lmv(const char *s, string itemset)
{
	string str = s;
	string items;
	string count;
	string temp;
	bool exit = false;
	int lmv = 0;
	unsigned first = str.find_first_of("\t");
	unsigned last = str.find_last_of("\t");
	temp = str.substr(first+2);
	first = temp.find_first_of("\t");
	items = temp.substr(0,first);
	count = str.substr(last+1);
	
	for(int i=0; i<itemset.size() && !exit; i++){
		size_t found = items.find(itemset.at(i));
		if(found != string::npos)
			lmv += atoi(&count.at(found));
			
		else
			exit = true;
	
	}
	
	if(exit)
		lmv = 0;
	
	return lmv;
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
	int item_count = 0;
	int lmv = 0;
	map<char, int> Candidates;
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
	//calculates tmvDB and tmv for each transaction
	for(int i=0; i<xctcount; i++){
			
		dataFile.getline(xcts, 256);
		tmvxcts[i] = calculate_tmvT(xcts);
		total_tmv += tmvxcts[i]; //iterator for tmvDB


		string transaction = xcts;
		for(int	j= 1; j < transaction.size(); j++) {
			if ( isupper(transaction.at(j))) {
				item_count = atoi(&transaction.at(j+2));
				cout << "Character: " << transaction.at(j)<< " Count:" << item_count << "\n";
				
			}
		}

			
		cout << "tmv of transaction " << i <<": "<< tmvxcts[i] << "\n";
	}

	cout << "Total tmv: " << total_tmv << "\n";
	
	min_lmv = ceil(minShare * tmv_total);  //rounds up min_lmv

	dataFile.close();	
	dataFile.open(fileName.c_str());
	dataFile.ignore(256,'\n');
		
	//for(int k=1; k<C1.length; k++){
			
		for(int i=0; i<xctcount; i++){
			ignore_col(&dataFile);
			dataFile.getline(xcts,256);
			//lmv += calculate_lmv(xcts, "CE");
			//cout<<lmv<<endl;	
		} 
		
	//}
  	return(1);
}
