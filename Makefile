CXX=g++

main:
	$(CXX) -Og -o chess src/main.cpp -std=c++17 -Ilibs/include -Llibs/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

run: main
	./chess.exe