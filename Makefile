CC = gcc

CFLAGS = -g -Wall -Wextra -Werror `pkg-config gtk+-3.0 --cflags`

LDFLAGS = -ljemalloc `pkg-config gtk+-3.0 --libs`

SRCS = main.c pptree.c

OBJS = $(SRCS:.c=.o)

MAIN = pikslpro

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(MAIN)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(MAIN)
