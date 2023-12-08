SRC-DIR := src/
SRC := $(wildcard ${SRC-DIR}*.cpp)
OUT:= gl-test
LIBS := -lglfw -lGLEW -lGL

all: ${OUT}

${OUT}: ${SRC}
	g++ ${SRC} -o ${OUT} ${LIBS}
