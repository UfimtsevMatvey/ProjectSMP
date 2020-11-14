all: SMPemu

SMPemu: maincpp.o core.o mem.o regf.o subfunc.o
	c++ maincpp.o core.o mem.o regf.o subfunc.o -o smpemu

maincpp.o:
	c++ -c maincpp.cpp

core.o:
	c++ -c core.cpp

mem.o:
	c++ -c mem.cpp

regf.o:
	c++ -c regf.cpp

subfunc.o:
	c++ -c subfunc.cpp

clean:
	rm -rf *.o smpemu