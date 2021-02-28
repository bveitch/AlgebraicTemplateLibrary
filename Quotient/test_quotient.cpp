
#include <iostream>
#include <climits>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include <gmpxx.h>
#include <random>
#include "Quotient.hh"
#include "../Utilities/general_tests.hh"
using namespace std;

bool sanity_tests(){
	cout << "Sanity tests for quotient" << endl;
	typedef Quotient<int> Mod;
	Mod::m=13;
	int k11=11;
	int k09=22;
	int k06=71;

	int k6pow5_13 =2;
	int k11p9_13  =7;
	int k11m9_13  =2;
	int k11t9_13  =8;
	int k11d9_13  =7;

	Mod m1=k11, m2=k09, m3=k06;
	
	
	bool passed=true;
	std::ostringstream ostr;
	ostr.str("");
	ostr << "-m1    : (-" << m1 << ")"         << "  = " << k11m9_13;
	passed *= AlgTests::test_error(ostr.str() , (-m1).value() , k11m9_13 );
	ostr.str("");
	ostr << "m3^5    : (" << m3 << ")^5"         << "  = " << k6pow5_13;
	passed *= AlgTests::test_error(ostr.str() , m3.pow(5).value() , k6pow5_13);
	ostr.str("");
	ostr << "m1 + m2 : (" << m1 << ") + (" << m2 << ") = " << k11p9_13;
	passed *= AlgTests::test_error(ostr.str() , (m1+m2).value()     , k11p9_13 );
	ostr.str("");
	ostr << "m1 - m2 : (" << m1 << ") - (" << m2 << ") = " << k11m9_13;
	passed *= AlgTests::test_error(ostr.str() , (m1-m2).value()     , k11m9_13 );
	ostr.str("");
	ostr << "m1 * m2 : (" << m1 << ") * (" << m2 << ") = " << k11t9_13;
	passed *= AlgTests::test_error(ostr.str() , (m1*m2).value()     , k11t9_13 );
	ostr.str("");
	ostr << "m1 / m2 : (" << m1 << ") / (" << m2 << ") = " << k11d9_13; 
	passed *= AlgTests::test_error(ostr.str() , (m1/m2).value()     , k11d9_13 ); 
	
	return passed;
}

template<class T> 
struct AddF {
  
  T operator()(T x, T y) const { return x + y; }

};

template<class T> 
struct MultF {
  
  T operator()(T x, T y) const { return x * y; }

};

template<class T> 
struct AddinvF {
  
  T operator()(T x) const { return -x; }

};
template<class T> 
struct MultinvF {
  
  T operator()(T x) const { return static_cast<T>(1)/x; }

};

template<class T>
bool test_Quotient(ofstream& file,T mod_,T a_, T b_, T c_)
{
	typedef Quotient<T> Modulus;
	Modulus::m=mod_;
	Modulus a(a_);
	Modulus b(b_);
	Modulus c(c_);

	
	file << " a = " << a << "\n";
	file << " b = " << b << "\n";
	file << " c = " << c << "\n";
	
	bool pass = true;
	AddF<Modulus> add_;
	MultF<Modulus> mult_;
	bool assoc_add  = AlgTests::test_associative(a, b, c, add_,file);
	if(!assoc_add){
		pass=false;
		file << "... Associative addition failed.\n";
	}
	bool assoc_mul = AlgTests::test_associative(a, b, c, mult_, file);
	if(!assoc_add){
		pass=false;
		file << "... Associative multiplication failed.\n";
	}
	bool dist_left = AlgTests::test_left_distributive(a, b, c, add_, mult_, file);
	if(!dist_left){
		pass=false;
		file << "... Distributive left failed: \n";
	}
	bool dist_right = AlgTests::test_right_distributive(a, b, c, add_, mult_, file);
	if(!dist_right){
		pass=false;
		file << "... Distributive right failed: \n";
	}
	bool comm_add = AlgTests::test_commutative(a, b, add_, file);
	if(!comm_add){
		pass=false;
		file << "... Commutative addition failed: \n";
	}
	bool comm_mul = AlgTests::test_commutative(a, b, mult_, file);
	if(!comm_mul){
		pass=false;
		file << "... Commutative multiplication failed: \n";
	}

	Modulus add_id(static_cast<T>(0));
	Modulus mult_id(static_cast<T>(1));
	bool left_id_add  = AlgTests::test_left_identity(add_id, a, add_, file);
	if(!left_id_add){
		pass=false;
		file << "... Left additive identity failed: \n";
	}
	bool right_id_add = AlgTests::test_right_identity(a, add_id, add_, file);
	if(!right_id_add){
		pass=false;
		file << "... Right additive identity failed: \n";
	}
	bool left_id_mul = AlgTests::test_left_identity(mult_id, a, mult_, file);
	if(!left_id_mul){
		pass=false;
		file << "... Left multiplicative identity failed: \n";
	}
	bool right_id_mul = AlgTests::test_right_identity(a, mult_id, mult_, file);
	if(!right_id_mul){
		pass=false;
		file << "... Right multiplicative identity failed: \n";
	}

	AddinvF<Modulus> add_inv;
	MultinvF<Modulus> mult_inv;
	bool left_inv_add = AlgTests::test_left_inverse(a, add_id, add_, add_inv, file);
	if(!left_inv_add){
		pass=false;
		file << "... Left additive inverse failed: \n";
	}
	bool right_inv_add = AlgTests::test_right_inverse(a, add_id, add_, add_inv, file);
	if(!right_inv_add){
		pass=false;
		file << "... Right additive inverse failed: \n";
	}
	bool left_inv_mul = AlgTests::test_left_inverse(a, mult_id, mult_, mult_inv, file);
	if(!left_inv_mul){
		pass=false;
		file << "... Left multiplicative inverse failed: \n";
	}
	bool right_inv_mul = AlgTests::test_right_inverse(a, mult_id, mult_, mult_inv, file);
	if(!right_inv_mul){
		pass=false;
		file << "... Right multipicative inverse failed: \n";
	} 
	
	if(!pass){
		std::cerr << "Randomized algebraic tests failed" << std::endl;
	}
	else{
		std::cerr << "Randomized algebraic tests passed" << std::endl;
	}
	return pass;
}
int main (int argc, char *argv[]) { 
	
	bool pass=true;
	pass*=sanity_tests();
	
	random_device dev;
    mt19937 gen(dev());
	int p=31;
    uniform_int_distribution<> randfn(1,p);
	
	int a(randfn(gen));
	int b(randfn(gen));
	int c(randfn(gen));
	ofstream file("test_Quotient.txt");
	
	pass*=test_Quotient<int>(file,31,a, b, c);
	if(pass){
		cout << "All tests passed" << endl;
	}
	return 0;
}

