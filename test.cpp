#include <iostream>  //stream IO
#include <fstream>   //file IO
#include <string>    //strings
#include <sstream> //stringstreams for converting data.
#include <stdlib.h>
#include <vector>
#include "Candidate.h"
using namespace std;

//Main here opens a file and reads individual characters
int main(void) {

    cout << "Hello\n";
    Candidate test (12, 12);
    cout << test.get_lmv() << "\n";
    return (1);
}
