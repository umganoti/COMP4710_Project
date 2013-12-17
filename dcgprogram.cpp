#include <iostream>  //stream IO
#include <fstream>   //file IO
#include <string>    //strings
#include <strstream> //stringstreams for converting data.
#include <stdlib.h> 
#include <vector>
#include <math.h>
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
int calculate_tmvDB (int arr[], int length)
{
	int tmv_total = 0;
	for(int i=0; i<length; i++){
		tmv_total += arr[i];
	}
	return tmv_total;
}
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
	else{
		cout << "File does not exist." <<endl;
		return 0;
	}
	
	xctcount = atoi(xcts);		//transaction count
	cout <<"There are "<< xctcount <<" transactions."<<endl;
	
	int tmvxcts[xctcount]; 
	
	//calculates tmvDB and tmv for each transaction
	for(int i=0; i<xctcount; i++){
			
		dataFile.getline(xcts, 256);
		tmvxcts[i] = calculate_tmvT(xcts);
				
		if(i == xctcount - 1){
			tmv_total = calculate_tmvDB(tmvxcts, xctcount);
			cout <<tmv_total<<endl;
		}
	}
	min_lmv = ceil(minShare * tmv_total);  //rounds up min_lmv
	cout << min_lmv <<endl;
	dataFile.close();
	
	dataFile.open(fileName.c_str());
	dataFile.ignore(256,'\n');
			
	//for(int k=1; k<C1.length; k++){
			
		for(int i=0; i<xctcount; i++){
			ignore_col(&dataFile);
			dataFile.getline(xcts,256);
			cout <<xcts<<endl;
			
		} 
		
	//}
  	return(1);
}
