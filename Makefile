CC = gcc

SOURCES += cntlib/*.c
SOURCES += examples/time/*.c

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror

INCLUDES += -I"."
OUTPUT := a.out

all:
	$(CC) $(INCLUDES) $(SOURCES) $(CFLAGS) -o $(OUTPUT)

example:
	$(CC) $(INCLUDES) $(SOURCES) $(CFLAGS) -o $(OUTPUT)

run:
	./$(OUTPUT)

clean:
	rm -rf $(OUTPUT)