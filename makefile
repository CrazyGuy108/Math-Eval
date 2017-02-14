ALL_SRCS = $(wildcard $(SRC)/*.c)
SRCS     = $(filter-out $(SRC)/main.c, $(ALL_SRCS))
SRC      = src
TESTS    = tests
BIN      = bin

all: $(ALL_SRCS)
	gcc -Wall -std=c11 -pedantic $(ALL_SRCS) -o $(BIN)/math-eval.exe
lexer-test: $(SRCS) $(TESTS)/lexer-test.c
	gcc -Wall -std=c11 -pedantic -g $(SRCS) $(TESTS)/lexer-test.c -o $(BIN)/lexer-test.exe
parser-test: $(SRCS) $(TESTS)/parser-test.c
	gcc -Wall -std=c11 -pedantic -g $(SRCS) $(TESTS)/parser-test.c -o $(BIN)/parser-test.exe
