# Makefile para Grafo de Coautorias FACOM/UFU
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2
TARGET = grafo_facom
OBJS = main.o grafo.o

.PHONY: all clean run debug

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c Grafo.h
	$(CC) $(CFLAGS) -c main.c

grafo.o: grafo.c Grafo.h
	$(CC) $(CFLAGS) -c grafo.c

run: $(TARGET)
	./$(TARGET)

debug: CFLAGS += -g -O0
debug: clean all

clean:
	rm -f $(OBJS) $(TARGET)
