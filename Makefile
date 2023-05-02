CC = gcc
CFLAGS = -std=c99 -O3

SRCS = main.c utils.c
OBJS = $(SRCS:.c=.o)

ifeq ($(OS),Windows_NT)
	TARGET = yacbfi.exe
	REM = del /Q /F
else
	TARGET = yacbfi
	REM = rm -rf
endif

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(REM) *.o $(TARGET)