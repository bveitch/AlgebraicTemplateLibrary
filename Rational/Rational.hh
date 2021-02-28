#ifndef RATIONAL_HH
#define RATIONAL_HH

#include <assert.h>     /* assert */
#include <string>
#include <sstream>
#include <iostream>
#include "../Utilities/NumTheoryUtils.hh"

/* template<typename T>
T gcd(T x, T y)
{
	if(x <0) x=-x;
	if(y < 0) y=-y;
	if(y == 0) return x;
	else return gcd(y, x % y);
};

template <typename T> 
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
};

template <typename T> 
T abs(T val) {
	return (val >=T(0)) ? val : -val;
}; */

template <class T>
class Rational{
T n_;
T d_;

public:
	Rational(const T& n){
		n_=n;
		d_=1;
	};
	
	Rational(const T& n, const T& m){ 
		
		if(m ==T(0) ) throw std::invalid_argument("0 in denominator");
		
		n_=NTUtils::sgn(m)*n/NTUtils::gcd(n,m);
		d_=NTUtils::abs(m)/NTUtils::gcd(n,m);
	};
	
	/**
	Rational(T n, T m){ 
		assert (sgn(m)>0 );
		//not the best ow change m's type to unsigned
		n_=n/gcd(n,m);
		d_=m/gcd(n,m);
	};
	*/
	Rational(const Rational& Rational){
		n_=Rational.n();
		d_=Rational.d();
	};
	
	T n() const {return n_;};
	T d() const {return d_;};
	
	Rational& operator= (const T& n){
		n_=n;
		d_=1;
		return *this;
	};
	
	Rational& operator= (const Rational& rhs){
		n_=rhs.n();
		d_=rhs.d();
		return *this;
	};

	Rational& operator*= (const T& n){
		T nn=NTUtils::gcd(n,d_);
		n_*=(n/nn);
		d_/=nn;
		return *this;
	};
	
	Rational& operator/= (const T& n){
		
		if(n ==T(0) ) throw std::invalid_argument("0 in denominator");
		
		int sign=NTUtils::sgn(n);
		T nn=NTUtils::gcd(n_,n);
		n_/=nn*sign;
		d_*=(NTUtils::abs(n)/nn);
		return *this;
	};
	
	Rational& operator+= (const T& n){
		n_+=n*d_;
		return *this;
	};
	
	Rational& operator-= (const T& n){
		n_-=n*d_;
		return *this;
	};
	
	template<class F>
	Rational& operator+= (const Rational<F>& rhs){
		n_*=rhs.d();
		n_+=d_*rhs.n();
		d_*=rhs.d();
		T d=NTUtils::gcd(n_,d_);
		n_/=d;
		d_/=d;
		return *this;
	};
	
	template<class F>
	Rational& operator-= (const Rational<F>& rhs){
		n_*=rhs.d();
		n_-=d_*rhs.n();
		d_*=rhs.d();
		T d=NTUtils::gcd(n_,d_);
		n_/=d;
		d_/=d;
		return *this;
	};
	template<class F>
	Rational& operator*= (const Rational<F>& rhs){
		n_*=rhs.n();
		d_*=rhs.d();
		T d=NTUtils::gcd(n_,d_);
		n_/=d;
		d_/=d;
		return *this;
	};
	
	template<class F>
	Rational& operator/= (const Rational<F>& rhs){
		n_*=rhs.d();
		d_*=rhs.n();
		T d=NTUtils::gcd(n_,d_);
		n_/=d;
		d_/=d;
		return *this;
	};  
	
};

template<class T> Rational<T> operator+(const Rational<T>& lhs, const Rational<T>& rhs){
	return Rational<T>(lhs.n()*rhs.d()+lhs.d()*rhs.n(),lhs.d()*rhs.d());
};

template<class T> Rational<T> operator+(const Rational<T>& lhs, const T& val){
	return Rational<T>(val*lhs.d()+lhs.n(),lhs.d());	
};

template<class T> Rational<T> operator+(const T& val, const Rational<T>& rhs){

	return Rational<T>(val*rhs.d()+rhs.n(),rhs.d());	
};

