# Project Name
PROJ = simple
EXE = $(PROJ).exe

# Source and Header Files
SRC = $(PROJ).cpp
SRCS = Background.cpp BouncingFace.cpp Game.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = Background.h BouncingFace.h Game.h

# Compiler and Flags
CXX = g++
CXXFLAGS = -g -lmingw32 -Wall 
SDLCFLAGS = -IC:/sdl2/include/SDL2 -D_REENTRANT
SDLLIBS = -LC:/sdl2/lib -lSDL2main -lSDL2


# Build Rules
all: $(EXE)

$(EXE): $(SRC) $(OBJS)
	$(CXX) $(CXXFLAGS) $(SDLCFLAGS) $(SRC) -o $@ $(OBJS) -LC:/sdl2/lib -lSDL2main -lSDL2


%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(SDLCFLAGS) -c $< -o $@

# Run the program
run: $(EXE)
	./$(EXE)

# Clean up build files
clean:
	del /f $(EXE) $(OBJS)
