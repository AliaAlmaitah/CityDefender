CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -lm #-lXrandr

all: CityDefender

CityDefender: CityDefender.cpp log.cpp jcanales.h jcanales.cpp bestrada.h bestrada.cpp aalmaitah.cpp
	g++ $(CFLAGS) CityDefender.cpp log.cpp jcanales.cpp bestrada.cpp aalmaitah.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o CityDefender

clean:
	rm -f CityDefender
	rm -f *.o

