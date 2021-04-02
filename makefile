#Javier Martinez Molina 20096647Y

OPTS = -Wall -O3 -std=c++0x

make: maxsum

maxsum: maxsum.cc
	g++ ${OPTS} -o maxsum maxsum.cc	 

tar: maxsum.cc makefile
	tar cvfz 20096647Y.tar.gz maxsum.cc makefile
 
