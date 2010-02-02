CC = clang
CFLAGS = -Wall -g -arch x86_64

LD = clang
LDFLAGS = -arch x86_64

CT = clang
CTFLAGS = -S -arch x86_64

RM = rm

OBJS = main.o
PROG = strangelet

all: $(PROG)

clean:
	$(RM) -f $(PROG) $(OBJS)

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.s: %.c
	$(CT) $(CTFLAGS) $<
