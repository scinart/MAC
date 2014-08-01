# 编译标志  
CFLAGS  += -Wall -std=c++11

###########################################################  

.PHONY : all clean

all : gen my std
	@echo
gen : gen.cc
	$(CXX) $(CFLAGS) gen.cc -o gen
my : my.cc
	$(CXX) $(CFLAGS) my.cc -o my
std : std.cc
	$(CXX) $(CFLAGS) std.cc -o std

clean :  
	rm my std gen

