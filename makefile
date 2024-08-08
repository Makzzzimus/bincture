CC = gcc
FLAGS = -g -Wall
OBJECTS = ./bin/main.o ./bin/cli.o ./bin/bmp.o ./bin/os.o ./bin/decfwrite.o ./bin/conio.o 

ifdef OS
	OUTPUT = bin\bincture.exe
	CLEAN = del /q .\bin\*.o ${OUTPUT}
else
	OUTPUT = ./bin/bincture
	CLEAN = rm -f ./bin/*.o ${OUTPUT}
endif

all: bin | ${OUTPUT}

${OUTPUT}: ${OBJECTS}
	${CC} ${FLAGS} $^ -o $@

bin/%.o: %.c
	${CC} ${FLAGS} -c $^ -o $@

bin:
	mkdir bin

clean: 
	${CLEAN}