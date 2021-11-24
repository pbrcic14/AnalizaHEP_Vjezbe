CC=g++ -std=c++11
CFLAGS=-I.
DEPS = Analyzer.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

analyzer: analyze.o Analyzer.o
	$(CC) -o analyze analyze.o Analyzer.o

clean:
	rm -rf *.o analyze
