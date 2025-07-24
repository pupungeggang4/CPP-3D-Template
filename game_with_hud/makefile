window:
	clang++ *.cpp script/*.cpp ../glad/src/glad.c -o main -I ../glad/include -lSDL3 -lSDL3_image -lSDL3_ttf -lglfw3 -w -std=c++11

macbrew:
	clang++ *.cpp script/*.cpp ../glad/src/glad.c -o main -I ../glad/include -I /opt/homebrew/include -lSDL3 -lSDL3_image -lSDL3_ttf -lglfw3 -w -std=c++11

linuxbrew:
	clang++ *.cpp ../glad/src/glad.c -o main -I /home/linuxbrew/.linuxbrew/include -I ../glad/include -L /home/linuxbrew/.linuxbrew/lib -lSDL3 -lSDL3_image -lSDL3_ttf -lglfw -w

dummy:
