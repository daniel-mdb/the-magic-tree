all: a.cc
	c++ -g -O0 -fsanitize=address -lpthread a.cc && ./a.out
