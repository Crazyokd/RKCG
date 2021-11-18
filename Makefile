.PHNOY : clean

CXXFLAGS := -g -I include

apps := hello.exe exp_3.exe
objects := hello.o exp_3.o
sources := hello.cpp hello.cpp

test: exp_3.exe
	$<

all: $(apps)

$(apps): %.exe: %.o

$(objects): %.o: %.cpp

%.exe : %.o
	$(CXX) -fdiagnostics-color=always \
		$< \
		-o $@ \
		-L lib \
		-lgraphics64 \
		-luuid \
		-lmsimg32 \
		-lgdi32 \
		-limm32 \
		-lole32 \
		-loleaut32 \
		-lwinmm \
		-lgdiplus \

clean :
	del $(wildcard *.o) $(wildcard *.exe)