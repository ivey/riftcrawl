CXX=g++
CC_FLAGS=-I. -Wall -Wextra -MMD
LD_FLAGS=

CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(CPP_FILES:.cpp=.o)

all: riftcrawl

riftcrawl: $(OBJ_FILES)
	$(CXX) $(LD_FLAGS) -o $@ $^

%.o: %.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm riftcrawl $(OBJ_FILES) $(wildcard *.d)

-include $(OBJ_FILES:.o=.d)
