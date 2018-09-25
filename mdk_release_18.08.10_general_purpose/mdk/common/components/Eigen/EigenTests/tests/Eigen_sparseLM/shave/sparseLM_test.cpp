// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.

#include <stdlib.h>
#include <stdio.h>
#include <sys/shave_system.h>
#include <iostream>
using namespace std;


void test_sparseLM(void); 

__attribute__((dllexport)) int main()
{
 std::cerr.copyfmt(std::cout);
 std::cerr.clear(std::cout.rdstate());
 std::cerr.rdbuf(std::cout.rdbuf());
 test_sparseLM(); 
 
 printf("All Passed !\n");
 return 0;
}


