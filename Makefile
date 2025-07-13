SRC = main.cpp engine.cpp math.cpp
OBJ = $(SRC:.cpp=.o)
DEPS = engine.h math.h

CC = g++

COMPILER_FLAGs = -std=c++17 -Wall

LINKER_FLAGS = -lSDL2

TARGET = engine

all : $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LINKER_FLAGS) -o $@

%.o: %.cpp $(DEPS)
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o $(TARGET)
