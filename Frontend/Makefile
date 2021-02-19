$(info $(SHELL))
SRC=src/
DIRECTORY=${SRC}de/numericat/
FILE_BASE=${DIRECTORY}Main
DEPENDENCIES=${DIRECTORY}Coordinate.java ${DIRECTORY}Numericanvas.java ${DIRECTORY}Io.java

all:${FILE_BASE}.class

# TODO: Unresolved prerequisites
%.class:%.java ${DEPENDENCIES}
	javac $< ${DEPENDENCIES}

README:
	echo "Run using java de.numericat.Main in src folder" > README

.PHONY:clean
clean:
	${RM} ${DIRECTORY}*.class
