CC = g++

all: main.o parser.o sort.o caller.o generator.o io.o
	$(CC) -o main main.o parser.o sort.o caller.o generator.o io.o
main.o: main.cpp parser.h
	$(CC) -g -c main.cpp
parser.o: parser.cpp parser.h caller.h generator.h io.h constant.h
	$(CC) -g -c parser.cpp
sort.o: sort.cpp sort.h
	$(CC) -g -c sort.cpp
caller.o: caller.cpp caller.h 
	$(CC) -g -c caller.cpp
generator.o: generator.cpp generator.h
	$(CC) -g -c generator.cpp
io.o: io.cpp io.h
	$(CC) -g -c io.cpp
clean: 
	rm -f *.o
	rm main