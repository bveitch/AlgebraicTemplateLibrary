/**
description : Tests for Residue class
author      : bveitch
version     : 1.0
project     : AlgebraicTemplateLibrary
date        : Sunday 28th February  
*/

#include <iostream>
#include <climits>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <random>
//#include <gmpxx.h>
#include "../Utilities/NumTheoryUtils.hh"
using namespace std;

//Programs should be linked with the libgmpxx and libgmp libraries. For example,
//g++ mycxxprog.cc -lgmpxx -lgmp


int main (int argc, char *argv[]) { 
	
	unsigned int p = 31; //p= 2^5-1
    unsigned int k = 5;

    unsigned int test=453;
    auto answer = test % p;

    auto trial = NTUtils::mod_MersenneBits(test, k , true);

    std::cerr << "answer = " << answer << std::endl;
    std::cerr << "trial = "  << trial  << std::endl;
  
    unsigned int p2 = 17; //p= 2^4 + 1
    unsigned int k2 = 4;

    unsigned int test2=133;
    auto answer2 = test2 % p2;

    auto trial2 = NTUtils::mod_MersenneBits(test2, k2 , false);

    std::cerr << "answer2 = " << answer2 << std::endl;
    std::cerr << "trial2 = "  << trial2  << std::endl;
	return 0;
}

