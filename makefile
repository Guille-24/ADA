#Guillermo Jiménez Martínez 71721984A

OPTS = -Wall -O3 -std=c++0x

make: potter

potter: potter.cc
	g++ ${OPTS} -o potter potter.cc	 

tar: potter.cc makefile
	tar cvfz 71721984A.tar.gz potter.cc makefile
 
