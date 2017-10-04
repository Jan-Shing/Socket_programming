
all: echo_server echo_client
CFLAGS = -std=c99 \
		 -I. \
		 -Wall\
		 -D_DEFAULT_SOURCE

echo_server:  echo_server.c IO_function.o helper_socket.o csapp.h
	gcc $(CFLAGS) -o $@ $<  IO_function.o helper_socket.o
echo_client:  echo_client.c IO_function.o helper_socket.o csapp.h
	gcc $(CFLAGS) -o $@ $<  IO_function.o helper_socket.o
%.o: %.c 
	gcc $(CFLAGS) -c  $<
clear:
	rm -rf *.o
