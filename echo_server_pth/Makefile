
all: echo_server_p
CFLAGS = -std=c99 \
		 -I. \
		 -Wall\
		 -D_DEFAULT_SOURCE\
		 -pthread

echo_server_p: echo_server.c echo-cnt.o sbuf.o IO_function.o helper_socket.o csapp.h
	gcc $(CFLAGS) -o $@ $^  
%.o: %.c 
	gcc $(CFLAGS) -c  $<

