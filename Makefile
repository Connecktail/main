FLAGS= -Wall
CC= gcc
LIBS= -lpq -ldb-utils -lpthread -lcjson
OBJECTS=objects
BUILD=build
SRC=src
INCLUDE=include

all: $(BUILD)/main

$(BUILD)/main: $(OBJECTS)/main.o
	$(CC) $(FLAGS) -o $(BUILD)/main $(OBJECTS)/main.o  $(LIBS)

$(OBJECTS)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	$(CC) $(FLAGS) -c $< -o $@ $(LIBS)

test: test.c
	$(CC) $(FLAGS) -o $@ $< -lcjson

clean:
	rm -f $(OBJECTS)/*
	rm -f $(BUILD)/*