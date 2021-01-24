CXX = g++
CXXFLAGS = -Wall -g  -mavx  -masm=intel

all: SMPemu

SMPemu: maincpp.o core.o mem.o regf.o subfunc.o testClass.o checkArh.o
	$(CXX) $(CXXFLAGS) maincpp.o core.o mem.o regf.o subfunc.o testClass.o checkArh.o -o smpemu.out

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

checkArh.o:
	$(CXX) $(CXXFLAGS) -c ../checkArh.cpp

clean:
	rm -rf *.o smpemu 
