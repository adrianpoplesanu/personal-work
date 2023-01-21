%:
	g++ -std=c++17 -o $* $*.cpp
clean:
	find . -type f  ! -name "*.*" ! -name "Makefile" ! -name "README.md" -delete
test:
	g++ -Wno-c++11-extensions -o syntax144 syntax144.cpp
cpp11 $(target):
	g++ -Wno-c++11-extensions -o $(target) $(target).cpp
