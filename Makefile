CXX=g++
CFLAGS=-Wall -pedantic
LDFLAGS=-lglut -lGL -lGLU

SRC_DIR=.
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES=$(SRC_FILES:.cpp=.o)


%.o: %.cpp %.h
		$(CXX) -I$(INCDIR) $(CFLAGS) $(LDFLAGS) -c $< -o $@

%.h:
	

all:	$(OBJ_FILES)
	$(CXX) $(LDFLAGS) $(OBJ_FILES) -o opengl-stickyman

clean:
	rm -f *.o opengl-stickyman


