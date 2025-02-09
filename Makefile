EXEC 		= bin/quarto

GGDB 		= -Wall -ggdb

paramC 		= -std=c++11 -Wall -c

ifeq ($(OS),Windows_NT)

libDir		= -L./libs/windows/lib
libFlags 	= -lsfml-graphics -lsfml-window -lsfml-system

else

libDir 		= -I./SFML/
libFlags	= -lsfml-graphics -lsfml-window -lsfml-system

endif

OBJ			= 	obj/Pion.o \
				obj/Case.o \
				obj/Grille.o \
				obj/IA.o \
				obj/Jeu.o \

HEADER		= 	src/Pion.h \
				src/Case.h \
				src/Grille.h \
				src/IA.h \
				src/Motif.h

all: $(EXEC)

bin/quarto: main.cpp $(OBJ)
	g++ -std=c++11 $(GGBD) main.cpp $(OBJ) -o bin/quarto $(libDir) $(libFlags)

obj/%.o: src/%.cpp $(HEADER)
	g++ $(paramC) $< -o $@

ifeq ($(OS),Windows_NT)
clean:
	del /f obj\*.o

veryclean: clean
	del /f bin\*.exe
else
clean:
	rm obj/*.o

veryclean:
	rm bin/quarto
	make clean
endif
