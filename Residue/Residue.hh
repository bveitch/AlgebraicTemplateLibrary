#ifndef RESIDUE_HH
#define RESIDUE_HH

#include <assert.h>     /* assert */
#include <string>
#include <sstream>
#include <iostream>
#include "../Utilities/NumTheoryUtils.hh"
#include <functional> 

template <class T, int Prime>
struct modF {
  		
  	int operator()(T x) const { 
		  int ans = x % Prime;
		  return (ans<0 ? ans + Prime: ans); 
	}

};

template <class T, int Prime>
class Residue{
	int a_;

	modF<T,Prime> mod_;
	

public:
	
	Residue(){
		a_=0;
	};
	
	Residue(const T& a){
		a_=mod_(a);
	};
	
	Residue(const Residue<T,Prime>& res){
		a_=res.a_;
	};
	
	int value() const { return a_; };
	
	Residue& operator=(const T& n){
		a_=mod_(n);
		return *this;
	};
	
	Residue& operator*= (const T& n){
		auto a=mod_(n);
		a_*=a;
		a_= mod_(a_);
		return *this;
	};
	
	Residue& operator/= (const T& n){
		T x;
		T y;
		auto a=mod_(n);
		auto d=NTUtils::euclid(a, static_cast<signed int>(Prime), x , y);
		if( a_ % d == 0) {
			a_=(a_/d)*x;
			a_=mod_(a_);
		}
		else a_=T(0);
		return *this;	
	};
	
	bool operator==(const T& n){
		if(a_==mod_(n)) return true;
		else return false;
	};
	
	template <class pT>
	Residue& pow(pT n){
		auto& a=*this;
		auto N = n % (Prime - 1);
		*this=NTUtils::fast_exp_bits( a, N);
		return *this;
	};
	
	Residue& operator+= (const T& n){
		auto a=mod_(n);
		a_+=a;
		a_= mod_(a_);
		return *this;
	};
	
	Residue& operator-= (const T& n){
		auto a=mod_(n);
		a_-=a;
		a_= mod_(a_);
		return *this;
	};
	
	Residue& operator+= (const Residue<T, Prime>& rhs){
		return (*this)+=rhs.value();
	};
	
	Residue& operator-= (const Residue<T, Prime>& rhs){
		return (*this)-=rhs.value();
	};
	
	Residue& operator*= (const Residue<T, Prime>& rhs){
		return (*this)*=rhs.value();
	};
	
	Residue& operator/= (const Residue<T, Prime>& rhs){
		return (*this)/=rhs.value();
	};
	
	bool operator == (const Residue<T, Prime>& rhs){
		if(a_==rhs.value() ) return true;
		else return false;
	};
	
};

template<class T, int Prime> Residue<T,Prime> operator+(const Residue<T,Prime>& lhs, const Residue<T,Prime>& rhs){
	auto f=lhs;
	return f+=rhs; 
};

template<class T, int Prime> Residue<T,Prime> operator+(const Residue<T,Prime>& lhs, const T& val){
	auto f=lhs;
	return f+=val; 
};

template<class T, int Prime> Residue<T,Prime> operator+(const T& val, const Residue<T,Prime>& rhs){
	auto f=Residue<T,Prime>(val);
	return f+=rhs;
};

template<class T, int Prime> Residue<T,Prime> operator-(const Residue<T,Prime>& lhs, const Residue<T,Prime>& rhs){
	auto f=lhs;
	return f-=rhs; 
};

template<class T, int Prime> Residue<T,Prime> operator-(const Residue<T,Prime>& lhs, const T& val){
	auto f=lhs;
	return f-=val; 
};

template<class T, int Prime> Residue<T,Prime> operator-(const T& val, const Residue<T,Prime>& rhs){
	auto f=Residue<T,Prime>(val);
	return f-=rhs;
};;

template<class T, int Prime> Residue<T,Prime> operator*(const Residue<T,Prime>& lhs, const Residue<T,Prime>& rhs){
	auto f=lhs;
	return f*=rhs;
};

template<class T, int Prime> Residue<T,Prime> operator*(const Residue<T,Prime>& lhs, const T& val){
	auto f=lhs;
	return f*=val;
};

template<class T, int Prime> Residue<T,Prime> operator*(const T& val, const Residue<T,Prime>& rhs){
	auto f=Residue<T,Prime>(val);
	return f*=rhs;
};

template<class T, int Prime> Residue<T,Prime> operator/(const Residue<T,Prime>& lhs, const Residue<T,Prime>& rhs){
	auto f=lhs;
	return f/=rhs;
};

template<class T, int Prime> Residue<T,Prime> operator/(const Residue<T,Prime>& lhs, const T& val){
	auto f=lhs;
	return f/=val;
};

template<class T, int Prime> Residue<T,Prime> operator/(const T& val, const Residue<T,Prime>& rhs){
	auto f=Residue<T,Prime>(val);
	return f/=rhs;
};

template<class T, int Prime> Residue<T,Prime> operator-(const Residue<T,Prime>& rhs){
	auto f=rhs;
	return f*=T(-1);
};

template<class T, int Prime>
bool operator==(const Residue<T,Prime>& lhs, const Residue<T,Prime>& rhs){
	return lhs==rhs;
};

template<class T, int Prime>
bool operator==(const Residue<T,Prime>& lhs, const T& val){
	return lhs==val;
};

template<class T, int Prime>
bool operator==(const T& val, const Residue<T,Prime>& rhs){
	auto f=Residue<T,Prime>(val);
	return f==rhs;
};

template<class T, int Prime>
bool operator!=(const Residue<T,Prime>& lhs, const Residue<T,Prime>& rhs){
	return !(lhs==rhs);
};

template<class T, int Prime>
bool operator!=(const Residue<T,Prime>& lhs, const T& val){
	return !(lhs==val);
};

template<class T, int Prime>
bool operator!=(const T& val, const Residue<T,Prime>& rhs){
	return !(val==rhs);
};

  
template<class T, int Prime,class charT, class traits>
  std::basic_ostream<charT,traits>&
    operator<< (std::basic_ostream<charT,traits>& ostr, const Residue<T,Prime>& rhs){
		std::basic_ostringstream<charT,traits>  s;
		s  << rhs.value() << " mod " << Prime;
 	   return ostr << s.str();
};

template<class T, int Prime,class charT, class traits>
  std::basic_istream<charT,traits>&
    operator>> (std::basic_istream<charT,traits>& istr, Residue<T,Prime>& rhs){
	    auto    a = T();
		istr >> a; 
        rhs = Residue<T,Prime>(a);
		return istr;
    };
#endif