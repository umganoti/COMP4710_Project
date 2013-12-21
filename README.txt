COMP4710 Project - Direct Candidate Generation C++ Program

Requirements: 
-dcgtable.txt or a text file with exact format as dcgtable.txt
-clang++ compiler

Output:
SH frequent items for k-itemsets, Candidate TMV values for k-itemsets and
k+1-itemsets that could be SH frequent.

How to run the program:
From the command line, compile files using the 'make' command and then enter the following format: 
program_name filename.txt minshare_value (float)
example: ./dcg.out dcgtable.txt 0.3