TARGET = tests
CC = g++ -fprofile-arcs -ftest-coverage 
SRC = $(wildcard *.cpp)

$(TARGET) :
	$(CC) $(SRC) -o $(TARGET) -lCatch2Main -lCatch2 -lgcov

clean :
	rm $(TARGET)*