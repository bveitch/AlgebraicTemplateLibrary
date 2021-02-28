
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

template <class T>
void print(std::ofstream& file, T & lhs, T& rhs){
    file << "lhs : " << lhs << " , " << "rhs : " << rhs << "\n";
}

namespace AlgTests {
    
    template<class T>
    bool test_error(std::string test, T lhs,T rhs){
        bool pass = ( rhs == lhs);
        std::cerr << test << ": lhs =" << lhs << " rhs = " << rhs << std::endl;
        return pass;
    }

    template<class T, class Predicate>
    bool test_compare(std::string comparison, T lhs,T rhs, Predicate pred){
        bool pass = pred( lhs, rhs);
        if(pass){
            std::cerr << "(" << lhs << " " << comparison << " " << rhs << ") = True " << std::endl;
        }
        else{
            std::cerr << "(" << lhs << " " << comparison << " " << rhs << ") = False " << std::endl;
        }
        return pass;
    }

    template <class T, class BinaryOp>
    bool test_associative(T& a, T&b, T&c, BinaryOp f, std::ofstream& file){

        T lhs = f( f(a,b),c );
        T rhs = f(a, f(b,c) );
        bool pass = (lhs == rhs);
        if(!pass) print(file,lhs,rhs);
        return pass;
    };

    template <class T, class BinaryOp1, class BinaryOp2>
    bool test_left_distributive(T&a, T&b, T&c, BinaryOp1 add, BinaryOp2 mult, std::ofstream& file){

        T lhs = mult(a, add(b,c));
        T rhs = add( mult(a,b), mult(a,c));
        bool pass = (lhs == rhs);
        if(!pass) print(file,lhs,rhs);
        return pass;
    }

    template <class T, class BinaryOp1, class BinaryOp2>
    bool test_right_distributive(T&a, T&b, T&c, BinaryOp1 add, BinaryOp2 mult, std::ofstream& file){

        T lhs = mult(add(a,b),c);
        T rhs = add( mult(a,c), mult(b,c));
        bool pass = (lhs == rhs);
        if(!pass) print(file,lhs,rhs);
        return pass;
    }

    template <class T, class BinaryOp>
    bool test_commutative(T& a, T& b, BinaryOp op, std::ofstream& file){

        T lhs = op(a,b);
        T rhs = op(b,a);
        bool pass = (lhs == rhs);
        if(!pass) print(file,lhs,rhs);
        return pass;
    }

    template <class T, class BinaryOp>
    bool test_left_identity(T& id, T& a, BinaryOp op, std::ofstream& file){

        T lhs = op(id,a);
        bool pass = (lhs == a);
        if(!pass) print(file,lhs,a);
        return pass;
    }

    template <class T, class BinaryOp>
    bool test_right_identity(T& a, T& id, BinaryOp op, std::ofstream& file){

        T lhs = op(a,id);
        bool pass = (lhs == a);
        if(!pass) print(file,lhs,a);
        return pass;
    }

    template <class T, class BinaryOp, class UnaryOp>
    bool test_left_inverse(T& a, T& id, BinaryOp op, UnaryOp inv, std::ofstream& file){

        T lhs = op(inv(a),a);
        bool pass = (lhs == id);
        if(!pass) print(file,lhs,id);
        return pass;
    }

    template <class T, class BinaryOp, class UnaryOp>
    bool test_right_inverse(T& a, T& id, BinaryOp op, UnaryOp inv, std::ofstream& file){

        T lhs = op(a,inv(a));
        bool pass = (lhs == id);
        if(!pass) print(file,lhs,id);
        return pass;
    }

}