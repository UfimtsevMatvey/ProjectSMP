CXX = g++ 
CXXFLAGS = -Wall -g  -mavx  -masm=intel

all: SMPemu
	rm -rf *.o smpemu 
	
SMPemu: maincpp.o core.o mem.o regf.o subfunc.o testClass.o checkArh.o cmd_line.o emu_display.o emu_keyboard.o device.o subline.o
	$(CXX) $(CXXFLAGS) maincpp.o core.o mem.o regf.o subfunc.o testClass.o checkArh.o cmd_line.o emu_display.o subline.o emu_keyboard.o device.o -o smpemu.out

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

cmd_line.o:
	$(CXX) $(CXXFLAGS) -c ../cmd_line.cpp

emu_display.o:
	$(CXX) $(CXXFLAGS) -c ../emu_display.cpp

emu_keyboard.o:
	$(CXX) $(CXXFLAGS) -c ../emu_keyboard.cpp

device.o:
	$(CXX) $(CXXFLAGS) -c ../device.cpp

subline.o:
	$(CXX) $(CXXFLAGS) -c ../subline.cpp
clean:
	rm -rf *.o smpemu 
