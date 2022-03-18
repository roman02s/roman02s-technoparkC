CFLAGS = -I. \
		 -Ifood \
		 -Iadd \
		 -Iinput
TARGET = ./main
INCLUDE_DIRS = food \
			   add \
			   input
SOURCE_FILES = main.c \
			   food/*.c \
			   add/*.c \
			   input/*.c

install_packages:
	 apt-get update -y && \
	 apt-get install build-essential && \
	 apt-get install -y cppcheck clang-tidy python3-pip libc6-dbg lcov libgtest-dev && \
	 pip3 install cpplint && \
	 apt-get install cmake -y && \
	 apt-get install valgrind -y

.PHONY: all build rebuild run clean

build: ${TARGET}

rebuild: clean build

${TARGET}: ${INCLUDE_DIRS} ${SOURCE_FILES}
	gcc  ${SOURCE_FILES} -o ${TARGET} ${CFLAGS}

run: ${TARGET}
	${TARGET}

#check: ${TARGET}
#	./linters/run.sh

test: ${TARGET}
	valgrind --tool=memcheck --leak-check=yes ./main < tests/test_1/test_1.in > tests/test_1/test_1.out

clean:
	rm ${TARGET}
