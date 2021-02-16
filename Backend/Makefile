$(info $(SHELL))
CC?=gcc
CFLAGS=-g -Wall -Werror -Wunused-parameter -Wunused-variable -Ofast -fsanitize=address -fsanitize-recover=address
CLIBS=-lcheck -pthread -lm
MACCLIBS=-lcheck -pthread -pthread -lm
UBUNTUFLAGS=-lsubunit
FILE_BASE=Program
DEPENDENCIES=Parser/Parser.c Parser/Function.c Solver/Types/Matrix.c Solver/Types/Complex.c Solver/CrankNicolson/Iterate.c
TEST_DEPENDENCIES=Tests/TestHelper.c
TEST_FILE_BASE=Tests/Checks
OS?=$(shell [ -e "/etc/os-release" ] && grep ^NAME=".*" /etc/os-release)
ifeq ($(OS),)
	OS=$(shell uname -s)
endif

all:${FILE_BASE}.x ${TEST_FILE_BASE}.x
program:${FILE_BASE}.x
test:${TEST_FILE_BASE}.x

${TEST_FILE_BASE}.x:${TEST_FILE_BASE}.c ${TEST_DEPENDENCIES} ${DEPENDENCIES}
ifneq (,$(findstring Ubuntu,${OS}))
# Ubuntu
	${CC} ${CFLAGS} -o $@ $< ${CLIBS} ${UBUNTUFLAGS} ${TEST_DEPENDENCIES} ${DEPENDENCIES}
else
ifeq ($(OS),Darwin)
# MacOS
	${CC} ${CFLAGS} -o $@ $< ${MACCLIBS} ${TEST_DEPENDENCIES} ${DEPENDENCIES}
else
# Everything else
	${CC} ${CFLAGS} -o $@ $< ${CLIBS} ${TEST_DEPENDENCIES} ${DEPENDENCIES}
endif
endif

%.x:%.c ${DEPENDENCIES}
ifneq (,$(findstring Ubuntu,${OS}))
# Ubuntu
	${CC} ${CFLAGS} -o $@ $< ${CLIBS} ${UBUNTUFLAGS} ${DEPENDENCIES}
else
ifeq ($(OS),Darwin)
# MacOS
	${CC} ${CFLAGS} -o $@ $< ${MACCLIBS} ${DEPENDENCIES}
else
# Everything else
	${CC} ${CFLAGS} -o $@ $< ${CLIBS} ${DEPENDENCIES}
endif
endif

.PHONY:clean
clean:
	${RM} ${FILE_BASE}.[ox]
	${RM} ${TEST_FILE_BASE}.[ox]
