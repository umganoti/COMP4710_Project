test: test.o Candidate.o
	clang++ test.o Candidate.o

test.o: test.cpp Candidate.h
	clang++ -c test.cpp

Candidate.o: Candidate.h Candidate.cpp
	clang++ -c Candidate.cpp
