CC = g++ -std=c++14
FLAGS = -march=native -Wall -g -rdynamic
LIBS	= -I/usr/local/include -L/usr/local/lib -lhidapi-hidraw -pthread

A_SRC = main.cpp
A_TARGET  = joycon-server

# Make Rules
.PHONY: all
all: joycon-server

.PHONY: joycon-server
joycon-server: $(A_SRC)
	$(CC) $(A_SRC) $(FLAGS) $(LIBS) -o $(A_TARGET)
		@echo "> Compiled joycon-server"
