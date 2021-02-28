#ifndef NTUTILS_HH
#define NTUTILS_HH


#include <vector>

namespace NTUtils {

	template <typename T> 
	T sgn(T val) {
    	int ans=(T(0) < val) - (val < T(0));
		return static_cast<T>(ans);
	};

	template<typename T>
	T gcd(T x, T y)
	{
		if(x <0) x=-x;
		if(y < 0) y=-y;
		if(y == 0) return x;
		else return gcd(y, x % y);
	};

	template<typename T>
	T gcd(std::vector<T> v)
	{
		if(     v.size() == 0 ) return T(0);
		else if(v.size() == 1 ) return v[0];
		else if(v.size() == 2 ) return gcd( v[0], v[1] );
		else {
			auto v0=v.back();
			v.pop_back();
			return gcd(v0, gcd(v) );
		}
	};

	template <typename T> 
	T euclid(T x, T y, T& a, T& b){
		if(y==static_cast<T>(0) ){
			auto d=abs(x);
			a=sgn(x);
			b=static_cast<T>(0);
			return d;
		}
		if(y<0){
			auto d = euclid(x, -y, a , b );
			b=-b;
			return d;
		}
		if(x<0){
			auto d = euclid(-x, y, a , b );
			a=-a;
			return d;
		}
	
		T a_;
		T b_;
		T x_=y;
		T y_=x%y;
		T q_=x/y;
		auto d = euclid(x_, y_, a_ , b_ );
		a=b_;
		b=a_-b_*q_;
		return d;
	}

	template <typename T> 
	T abs(T val) {
		return (val >=T(0)) ? val : -val;
	};


	template<typename T> 
	T fast_exp(T v, long n){
		if(n < 0 ) return fast_exp( T(1)/v, -n);
		else if(n == 0 ) return 1;
		else if(n == 1 ) return v;
		else if(n % 2 ==1) return v*fast_exp(v*v,(n-1)/2);
		else return fast_exp(v*v,n/2 );	
	}

	template<typename T> 
	T fast_exp_bits(T v, long n){
		if(n < 0 ) return fast_exp_bits( T(1)/v, -n);
		else if(n == 0 ) return 1;
		else if(n == 1 ) return v;
		else if( (n & 1) == 1) return v*fast_exp_bits(v*v,(n-1) >> 1);
		else return fast_exp_bits(v*v,n >>1 );	
	}

	unsigned int countBits(unsigned int n)
	{
   		unsigned int count = 0;
   		while (n)
   		{
        	count++;
        	n >>= 1;
    	}
    	return count;
	}
  
	int mod_MersenneBits(unsigned int v, unsigned int K, bool neg){
		//K = block_size
		// p = a prime! 
		//if(neg) p = 2^K - 1
		//else    p = 2^K + 1

		unsigned int exponent = countBits(v);
		unsigned int nblocks = (exponent/K) + 1;

		int sum = 0;
		bool even_blocknum= true;
		while(v) 
		{
			auto v2 = v >> K;
			auto w = v2 << K;
			if(even_blocknum || neg){
				sum += (v ^ w);
			}
			else {
				sum -= ( v ^ w);
			}
			even_blocknum = !even_blocknum;
			v = v2;
		} 
		return sum;


	}

}
#endif