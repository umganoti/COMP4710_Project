COMP4710 Project - Direct Candidate Generation C++ Program

Requirements: 
-dcgtable.txt or a text file with exact format as dcgtable.txt
-clang++ compiler

Text file format:
First line is the number of domain items.
Second line is the number of transactions.
Subsequent lines contains the transaction number, followed by a tab,
number of domains, followed by a tab, and the domain items and its corresponding count separated by a colon.

Output:
SH frequent items for k-itemsets, Candidate TMV values for k-itemsets,
k+1-itemsets that could be SH frequent, SH-frequency count for k-itemsets 
and the runtime of the program.

How to run the program:
From the command line, compile files using the 'make' command.
From the command line, enter ./dcg.out to see parameters you want to view.  See below for usage.

Usage: ./dcg.out TDB minshare showFSH showTMV showNextCan cntFSH showTime
		minshare	FLOAT
		showFSH		0(No) or 1(Yes) to show freq SH for k-itemset
		showTMV		0(No) or 1(Yes) to show TMV values for k-itemset
		showNextCan	0(No) or 1(Yes) to show items that could be SH freq
		cntFSH		0(No) or 1(Yes) to count SH frequent for k sequences
		showTime	0(No) or 1(Yes) to show runtime


An example to view all parameters, from the command line enter: ./dcg.out dcgtable.txt 0.3 1 1 1 1 1