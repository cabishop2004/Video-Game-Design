PROJ=simple
EXE=${PROJ}.exe
SRC=${PROJ}.cpp
SRCS=Background BouncingFace Game
CPPFiles=$(foreach item,$(SRCS),$(item).cpp)
OBJS=$(foreach item,$(SRCS),$(item).o)
HEADERS=$(foreach item,$(SRCS),$(item).h)
CFLAGS=-g 
SDLCFLAGS=-I/usr/include/SDL2 -D_REENTRANT
SDLLIBS=-lSDL2

%.o: %.cpp
	g++ -c ${SDLCFLAGS} ${CFLAGS} $< -o $@ 

run: ${EXE}
	./${EXE}

${EXE}: ${SRC} ${OBJS}
	g++ ${SDLCFLAGS} ${CFLAGS} ${SRC} -o $@ ${OBJS} ${SDLLIBS}

clean:
	rm -f ${EXE} ${OBJS}
	#del /Q ${EXE} ${OBJS}
