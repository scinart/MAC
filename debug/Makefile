# 编译标志  
CFLAGS  += -Wall -std=c++11

###########################################################  

.PHONY : all clean

all : gen my std
	@echo
gen : gen.cc
	$(CXX) $(CFLAGS) gen.cc -o gen -O2
my : my.cc
	$(CXX) $(CFLAGS) my.cc -o my -O2 -g -DONLINE_JUDGE
std : std.cc
	$(CXX) $(CFLAGS) std.cc -o std -O2 -DONLINE_JUDGE

clean :  
	rm my std gen

