#include <iostream>  //stream IO
#include <fstream>   //file IO
#include <string>    //strings
#include <strstream> //stringstreams for converting data.
#include <stdlib.h> 
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
//**************************************************************
//**************************M A I N*****************************
//**************************************************************

//Main here opens a file and reads individual characters
int main(void) {

	string fileName;   //name of the desired input file
	char xcts[256];  
	int xctcount = 0;
	int tmv = 0; 
	int num = 0;
	float minShare = 0.3;
	int tmv_total = 0; 
	ifstream dataFile; //the input file
	int min_lmv = 0;

	
	enum {A, B, C, D, E, F, G, H};
	//candidate 1
	int C1[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
		

	//prompt for the desired input file name
	//cout <<"Please enter input file name:";
	//cin >> fileName;
	
	//if (fileName==""){
	//	cout <<"\nNo filename entered.\n";
	//}
	
	//open the file
	//dataFile.open(fileName.c_str());
	dataFile.open("dcgtable.txt");
		
	//newLine = &dataFile.getline(xcts, 256);
	dataFile.getline(xcts,256);
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
	dataFile.close();
	dataFile.open("dcgtable.txt");
	dataFile.ignore(256, '\n');
	dataFile.getline(xcts,256);
	min_lmv = minShare * tmv_total;
	//cout <<xcts<<endl;
		
	//for(int k=1; k<C1.length; k++){
			
		//for(int i=0; i<xctcount; i++){
			
			
		//} 
		
	//}
		

  	return(1);
}
