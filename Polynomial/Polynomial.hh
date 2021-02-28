/**
description : Polynomial class
author      : bveitch
version     : 1.0
project     : AlgebraicTemplateLibrary
date        : Sunday 28th February  
*/

#ifndef POLYNOMIAL_HH
#define POLYNOMIAL_HH

#include <sstream>
#include <iostream>
#include <deque>
#include <functional>   // std::minus
#include <numeric>      // std::accumulate
#include <algorithm>  

template <class T>
class Polynomial {
	std::deque<T> coeff;
 
 	void pop_back(){
		 coeff.pop_back();
 	}
 
 	T back() const {
	 	return coeff.back();
 	}
	
	void trim(){
		//recheck;
		//auto size_=size()+1;
		auto rit=std::find_if(rbegin(),rend(), [&](T c)
		{
			//size_--;
			return (c != T(0));
		});
		//resize(size_);
		if(rit!=rend()){
			resize(std::distance(rit, rend()) );
		}
		else {
			resize(1);
			coeff[0]=0;
		}
	}
	
	void quot_rem(const Polynomial<T>& A, const Polynomial<T>& B, 
				Polynomial<T>& Q, Polynomial<T>& R)
	{
		Q.reset();
		R.reset();
		Polynomial<T> AA(A);
		
		auto Qdeg=A.degree() - B.degree();
		Q.resize(Qdeg + 1);
		R.resize(A.size() );
		for(auto k = Qdeg;k>=0; k--)
			{
				Polynomial<T> BB=B;
				BB.shift_fwd(k);
				T rat=( AA.lcoeff()/BB.lcoeff() );
				for_each(BB.begin(), BB.end(), [&](T& b)
					{
						b*=rat;
					});
				std::transform (AA.begin(), AA.end(), BB.begin(), AA.begin(), std::minus<T>());
				auto r=AA.back();
				AA.pop_back();
				Q[k]=rat;
			};
		R = A - Q*B;
	};
		
public:
	
	Polynomial(){
		coeff.push_back(T(0));
	};
	
	Polynomial(const T& a){
		coeff.push_back(a);
	};
	
	Polynomial(const T& a, const T& b){
		coeff.push_back(a);
		coeff.push_back(b);
	};
	
	Polynomial(const T a, const T b, const T c){
		coeff.push_back(a);
		coeff.push_back(b);
		coeff.push_back(c);
	};

	Polynomial(const std::vector<T> v){
		coeff.resize(v.size());
		std::copy ( v.begin(), v.end(), coeff.begin() );
		reverse(coeff.begin(),coeff.end());
	};

	typename std::deque<T>::iterator begin() { return coeff.begin(); };
	typename std::deque<T>::iterator end() { return coeff.end(); };
	typename std::deque<T>::const_iterator cbegin() const { return coeff.cbegin(); };
	typename std::deque<T>::const_iterator cend() const { return coeff.cend(); };
	typename std::deque<T>::reverse_iterator rbegin() { return coeff.rbegin(); };
	typename std::deque<T>::reverse_iterator rend() { return coeff.rend(); };
	typename std::deque<T>::const_reverse_iterator crbegin() const { return coeff.crbegin(); };
	typename std::deque<T>::const_reverse_iterator crend() const { return coeff.crend(); };
	
	void resize(int i) { coeff.resize(i);}
 	
	void resize(int n, T c){
	 	coeff.resize(n,c);
 	}
	
	int degree() const{ return coeff.size()-1; }

	int size() const{ return coeff.size();};
	
	T lcoeff() const { 
		return coeff[coeff.size()-1];
	 };
	
	 T operator[](int n) const {
		 if( n < coeff.size() ) return coeff[n];
		 else return T(0);
	 }
	
	 T& operator[](int n) {
		 return coeff.at(n);
	 }
	 
	 void reset(){
		 coeff.clear();
		 coeff.push_back(T(0));
	 }
	 
	
	 template <class vType>
	 vType operator()(const vType& v) const {
		 if(coeff.size()==1) return coeff[0];
		 return std::accumulate (crbegin(), crend(), vType(0), [&](vType ans, T c )
		{
			ans*=v;
			ans+=c;
			return ans;
		});
	 }
	 
