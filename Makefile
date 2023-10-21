game:
	g++ main.cpp -o play -I include/freetype2 -I include -I include/SDL2 -I include/libpng16 -L lib -lSDL2 -lSDL_mixer -lSDL_ttf -l SDL2-2.0.0 -lSDL2_image -lSDL_ttf