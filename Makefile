CC = clang
CFLAGS = -g -Wall -Wextra -pthread
SRCS = main.c funciones.c 
HEADERS = funciones.h 

PRODUCTS = productos.txt ventas.txt usuario.txt	

OBJS = $(SRCS:.c=.o)
ASMS = $(SRCS:.c=.s)

main: $(OBJS) $(HEADERS) $(PRODUCTS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.s: %.c $(HEADERS)
	$(CC) $(CFLAGS) -S $< -o $@

clean:
	rm -f main $(OBJS) $(ASMS)

