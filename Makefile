CC = gcc
CFLAGS = -Og -Wall -I .
LDLIBS = -lpthread

# Main targets
PROGS = echoclient echoservers

all: $(PROGS)

# Build csapp library object
csapp.o: csapp.c csapp.h
	$(CC) $(CFLAGS) -c csapp.c

# Build echo helper object
echo.o: echo.c csapp.h
	$(CC) $(CFLAGS) -c echo.c

# Build echoclient (requires echoclient.o, echo.o, and csapp.o)
echoclient: echoclient.o echo.o csapp.o
	$(CC) $(CFLAGS) -o echoclient echoclient.o echo.o csapp.o $(LDLIBS)

echoclient.o: echoclient.c csapp.h
	$(CC) $(CFLAGS) -c echoclient.c

# Build echoservers (requires echoservers.o, echo.o, and csapp.o)
echoservers: echoservers.o echo.o csapp.o
	$(CC) $(CFLAGS) -o echoservers echoservers.o echo.o csapp.o $(LDLIBS)

echoservers.o: echoservers.c csapp.h
	$(CC) $(CFLAGS) -c echoservers.c

# Optional: build select example
select: select.o echo.o csapp.o
	$(CC) $(CFLAGS) -o select select.o echo.o csapp.o $(LDLIBS)

select.o: select.c csapp.h
	$(CC) $(CFLAGS) -c select.c

# Clean build artifacts
clean:
	rm -f $(PROGS) select *.o *~

.PHONY: all clean
