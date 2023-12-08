SRC := src/main.cpp src/shader.cpp src/renderer.cpp
OUT:= gl-game.out
LIBS := -lglfw -lGLEW -lGL

all: ${OUT}

${OUT}: ${SRC}
	g++ ${LIBS} ${SRC} -o ${OUT}

debug: ${SRC}
	g++ ${LIBS} ${SRC} -o ${OUT} -g

clean: 
	rm ${OUT}
