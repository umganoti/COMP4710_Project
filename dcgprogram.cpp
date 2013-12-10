#include <iostream>  //stream IO
#include <fstream>   //file IO
#include <string>    //strings
#include <strstream> //stringstreams for converting data.
using namespace std;

//--------------------------------------------------------
// NAME		      : Noel Ganotisi
// STUDENT NUMBER : 6721898
// COURSE		  : COMP4710
// INSTRUCTOR	  : Carson K. Leung
//
// REMARKS:
// This program reads a file and counts the number of occurrences
// of each character in it.  A huffman tree is then created from
// the occurences data.
//
// INPUT:
// A simple file of text
//
// OUTPUT:
// the file is echoed here (tho you wouldn't want to do this for
// a longer file, followed by the counts for each character.
//
//

//**************************************************************
//**************************M A I N*****************************
//**************************************************************

//Main here opens a file and reads individual characters, inserting
//them in an OccurrenceList in order to count the number of instances
//of each particular character.
int main(void) {
	ifstream dataFile; //the input file

	string fileName;   //name of the desired input file
	char data[256];           //a char from the input file
	int count = 0;

	//prompt for the desired input file name
	cout <<"Please enter input file name:";
	cin >> fileName;
	if (fileName=="")
		cout <<"\nNo filename entered.\n";
	else {
		//open the file
		dataFile.open(fileName.c_str());

	    //read chars and insert until eof
		while(dataFile.getline(data, 256)) {
		     

			 
        }//while

		//we've read all the data
		cout << endl;
		
	}
	dataFile.close();

  	return(1);
}
