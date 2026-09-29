test:test.cc object_pool.hpp
	g++ -o $@ $^ -std=c++17
.PHONY:clear
clear:
	rm -f test