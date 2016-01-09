CC = c++
CFLAG = -O2 -std=c++11

.PHONY: all
all: transform graph

.PHONY: graph
.PHONY: table

graph: transform input.txt
	./$< $@ < input.txt > graph.dot
	dot -Teps < graph.dot > graph.eps
	rm graph.dot

table: transform input.txt
	./$< $@ < input.txt > table.tex

transform: transform.cpp
	$(CC) -o $@ $< $(CFLAG)

.PHONY:clean
clean:
	if [ -e table.tex ]; then rm table.tex; fi;
	if [ -e graph.eps ]; then rm graph.eps; fi;
