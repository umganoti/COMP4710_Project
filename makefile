dcgprogram: dcgprogram.o
	clang++ -o dcg.out dcgprogram.o

dcgprogram.o: dcgprogram.cpp
	clang++ -c dcgprogram.cpp

