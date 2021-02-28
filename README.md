# Algebraic Template Library

Header files for algebraic structures and symbolic computation in C++.
Attempts algebraic completeness through generic programming and operator overloading. 
Currently supported:


Rational.hh:  rational types (ie fractional fields for rings),

ie Rational =type(a)/type(a).

Quotients.hh: Quotients of rings

ie Quoteint = type(a) % type(b).

For convenience Residue.hh also computes the above but with type restricted to integral types.

Polynomial.hh: Rings over arbitrary field types.

With these once can build other Field types, eg rational functions, finite fields.
******************************************************************************************************

Not implemented

Quadratic rings/fields, Quaternions, Multi-varaiate polynomials & Grobner bases.
Its a work in progress, happy for requests!
