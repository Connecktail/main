FLAGS= -Wall
CC= gcc
LIBS= -lpq -ldb-utils -lpthread -lcjson -lmsq-utils -lcurl -lshm-utils
OBJECTS=objects
BUILD=build
SRC=src
INCLUDE=include
OBJECTS_FILES= main.o pair.o server.o add_bottle.o configure_curl.o search_bottle.o send_data_to_module.o signal_handler.o protocol.o bottle_taken.o set_battery.o
OBJS=$(addprefix $(OBJECTS)/, $(OBJECTS_FILES))


all: $(BUILD)/main

$(BUILD)/main: $(OBJS)
	$(CC) $(FLAGS) -o $(BUILD)/main $^  $(LIBS)

$(OBJECTS)/%.o: $(SRC)/%.c $(INCLUDE)/*.h
	$(CC) $(FLAGS) -c $< -o $@ $(LIBS)

test: test.c
	$(CC) $(FLAGS) -o $@ $< -lcjson

clean:
	rm -f $(OBJECTS)/*
	rm -f $(BUILD)/*