#/bin/bash
g++ particle.cpp -c -std=c++11 -o particle.o
g++ test.cpp particle.o -std=c++11 -o test
