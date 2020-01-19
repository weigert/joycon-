CC = g++ -std=c++14
FLAGS = -march=native -Wall -g -rdynamic
LIBS	= -I/usr/local/include -L/usr/local/lib -lhidapi-hidraw -pthread

A_SRC = main.cpp
A_TARGET  = joycon

# Make Rules
.PHONY: all
all: joycon

.PHONY: joycon
joycon: $(A_SRC)
	$(CC) $(A_SRC) $(FLAGS) $(LIBS) -o $(A_TARGET)
		@echo "> Compiled joycon-client"
