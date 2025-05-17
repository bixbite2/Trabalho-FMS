CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lpthread

SRCS = main.c error_functions.c usage_interface.c usage_monitor.c
OBJS = $(SRCS:.c=.o)
TARGET = my_app.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)