template<class T> Rational<T> operator-(const Rational<T>& lhs, const Rational<T>& rhs){
	return Rational<T>(lhs.n()*rhs.d()-lhs.d()*rhs.n(),lhs.d()*rhs.d());
};

template<class T> Rational<T> operator-(const Rational<T>& lhs, const T& val){
	return Rational<T>(lhs.n()-val*lhs.d(),lhs.d());	
};

template<class T> Rational<T> operator-(const T& val, const Rational<T>& rhs){
	return Rational<T>(-val*rhs.d()-rhs.n(),rhs.d());	
};;

template<class T> Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs){
	return Rational<T>(lhs.n()*rhs.n(),lhs.d()*rhs.d());	
};

template<class T> Rational<T> operator*(const Rational<T>& lhs, const T& val){
	return Rational<T>(lhs.n()*val,lhs.d());	
};

template<class T> Rational<T> operator*(const T& val, const Rational<T>& rhs){
	return Rational<T>(val*rhs.n(),rhs.d());	
};

template<class T> Rational<T> operator/(const Rational<T>& lhs, const Rational<T>& rhs){
	int sign=NTUtils::sgn(rhs.n());
	return Rational<T>(lhs.n()*rhs.d()*sign,lhs.d()*abs(rhs.n()));
};

template<class T> Rational<T> operator/(const Rational<T>& lhs, const T& val){
	if(val ==T(0) ) throw std::invalid_argument("0 in denominator");
	
	int sign=sgn(val);
	return Rational<T>(lhs.n()*sign,lhs.d()*abs(val));	
};

template<class T> Rational<T> operator/(const T& val, const Rational<T>& rhs){
	int sign=NTUtils::sgn(rhs.n());
	return Rational<T>(val*rhs.d()*sign,abs(rhs.n()));
};

template<class T> Rational<T> operator+(const Rational<T>& rhs){
	return rhs;
};

template<class T> Rational<T> operator-(const Rational<T>& rhs){
return Rational<T>(-rhs.n(),rhs.d());
};

template<class T>
bool operator==(const Rational<T>& lhs, const Rational<T>& rhs){
	if(lhs.n()==rhs.n() && lhs.d()==rhs.d()) return true;
	else return false;
};

template<class T>
bool operator==(const Rational<T>& lhs, const T& val){
	if(lhs.n()==val && lhs.d()==1) return true;
	else return false;
};

template<class T>
bool operator==(const T& val, const Rational<T>& rhs){
	if(rhs.n()==val && rhs.d()==1) return true;
	else return false;
};

template<class T>
bool operator!=(const Rational<T>& lhs, const Rational<T>& rhs){
	if(lhs.n()!=rhs.n() || lhs.d()!=rhs.d()) return true;
	else return false;
};

template<class T>
bool operator!=(const Rational<T>& lhs, const T& val){
	if(lhs.n()!=val || lhs.d()==1) return true;
	else return false;
};

template<class T>
bool operator!=(const T& val, const Rational<T>& rhs){
	if(rhs.n()!=val || rhs.d()!=1) return true;
	else return false;
};

  
template<class T, class charT, class traits>
  std::basic_ostream<charT,traits>&
    operator<< (std::basic_ostream<charT,traits>& ostr, const Rational<T>& rhs){
		std::basic_ostringstream<charT,traits>  s;
		s  << rhs.n() << '/' << rhs.d();
 	   return ostr << s.str();
};

template<class T, class charT, class traits>
  std::basic_istream<charT,traits>&
    operator>> (std::basic_istream<charT,traits>& istr, Rational<T>& rhs){
    	//std::basic_istringstream<charT,traits>  s;
	    T    a = T();
	    T    b = T();    
		istr >> a;	
	    charT ch = charT();
	   	char cc;
	    istr >> ch;                         
		cc = ch;
        if (cc == '/') 
     	{	
			//s.putback(ch);
		   	istr >> b;   
			   
			if(b ==T(0) ) throw std::invalid_argument("0 in denominator");
			
            rhs = Rational<T>(a,b);
        }
        else                        // error
       	{
  			  istr.setstate(::std::ios_base::failbit);
        }
		return istr;
    };
#endif