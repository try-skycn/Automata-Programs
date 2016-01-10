CC = c++
CFLAG = -O2

.PNOHY: all
all: turing
	./turing -t100000 < input.txt

turing: turing.cpp
	$(CC) -o $@ $< $(CFLAG)
