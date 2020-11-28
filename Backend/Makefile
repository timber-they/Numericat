CC=clang
CFLAGS=-g -Wall -Werror -Wunused-parameter -Wunused-variable -O3 -pedantic
FILE_BASE=Program
DEPENDENCIES=Parser/Parser.c Parser/Function.c

all:${FILE_BASE}.x

# TODO: Unresolved prerequisites
%.x:%.c ${DEPENDENCIES}
	${CC} ${CFLAGS} -o $@ $< ${DEPENDENCIES}

.PHONY:clean
clean:
	${RM} ${FILE_BASE}.[ox]
