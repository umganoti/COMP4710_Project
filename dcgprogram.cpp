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

//**************************************************************
//**************************M A I N*****************************
//**************************************************************

//Main here opens a file and reads individual characters
int main(void) {

	string fileName;   //name of the desired input file
	char xcts[256];  
	string str;
	string substr;
	int xctcount = 0;
	int tmv = 0; 
	int num = 0;
	ifstream dataFile; //the input file

	
	//enum itemsetX = {A, B, C, D, E, F, G, H};
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
	//dataFile.close();
		
	//for(int k=1; k<C1.length; k++){
			
		for(int i=0; i<xctcount; i++){
			
			//count and store tmv(T)
			//if(k == 1){
				dataFile.getline(xcts, 256);
				str = xcts;
				unsigned found = str.find_last_of("\t");
				substr = str.substr(found+1);
				for(int j=0; j<substr.size(); j++){
					if(substr.compare(j,1, " ") != 0)
						tmv += atoi(&substr.at(j));
				}
				cout <<tmv<<endl;
				tmv = 0;
				
				
			//}	
		} 
		
	//}
		

  	return(1);
}
