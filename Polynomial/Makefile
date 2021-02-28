TARGET =
#IDIR =../include
#CC=g++
CC=g++-9
#CC = clang++
CPPFLAGS= -std=c++14 
#-I$(IDIR)
#ODIR=obj
LIBS =-lm -lgmpxx -lgmp

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
#HEADERS=pascaltri.hh binomial_coeff.hh MyFrac.hh Quadr.hh
HEADERS = $(wildcard *.hh)
%.o: %.cpp $(HEADERS)
	$(CC) $(CPPFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@
	
test: test_Polynomial.o
	$(CC) -o $@ $^ $(CPPFLAGS) $(LIBS)

clean:
	-rm -f *.o