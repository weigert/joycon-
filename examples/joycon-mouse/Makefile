CC = g++ -std=c++14
FLAGS = -march=native -Wall -g -rdynamic
LIBS	= -I/usr/local/include -L/usr/local/lib -lhidapi-hidraw -pthread -lX11 -lXtst

A_SRC = main.cpp
A_TARGET  = joycon-mouse

# Make Rules
.PHONY: all
all: joycon-mouse

.PHONY: joycon-mouse
joycon-mouse: $(A_SRC)
	$(CC) $(A_SRC) $(FLAGS) $(LIBS) -o $(A_TARGET)
		@echo "> Compiled joycon-client"
