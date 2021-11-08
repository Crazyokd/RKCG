exp_3.exe : exp_3.cpp
	g++ -fdiagnostics-color=always \
		-g exp_3.cpp \
		-o exp_3.exe \
		-I include \
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

hello.exe : hello.cpp
	g++ -fdiagnostics-color=always \
		-g hello.cpp \
		-o hello.exe \
		-I include \
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
