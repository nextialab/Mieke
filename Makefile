mieke: main.cpp agent.cpp
	clang++ -std=c++11 -stdlib=libc++ -o mieke main.cpp agent.cpp -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo