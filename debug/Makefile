# 编译标志  
CFLAGS  += -Wall -std=c++11

###########################################################  

.PHONY : all clean

all : gen my std
	@echo
gen : gen.cc
	$(CXX) $(CFLAGS) gen.cc -o gen -O
my : my.cc
	$(CXX) $(CFLAGS) my.cc -o my -O0 -g -pg -DONLINE_JUDGE
std : std.cc
	$(CXX) $(CFLAGS) std.cc -o std -O -DONLINE_JUDGE

clean :  
	rm my std gen

