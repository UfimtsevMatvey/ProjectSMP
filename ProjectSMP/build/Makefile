CXX = g++
CXXFLAGS = -Wall -g -march='znver1'  -mavx512f -mavx512cd -masm=intel

all: SMPemu

SMPemu: maincpp.o core.o mem.o regf.o subfunc.o testClass.o
	$(CXX) $(CXXFLAGS) maincpp.o core.o mem.o regf.o subfunc.o testClass.o -o smpemu.out

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

testClass.o:
	$(CXX) $(CXXFLAGS) -c ../testClass.cpp

clean:

	rm -rf *.o smpemu 