	 void deriv(){
		 int i=0;
		 for_each(coeff.begin(),coeff.end(),[&](T& c)
			{
				c*=i;
				i++;
			});
		shift_bwd();
	 }
	 
	 void shift_bwd(int i=1){
		 if(i==1){
			 coeff.pop_front();
		 }
		 else if (i>1){
		 	coeff.erase (coeff.begin(),coeff.begin()+i);
			
		 }
	 } 
	 
	 void shift_fwd(int i=1){
		 if(i==1){
			 coeff.push_front( T(0) );
		 }
		 else if (i>1){
		 	coeff.insert (coeff.begin(),i,T(0) );
			
		 }
	 }
	
	 
	bool operator==(const Polynomial<T>& rhs) const{
		if(this->degree()!=rhs.degree()) return false;
		return std::equal (coeff.cbegin(), coeff.cend(), rhs.cbegin() );
	}
	
	bool operator!=(const Polynomial<T>& rhs) const {
		return !(this==rhs);
	}
	
	bool operator<(const Polynomial<T>& rhs) const {
		if(degree()<rhs.degree() ) {
			return (lcoeff() > 0 );
		}
		else if(degree()>rhs.degree() ) {
			return (rhs.lcoeff() <0 );
		}
		else {
			auto pair= std::mismatch (coeff.crbegin(), coeff.crend(), rhs.crbegin() );
			return (pair.first < pair.second );
		}
	}
	
	bool operator>(const Polynomial<T>& rhs){
		if(degree()>rhs.degree() ) {
			return (lcoeff() > 0 );
		}
		else if(degree()<rhs.degree() ) {
			return (rhs.lcoeff() <0 );
		}
		else {
			auto pair= std::mismatch (coeff.crbegin(), coeff.crend(), rhs.crbegin() );
			return (pair.first > pair.second );
		}
	}
	bool operator<=(const Polynomial<T>& rhs){
		return !(lcoeff() >rhs.lcoeff() );
	}
	
	bool operator>=(const Polynomial<T>& rhs){
		return !(lcoeff() < rhs.lcoeff() );
	}
	
	
	
	Polynomial<T>& operator-(){
		for_each(begin(),end(),std::negate<T>());
		return *this;
	};
	
	
	Polynomial<T>& operator+= (const T& v){
		coeff[0]+=v;
		return *this;
	};
	
	Polynomial<T>& operator-= (const T& v){
		coeff[0]-=v;
		return *this;
	};

	Polynomial<T>& operator*= (const T& v){
		for_each(begin(),end(),[&](T& c)
			{
				c*=v;
			});
		return *this;
	};
	
	Polynomial<T>& operator/= (const T& v){
		for_each(begin(),end(),[&](T& c)
			{
				c/=v;
			});
		return *this;
	};
	
	Polynomial<T>& operator%= (const T& v){
		for_each(begin(),end(),[&](T& c)
			{
				c%=v;
			});
		return *this;
	};

	Polynomial<T>& operator+= (const Polynomial<T>& rhs){
		if(rhs.degree() > degree() ){
			resize(rhs.size());
		}
		auto iend=rhs.size();
		std::transform (begin(), begin()+iend, rhs.cbegin(), begin(), std::plus<T>());
		trim();
		return *this;
	};
	
	Polynomial<T>& operator-= (const Polynomial<T>& rhs){
		if(rhs.degree() > degree() ){
			resize(rhs.size());
		}
		auto iend=rhs.size();
		std::transform (begin(), begin()+iend, rhs.cbegin(), begin(), std::minus<T>());
		trim();
		return *this;
	};
	
	Polynomial<T>& operator*= (const Polynomial<T>& that){
		if(that.degree()==0)
		{
			(*this)*=that[0];
			return *this;
		}
		else if(that.degree()==1)
		{
			auto a=*this;
			a*=that[0];
			shift_fwd();
			(*this)*=that[1];
			(*this)+=a;	
		}
		else 
		{
			auto deg_a=this->degree();
			std::deque<T> a(deg_a+that.degree()+1);
			for(auto i=0; i < a.size(); i++){
				auto P=std::max(0, i-that.degree() );
				auto Q=std::min(i,deg_a );
				auto QR=std::max(0,that.degree()-i );
				auto it=that.crbegin() + QR;
				for(auto jt=begin()+P ; jt<= begin()+Q; jt++, it++) a[i]+=(*jt)*(*it);
			}
			resize(a.size() );
			std::copy ( a.begin(), a.end(), begin() );
		}
		return *this;
	};
	
