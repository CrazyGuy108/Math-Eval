CFILES = $(SRC)/*.c
EXE = $(BIN)/math-eval.exe
SRC = src
BIN = bin

all: $(CFILES)
	gcc -Wall -std=c11 $(CFILES) -o $(EXE)