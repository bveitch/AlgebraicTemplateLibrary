/**
description : Tests for Polynomial class
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
//#include <gmpxx.h>
#include "Polynomial.hh"
#include "../Utilities/general_tests.hh"

using namespace std;
bool scalar_tests(){

	vector<int> c1{1,2,1};
	vector<int> c2 { 1, 2, 3, 4};

	typedef Polynomial<int> polyI;
	polyI p1(1,2,1);
	polyI p2(c2);
	int V=2;
	bool passed=true;
	{
		{
			std::ostringstream ostr;
			ostr.str("");
			vector<int> c2PV { 1, 2, 3, V+4};
			polyI rhs(c2PV);
			ostr << "p1 +=V : ((" << p1 << ")+=(" << V << ")) = " << rhs;
			polyI lhs(p2);
			lhs+=V;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );
		}
		{
			std::ostringstream ostr;
			ostr.str("");
			vector<int> c2MV { 1, 2, 3, 4-V};
			polyI rhs(c2MV);
			ostr << "p2 -=V : ((" << p2 << ")-=(" << V << ")) = " << rhs;
			polyI lhs(p2);
			lhs-=V;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		{
			std::ostringstream ostr;
			ostr.str("");
			vector<int> c2TV { V, 2*V, 3*V, 4*V};
			polyI rhs(c2TV);
			ostr << "p2 *=V : ((" << p2 << ")*=(" << V << ")) = " << rhs;
			polyI lhs(p2);
			lhs*=V;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		{
			std::ostringstream ostr;
			ostr.str("");
			vector<int> c2DV { 1/V, 2/V, 3/V, 4/V};
			polyI rhs(c2DV);
			ostr << "p2 /=V : ((" << p2 << ")/=(" << V << ")) = " << rhs;
			polyI lhs(p2);
			lhs/=V;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		{
			std::ostringstream ostr;
			ostr.str("");
			vector<int> c2QV { 1 % V, 2 % V, 3 % V, 4 %V};
			polyI rhs(c2QV);
			ostr << "p2 %=V : ((" << p2 << ")%=(" << V << ")) = " << rhs;
			polyI lhs(p2);
			lhs%=V;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		if(!passed){
			cerr << " Scalar tests failed" << endl;
		}
	   return passed; 
    }
}

bool deriv_shift_tests(){

	vector<int> c1 {1, 2, 3, 4, 5};
	vector<int> c2 {4, 6, 6, 4};

	typedef Polynomial<int> polyI;
	polyI p1(c1);
	polyI p2(c2);

	bool passed=true;
	{
		{
			std::ostringstream ostr;
			ostr.str("");
			vector<int> Dc1 { 4, 6, 6, 4};
			polyI rhs(Dc1);
			ostr << "derivative : D(" << p1 << ") = " << rhs;
			polyI lhs(p1);
			lhs.deriv();
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );
		}
		{
			std::ostringstream ostr;
			ostr.str("");
			vector<int> p1_shiftF2 { 1, 2, 3, 4, 5, 0, 0};
			polyI rhs(p1_shiftF2);
			ostr << "p1 shift 2 : ((" << p1 << ") S2 = " << rhs;
			polyI lhs(p1);
			lhs.shift_fwd(2);
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		{
			std::ostringstream ostr;
			ostr.str("");
			vector<int> p1_shiftB3 { 1, 2};
			polyI rhs(p1_shiftB3);
			ostr << "p1 shift 1 : ((" << p1 << ") S1 = " << rhs;
			polyI lhs(p1);
			lhs.shift_bwd(3);
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		if(!passed){
			cerr << " Deriv and shift tests failed" << endl;
		}
	   return passed; 
    }
}



bool comparison_op_tests(){

	vector<int> c1 {-1, 0, 3, 4, 5};
	vector<int> c2 {4, 6, 6, 4};
	vector<int> c3 {-1, 0, 0 ,0, 1};

	typedef Polynomial<int> polyI;
	polyI p1(c1);
	polyI p2(c2);
	polyI p3(c3);

	bool passed=true;
	{
		{

			auto greaterthan=[](polyI lhs, polyI rhs){ return (lhs > rhs); } ;

			std::ostringstream ostr;
			ostr.str("");
			polyI lhs=c2;
			polyI rhs=c1;
			ostr << "greaterthan" ;
			passed *= AlgTests::test_compare(ostr.str() , lhs , rhs, greaterthan );
		}
		{
			auto lessthan=[](polyI lhs, polyI rhs){ return (lhs < rhs); } ;
			std::ostringstream ostr;
			ostr.str("");
			polyI lhs=c3;
			polyI rhs=c1;
			ostr << "lessthan" ;
			passed *= AlgTests::test_compare(ostr.str() , lhs , rhs, lessthan );

		}
		{
			auto greaterthaneq=[](polyI lhs, polyI rhs){ return (lhs >= rhs); } ;
			std::ostringstream ostr;
			ostr.str("");
			polyI lhs=c1;
			polyI rhs=c3;
			ostr << "greaterthaneq";
			passed *= AlgTests::test_compare(ostr.str() , lhs , rhs, greaterthaneq );

		}
		{
			auto lessthaneq=[](polyI lhs, polyI rhs){ return (lhs <= rhs); } ;
			std::ostringstream ostr;
			ostr.str("");
			polyI lhs=c1;
			polyI rhs=c2;
			ostr << "lessthaneq" ;
			passed *= AlgTests::test_compare(ostr.str() , lhs , rhs, lessthaneq );

		}
		if(!passed){
			cerr << " Comparison operator tests failed" << endl;
		}
	   return passed; 
    }
}
bool sanity_tests_assignment(){

	vector<int> c1{1,2,1};
	vector<int> c2 { 1, 2, 3, 4};
	vector<int> c1Pc2 {1, 3, 5, 5};
	vector<int> c2Mc1 { 1, 1, 1, 3};
	vector<int> c2Tc1 { 1, 4, 8, 12, 11, 4};
	vector<int> c2Dc1 { 1, 0};
	vector<int> c2Qc1 { 2, 4};

	typedef Polynomial<int> polyI;
	polyI p1(1,2,1);
	polyI p2(c2);
	
	bool passed=true;
	{
		{
			std::ostringstream ostr;
			ostr.str("");
			polyI rhs(c1Pc2);
			ostr << "p1 +=p2 : ((" << p1 << ")+=(" << p2 << ")) = " << rhs;
			polyI lhs(p1);
			lhs+=p2;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );
		}
		{
			std::ostringstream ostr;
			ostr.str("");
			polyI rhs(c2Mc1);
			ostr << "p2 -=p1 : ((" << p2 << ")-=(" << p1 << ")) = " << rhs;
			polyI lhs(p2);
			lhs-=p1;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		{
			std::ostringstream ostr;
			ostr.str("");
			polyI rhs(c2Tc1);
			ostr << "p2 *=p1 : ((" << p2 << ")*=(" << p1 << ")) = " << rhs;
			polyI lhs(p2);
			lhs*=p1;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		{
			std::ostringstream ostr;
			ostr.str("");
			polyI rhs(c2Dc1);
			ostr << "p2 /=p1 : ((" << p2 << ")/=(" << p1 << ")) = " << rhs;
			polyI lhs(p2);
			lhs/=p1;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		{
			std::ostringstream ostr;
			ostr.str("");
			polyI rhs(c2Qc1);
			ostr << "p2 %=p1 : ((" << p2 << ")%=(" << p1 << ")) = " << rhs;
			polyI lhs(p2);
			lhs%=p1;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		if(!passed){
			cerr << "Assignment tests failed" << endl;
		}
	   return passed; 
    }
}

bool sanity_tests_operator(){
	vector<int> c1{1,2,1};
	vector<int> c2 { 1, 2, 3, 4};
	vector<int> c1Pc2 {1, 3, 5, 5};
	vector<int> c2Mc1 { 1, 1, 1, 3};
	vector<int> c2Tc1 { 1, 4, 8, 12, 11, 4};
	vector<int> c2Dc1 { 1, 0};
	vector<int> c2Qc1 { 2, 4};

	typedef Polynomial<int> polyI;
	polyI p1(1,2,1);
	polyI p2(c2);
	bool passed=true;
	{
		{
			std::ostringstream ostr;
			ostr.str("");
			polyI rhs(c1Pc2);
			ostr << "p1 + p2 : ((" << p1 << ") + (" << p2 << ")) = " << rhs;
			auto lhs = p1 + p2;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );
		}
		{
			std::ostringstream ostr;
			ostr.str("");
			polyI rhs(c2Mc1);
			ostr << "p2 - p1 : ((" << p2 << ") - (" << p1 << ")) = " << rhs;
			auto lhs = p2 - p1;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		{
			std::ostringstream ostr;
			ostr.str("");
			polyI rhs(c2Tc1);
			ostr << "p2 * p1 : ((" << p2 << ") * (" << p1 << ")) = " << rhs;
			auto lhs = p2 * p1;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		{
			std::ostringstream ostr;
			ostr.str("");
			polyI rhs(c2Dc1);
			ostr << "p2 / p1 : ((" << p2 << ") / (" << p1 << ")) = " << rhs;
			auto lhs = p2 / p1;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		{
			std::ostringstream ostr;
			ostr.str("");
			polyI rhs(c2Qc1);
			ostr << "p2 % p1 : ((" << p2 << ") % (" << p1 << ")) = " << rhs;
			auto lhs = p2 % p1;
			passed *= AlgTests::test_error(ostr.str() , lhs , rhs );

		}
		if(!passed){
			cerr << "Operator tests failed" << endl;
		}
	   return passed; 
    }
}

int main (int argc, char *argv[]) { 
	bool passed = true;
	passed *= scalar_tests();
	passed *= deriv_shift_tests();
	passed *= comparison_op_tests();
	passed *= sanity_tests_assignment();
	passed *= sanity_tests_operator();

	if(passed){
		cout << "All tests passed" << endl;
	}
	else{
		std::cerr << "Test failed" << std::endl;
	}
	
	return 0;
}

