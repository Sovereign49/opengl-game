SRC-DIR := src/
SRC := $(wildcard ${SRC-DIR}*.cpp)
OUT:= gl-game.out
LIBS := -lglfw -lGLEW -lGL

all: ${OUT}

${OUT}: ${SRC}
	g++ ${SRC} -o ${OUT} ${LIBS}

build-debug: ${SRC}
	g++ ${SRC} -o ${OUT} ${LIBS} -g

clean: 
	rm ${OUT}
