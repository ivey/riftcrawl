CXX=g++
CFLAGS=-I. -Wall -Wextra

all: riftcrawl

riftcrawl: rlutil.h riftcrawl.cpp
	$(CXX) $(CFLAGS) -o riftcrawl riftcrawl.cpp

.PHONY: clean

clean:
	rm riftcrawl
