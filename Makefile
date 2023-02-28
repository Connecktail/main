FLAGS= -Wall
CC= gcc
LIBS= -lpq -ldb-utils -lpthread -lcjson
OBJECTS=objects
BUILD=build
SRC=src
INCLUDE=include
OBJECTS_FILES= $(OBJECTS)/main.o $(OBJECTS)/pair.o $(OBJECTS)/server.o

all: $(BUILD)/main

$(BUILD)/main: $(OBJECTS_FILES)
	$(CC) $(FLAGS) -o $(BUILD)/main $^  $(LIBS)

$(OBJECTS)/%.o: $(SRC)/%.c $(INCLUDE)/*.h
	$(CC) $(FLAGS) -c $< -o $@ $(LIBS)

test: test.c
	$(CC) $(FLAGS) -o $@ $< -lcjson

clean:
	rm -f $(OBJECTS)/*
	rm -f $(BUILD)/*