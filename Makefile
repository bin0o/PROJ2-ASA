all: p2

p2:
	g++ -std=c++11 -O3 -Wall p2.cpp -lm
testfile:
	./a.out < testfile.in > testfile.out
clean: 
	rm a.out testfile.out p2