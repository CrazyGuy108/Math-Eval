CFILES = $(SRC)/token.c $(SRC)/lexer.c $(SRC)/expr.c $(SRC)/parser.c $(SRC)/main.c
EXE = $(BIN)/math-eval.exe
SRC = src
BIN = bin

all: $(CFILES)
	gcc -Wall -std=c11 $(CFILES) -o $(EXE)