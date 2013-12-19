dcgprogram: dcgprogram.o Candidate.o
	clang++ -o dcg.out dcgprogram.o Candidate.o

dcgprogram.o: dcgprogram.cpp Candidate.h
	clang++ -c dcgprogram.cpp

Candidate.o: Candidate.h Candidate.cpp
	clang++ -c Candidate.cpp
