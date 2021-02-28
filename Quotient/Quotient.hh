/**
description : Quotient on ring
author      : bveitch
version     : 1.0
project     : AlgebraicTemplateLibrary
date        : Sunday 28th February  
*/

#ifndef QUOTIENT_HH
#define QUOTIENT_HH

#include <assert.h>     /* assert */
#include <string>
#include <sstream>
#include <iostream>
#include "../Utilities/NumTheoryUtils.hh"


template <class T>
class Quotient{
		
public:

	T a_;
	static T m;

	Quotient(){
		a_=T(0);
	};
	
	Quotient(const T& a){
		a_=a % Quotient<T>::m;
		if(a_<static_cast<T>(0)) a_+=Quotient<T>::m;
	};
	
	Quotient(const Quotient& res){
		a_=res.a_;
	};
	
	T value() const {
		return a_;
	}

	Quotient& operator=(const T& n){
		a_=n % Quotient<T>::m;
		if(a_<static_cast<T>(0)) a_+=Quotient<T>::m;
		return *this;
	};
	
	Quotient& operator= (const Quotient& rhs){
		a_=rhs.a_;
		return *this;
	};

	Quotient& operator*= (const T& n){
		auto a=n % Quotient<T>::m;
		if(a<static_cast<T>(0)) a+=Quotient<T>::m;
		a_*=a;
		a_= a_ % m;
		return *this;
	};
	
	Quotient<T>& operator/= (const T& n){
		T x;
		T y;
		auto a=n % Quotient<T>::m;
		auto d=euclid(a,Quotient<T>::m, x , y);
		if( a_ % d == 0) {
			a_=(a_/d)*x;
			a_=a_ % Quotient<T>::m;
		}
		if(a_<static_cast<T>(0)) a_+=Quotient<T>::m;
		return *this;	
	};
	
	bool operator==(const T& n){
		if(a_==n) return true;
		else return false;
	};
	
	template <class pT>
	Quotient<T>& pow(pT n){
		auto& a=*this;
		*this=NTUtils::fast_exp_bits( a, n );
		return *this;
	};
	
	Quotient<T>& operator+= (const T& n){
		auto a=n % m;
		if(a<static_cast<T>(0)) a+=Quotient<T>::m;
		a_+=a;
		a_= a_ % Quotient<T>::m;
		return *this;
	};
	
	Quotient<T>& operator-= (const T& n){
		auto a=n % m;
		if(a<static_cast<T>(0)) a+=Quotient<T>::m;
		a_-=a;
		a_= a_ % Quotient<T>::m;
		if(a_<static_cast<T>(0)) a_+=Quotient<T>::m;
		return *this;
	};
	
	Quotient<T>& operator+= (const Quotient<T>& rhs){
		auto b=rhs.a_;
		a_+=b;
		a_= a_ % Quotient<T>::m;
		return *this;
	};
	
	Quotient<T>& operator-= (const Quotient<T>& rhs){
		auto b=rhs.a_;
		a_-=b;
		a_= a_ % m;
		if(a_<static_cast<T>(0)) a_+=Quotient<T>::m;
		return *this;
	};
	
	Quotient<T>& operator*= (const Quotient<T>& rhs){
		auto b=rhs.a_;
		a_*=b;
		a_= a_ % Quotient<T>::m;
		return *this;
	};
	
	Quotient<T>& operator/= (const Quotient<T>& rhs){
		T x;
		T y;
		auto d=NTUtils::euclid( rhs.a_,Quotient<T>::m, x , y);
		if( a_ % d == 0) {
			a_=(a_/d)*x;
			a_=a_ % Quotient<T>::m;
		}
		if(a_<static_cast<T>(0)) a_+=Quotient<T>::m;
		return *this;	
	};
	
	bool operator == (const Quotient<T>& rhs){
		if(a_==rhs.a_ ) return true;
		else return false;
	};
	
};

template<class T>
T Quotient<T>::m=T(1);

template<class T> Quotient<T> operator+(const Quotient<T>& lhs, const Quotient<T>& rhs){
	auto f=lhs;
	return f+=rhs; 
};

template<class T> Quotient<T> operator+(const Quotient<T>& lhs, const T& val){
	auto f=lhs;
	return f+=val; 
};

template<class T> Quotient<T> operator+(const T& val, const Quotient<T>& rhs){
	auto f=Quotient<T>(val);
	return f+=rhs;
};

template<class T> Quotient<T> operator-(const Quotient<T>& lhs, const Quotient<T>& rhs){
	auto f=lhs;
	return f-=rhs; 
};

template<class T> Quotient<T> operator-(const Quotient<T>& lhs, const T& val){
	auto f=lhs;
	return f-=val; 
};

template<class T> Quotient<T> operator-(const T& val, const Quotient<T>& rhs){
	auto f=Quotient<T>(val);
	return f-=rhs;
};;

template<class T> Quotient<T> operator*(const Quotient<T>& lhs, const Quotient<T>& rhs){
	auto f=lhs;
	return f*=rhs;
};

template<class T> Quotient<T> operator*(const Quotient<T>& lhs, const T& val){
	auto f=lhs;
	return f*=val;
};

template<class T> Quotient<T> operator*(const T& val, const Quotient<T>& rhs){
	auto f=Quotient<T>(val);
	return f*=rhs;
};

template<class T> Quotient<T> operator/(const Quotient<T>& lhs, const Quotient<T>& rhs){
	auto f=lhs;
	return f/=rhs;
};

template<class T> Quotient<T> operator/(const Quotient<T>& lhs, const T& val){
	auto f=lhs;
	return f/=val;
};

template<class T> Quotient<T> operator/(const T& val, const Quotient<T>& rhs){
	auto f=Quotient<T>(val);
	return f/=rhs;
};

template<class T> Quotient<T> operator-(const Quotient<T>& rhs){
	auto f=rhs;
	return f*=T(-1);
};

template<class T>
bool operator==(const Quotient<T>& lhs, const Quotient<T>& rhs){
	return lhs==rhs;
};

template<class T>
bool operator==(const Quotient<T>& lhs, const T& val){
	return lhs==val;
};

template<class T>
bool operator==(const T& val, const Quotient<T>& rhs){
	auto f=Quotient<T>(val);
	return f==rhs;
};

template<class T>
bool operator!=(const Quotient<T>& lhs, const Quotient<T>& rhs){
	return !(lhs==rhs);
};

template<class T>
bool operator!=(const Quotient<T>& lhs, const T& val){
	return !(lhs==val);
};

template<class T>
bool operator!=(const T& val, const Quotient<T>& rhs){
	return !(val==rhs);
};

  
template<class T, class charT, class traits>
  std::basic_ostream<charT,traits>&
    operator<< (std::basic_ostream<charT,traits>& ostr, const Quotient<T>& rhs){
		std::basic_ostringstream<charT,traits>  s;
		s  << rhs.a_ << " mod " << rhs.m;
 	   return ostr << s.str();
};

template<class T, class charT, class traits>
  std::basic_istream<charT,traits>&
    operator>> (std::basic_istream<charT,traits>& istr, Quotient<T>& rhs){
	    auto    a = T();
		istr >> a; 
        rhs = Quotient<T>(a);
		return istr;
    };
#endif