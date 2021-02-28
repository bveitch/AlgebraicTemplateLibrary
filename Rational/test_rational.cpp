
#include <iostream>
#include <fstream>
#include <climits>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <random>
#include <gmpxx.h>
#include "Rational.hh"
#include "../Utilities/general_tests.hh"

using namespace std;

//Programs should be linked with the libgmpxx and libgmp libraries. For example,
//g++ mycxxprog.cc -lgmpxx -lgmp

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

bool sanity_tests(){

	typedef Rational<int> Frac;
	Frac a(12,5);
	Frac b(5,6);
	bool pass=true;
	{
		Frac rhs(97,30);
		auto lhs = a+b; 
		if ( !AlgTests::test_error("addition", lhs,rhs) ){
			pass=false;
		}
	    
    }
	{
		Frac rhs(47,30);
		auto lhs = a-b; 
		if ( !AlgTests::test_error("subtraction", lhs,rhs) ){
			pass=false;
		}
	    
    }
	{
		Frac rhs(2,1);
		auto lhs = a*b; 
		if ( !AlgTests::test_error("multiplication", lhs,rhs) ){
			pass=false;
		}
	    
    }
	{
		Frac rhs(25,72);
		auto lhs = b/a; 
		if ( !AlgTests::test_error("division", lhs,rhs) ) {
			pass=true;
		}

	}

	{
		Frac rhs(22,5);
		auto lhs=a;
		lhs+=2; 
		if ( !AlgTests::test_error("a+=2", lhs,rhs) ){
			pass=false;
		}
	    
    }
	{
		Frac rhs(2,5);
		auto lhs = a;
		lhs-=2;
		if ( !AlgTests::test_error("a-=2", lhs,rhs) ){
			pass=false;
		}
	    
    }
	{
		Frac rhs(5,2);
		auto lhs = b;
		lhs*=3;
		if ( !AlgTests::test_error("b*=3", lhs,rhs) ){
			pass=false;
		}
	    
    }
	{
		Frac rhs(2,5);
		auto lhs = a;
		lhs/=6; 
		if ( AlgTests::test_error("a/=6", lhs,rhs) ) {
			pass=true;
		}

	}

	{
		Frac rhs(97,30);
		auto lhs=a;
		lhs+=b; 
		if ( !AlgTests::test_error("a+=b", lhs,rhs) ){
			pass=false;
		}
	    
    }
	{
		Frac rhs(47,30);
		auto lhs = a;
		lhs-=b;
		if ( !AlgTests::test_error("a-=b", lhs,rhs) ){
			pass=false;
		}
	    
    }
	{
		Frac rhs(2,1);
		auto lhs = a;
		lhs*=b;
		if ( !AlgTests::test_error("a*=b", lhs,rhs) ){
			pass=false;
		}
	    
    }
	{
		Frac rhs(25,72);
		auto lhs = a;
		lhs/=b; 
		if ( !AlgTests::test_error("a/=b", lhs,rhs) ) {
			pass=true;
		}

	}
	return pass;
}

template<class T>
bool test_Rational(ofstream& file,std::pair<T,T> apair, std::pair<T,T> bpair, std::pair<T,T> cpair)
{
	typedef Rational<T> Frac;
	Frac a(apair.first,apair.second);
	Frac b(bpair.first,bpair.second);
	Frac c(cpair.first,cpair.second);
 	
	file << " a = " << a << "\n";
	file << " b = " << b << "\n";
	file << " c = " << c << "\n";
	
	bool pass = true;
	AddF<Frac> add_;
	MultF<Frac> mult_;
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

	Frac add_id(static_cast<T>(0));
	Frac mult_id(static_cast<T>(1));
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

	AddinvF<Frac> add_inv;
	MultinvF<Frac> mult_inv;
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
	return pass;
}

template<class T>
bool test_exception(T n){
	typedef Rational<T> Frac;
	bool pass=false;
	try{
		Frac a(n,0);
	}
	catch(...){
		pass=true;
	}
	if(!pass){
		std::cerr << "Exception, test failed" << std::endl;
	}
	return pass;
}

int main (int argc, char *argv[]) { 
	random_device dev;
    mt19937 gen(dev());
	int N=9;
    uniform_int_distribution<> randfn(1,N);
	typedef pair<int,int> Pairofint;
	Pairofint a(randfn(gen),randfn(gen));
	Pairofint b(randfn(gen),randfn(gen));
	Pairofint c(randfn(gen),randfn(gen));
	ofstream file("test_Rational.txt");
	bool pass=true;
	pass*=sanity_tests();
	pass*=test_Rational(file,a, b, c);
	file.close();
	
	pass*=test_exception(5);
	if(pass){
		cout << "All tests passed" << endl;
	}
	else{
		std::cerr << "Test failed" << std::endl;
	}
}

