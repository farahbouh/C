all: bin/mainTest1 bin/mainsdl

bin/mainsdl: obj/mainsdl.o obj/AffichageSDL.o obj/Image.o obj/De.o obj/Jeu.o obj/Joueur.o obj/Pion.o obj/Color.o
	g++ -ggdb -Wall obj/mainsdl.o obj/AffichageSDL.o obj/Image.o obj/De.o obj/Jeu.o obj/Joueur.o obj/Pion.o obj/Color.o -o bin/mainsdl $(shell sdl2-config --libs) -lSDL2_mixer -lSDL2_image -lSDL2_ttf

bin/mainTest1: obj/mainTest1.o obj/AffichageSDL.o obj/Jeu.o obj/Joueur.o obj/Pion.o obj/De.o obj/Color.o obj/Image.o
	g++ -ggdb -Wall obj/mainTest1.o obj/AffichageSDL.o obj/Jeu.o obj/Joueur.o obj/Pion.o obj/De.o obj/Color.o obj/Image.o -o bin/mainTest1 $(shell sdl2-config --libs) -lSDL2_mixer -lSDL2_image -lSDL2_ttf
	
obj/mainTest1.o: src/mainTest1.cpp 	src/AffichageSDL.h src/Jeu.h src/Joueur.h src/Pion.h src/De.h src/Color.h src/Image.h
	g++ -ggdb -Wall -c src/mainTest1.cpp -o obj/mainTest1.o

obj/mainsdl.o: src/mainsdl.cpp src/AffichageSDL.h src/Image.h src/De.h src/Joueur.h src/Jeu.h
	g++ -ggdb -Wall -c src/mainsdl.cpp -o obj/mainsdl.o

obj/AffichageSDL.o:	src/AffichageSDL.cpp src/AffichageSDL.h src/Jeu.h src/Image.h src/De.h
	g++ -ggdb -Wall $(shell sdl2-config --cflags) -c src/AffichageSDL.cpp -o obj/AffichageSDL.o

obj/Jeu.o: src/Jeu.cpp src/Jeu.h src/Joueur.h src/De.h
	g++ -ggdb -Wall -c src/Jeu.cpp -o obj/Jeu.o

obj/Joueur.o: src/Joueur.cpp src/Joueur.h src/Pion.h src/Color.h
	g++ -ggdb -Wall -c src/Joueur.cpp -o obj/Joueur.o

obj/De.o: src/De.cpp src/De.h
	g++ -ggdb -Wall -c src/De.cpp -o obj/De.o

obj/Pion.o: src/Pion.cpp src/Pion.h
	g++ -ggdb -Wall -c src/Pion.cpp -o obj/Pion.o

obj/Color.o: src/Color.cpp src/Color.h
	g++ -ggdb -Wall -c src/Color.cpp -o obj/Color.o

obj/Image.o: src/Image.cpp src/Image.h
	g++ -ggdb -Wall $(shell sdl2-config --cflags) -c src/Image.cpp -o obj/Image.o

doc:
	doxygen dox/doxyfile

clean:
	rm -f obj/*.o bin/mainTest1 bin/mainsdl

