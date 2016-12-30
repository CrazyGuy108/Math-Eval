ALL_SRCS = $(wildcard $(SRC)/*.c)
SRCS     = $(filter-out $(SRC)/main.c, $(ALL_SRCS))
SRC      = src
TESTS    = tests
BIN      = bin

all: $(ALL_SRCS)
	gcc -Wall -std=c11 $(ALL_SRCS) -o $(BIN)/math-eval.exe
lexer-test: $(SRCS) $(TESTS)/lexer-test.c
	gcc -Wall -std=c11 -g $(SRCS) $(TESTS)/lexer-test.c -o $(BIN)/lexer-test.exe
expr-test: $(SRCS) $(TESTS)/expr-test.c
	gcc -Wall -std=c11 -g $(SRCS) $(TESTS)/expr-test.c -o $(BIN)/expr-test.exe
