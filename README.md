# Algebraic Template Library

Header files for algebraic structures and symbolic computation in C++.
Attempts algebraic completeness through generic programming with operator overloading. 
Currently supported:

Rational.hh:  rational types (ie fractional fields for rings),

ie Rational =type(a)/type(a).

Quotients.hh: Quotients of rings
(base ring static member)

ie Quotient = type(a) % type(b).

Residue.hh: For convenience, same operators as Quotient, but with type restricted to integral types.
(Base ring defined at compile time). 

Polynomial.hh: Polynomial rings over arbitrary field types.

With these one can build other Field types, eg rational functions, finite fields.

******************************************************************************************************

Not implemented

Quadratic rings/fields, Quaternions, Multi-varaiate polynomials & Grobner bases.
Its a work in progress, happy for requests!
