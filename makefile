make:
	g++ src/*.cpp -o bin -lsfml-graphics -lsfml-window -lsfml-system -lGLU -lGL
	./bin
	rm bin

install:
	sudo pacman -S glu
	sudo pacman -S sfml