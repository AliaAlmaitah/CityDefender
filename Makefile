CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -lm #-lXrandr

all: rainforest

rainforest: rainforest.cpp log.cpp jcanales.h jcanales.cpp bestrada.h bestrada.cpp aalmaitah.cpp
	g++ $(CFLAGS) rainforest.cpp log.cpp jcanales.cpp bestrada.cpp aalmaitah.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o rainforest

clean:
	rm -f rainforest
	rm -f *.o

