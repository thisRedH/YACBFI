CC = gcc
CFLAGS = -std=c99 -O3

SRCS = main.c utils.c
OBJS = $(SRCS:.c=.o)

ifeq ($(OS),Windows_NT)
	TARGET = yacbfi.exe
else
	TARGET = yacbfi
endif

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)