	Polynomial<T>& operator/= (const Polynomial<T>& rhs){
		Polynomial<T> Q;
		Polynomial<T> R;
		quot_rem(*this,rhs,Q,R);
		*this=Q;
		return *this;
	};
	
	Polynomial<T>& operator%= (const Polynomial<T>& rhs){
		Polynomial<T> Q;
		Polynomial<T> R;
		quot_rem(*this,rhs,Q,R);
		*this=R;
		return *this;
	};
};

template<class T> 
inline Polynomial<T> operator+(const Polynomial<T>& lhs, const Polynomial<T>& rhs){
	auto f=lhs;
	return f+=rhs; 
};

template<class T> 
inline Polynomial<T> operator+(const Polynomial<T>& lhs, const T& val){
	auto f=lhs;
	return f+=val; 
};

template<class T> 
inline Polynomial<T> operator+(const T& val, const Polynomial<T>& rhs){
	auto f=Polynomial<T>(val);
	return f+=rhs;
};

template<class T> 
inline Polynomial<T> operator-(const Polynomial<T>& lhs, const Polynomial<T>& rhs){
	auto f=lhs;
	return f-=rhs; 
};

template<class T> 
inline Polynomial<T> operator-(const Polynomial<T>& lhs, const T& val){
	auto f=lhs;
	return f-=val; 
};

template<class T> 
inline Polynomial<T> operator-(const T& val, const Polynomial<T>& rhs){
	auto f=Polynomial<T>(val);
	return f-=rhs;
};;

template<class T> 
Polynomial<T> operator*(const Polynomial<T>& lhs, const Polynomial<T>& rhs){
	auto f=lhs;
	return f*=rhs;
};

template<class T> 
inline Polynomial<T> operator*(const Polynomial<T>& lhs, const T& val){
	auto f=lhs;
	return f*=val;
};

template<class T> 
inline Polynomial<T> operator*(const T& val, const Polynomial<T>& rhs){
	auto f=Polynomial<T>(val);
	return f*=rhs;
};

template<class T> 
inline Polynomial<T> operator/(const Polynomial<T>& lhs, const Polynomial<T>& rhs){
	auto f=lhs;
	return f/=rhs;
};

template<class T> 
inline Polynomial<T> operator/(const Polynomial<T>& lhs, const T& val){
	auto f=lhs;
	return f/=val;
};

template<class T> 
inline Polynomial<T> operator/(const T& val, const Polynomial<T>& rhs){
	auto f=Polynomial<T>(val);
	return f/=rhs;
};

template<class T> 
inline Polynomial<T> operator%(const Polynomial<T>& lhs, const Polynomial<T>& rhs){
	auto f=lhs;
	return f%=rhs;
};

template<class T> 
inline Polynomial<T> operator%(const Polynomial<T>& lhs, const T& val){
	auto f=lhs;
	return f%=val;
};

template<class T> 
inline Polynomial<T> operator%(const T& val, const Polynomial<T>& rhs){
	auto f=Polynomial<T>(val);
	return f%=rhs;
};
template<class T, class charT, class traits>
inline   std::basic_ostream<charT,traits>&
    operator<< (std::basic_ostream<charT,traits>& ostr, const Polynomial<T>& rhs){
		std::basic_ostringstream<charT,traits>  s;
		for(auto i=rhs.degree() ; i>=0; i--){
			if(i >1 ){
				s << rhs[i] << "*x^" << i << " + ";
			}
			else if(i == 1 ){
				s << rhs[i] << "*x" << " + ";
			}
			else{
				s<< rhs[0];
			} 
		}
 	   return ostr << s.str();
};

template<class T, class charT, class traits>
inline   std::basic_istream<charT,traits>&
    operator>> (std::basic_istream<charT,traits>& istr, Polynomial<T>& rhs){
	    auto    a = T();
		istr >> a; 
        //rhs = Polynomial<T>(a);
		return istr;
    };
#endif