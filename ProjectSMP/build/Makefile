CXX = c++
CXXFLAGS = -Wall

all: SMPemu

SMPemu: maincpp.o core.o mem.o regf.o subfunc.o logicFunctors.o
	$(CXX) $(CXXFLAGS) maincpp.o core.o mem.o regf.o subfunc.o logicFunctors.o -o smpemu

maincpp.o:
	$(CXX) $(CXXFLAGS) -c ../maincpp.cpp

core.o:
	$(CXX) $(CXXFLAGS) -c ../core.cpp

mem.o:
	$(CXX) $(CXXFLAGS) -c ../mem.cpp

regf.o:
	$(CXX) $(CXXFLAGS) -c ../regf.cpp

subfunc.o:
	$(CXX) $(CXXFLAGS) -c ../subfunc.cpp

logicFunctors.o:
	$(CXX) $(CXXFLAGS) -c ../logicFunctors.cpp

clean:

	rm -rf *.o smpemu 