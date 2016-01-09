CC = c++
CFLAG = -O2 -std=c++11

.PHONY: all
all: transform

.PHONY: expression
expression: transform input.txt
	./$< < input.txt > output.txt

transform: transform.cpp
	$(CC) -o $@ $< $(CFLAG)

.PHONY: clean
clean:
