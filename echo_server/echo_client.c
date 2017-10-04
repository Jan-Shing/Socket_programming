#include "csapp.h"
int main(int argc, char **argv){
	int clientfd;
	char *host, *port, buf[MAXLINE];
	rio_t rio;

	if(argc != 3){
		fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
		exit(0);
	}

	host = argv[1];
	port = argv[2];

	
	
	if ((clientfd = open_clientfd(host, port)) < 0)
		printf("Connect to host %s failed~\n",argv[1]);
	/*
	struct addrinfo hints, *result, *rp;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV;
	getaddrinfo(host, port, &hints, &result);
	for(rp = result; rp;rp = rp->ai_next){
		clientfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (clientfd == -1) continue;
		if(connect(clientfd, rp->ai_addr, rp->ai_addrlen) != -1) break;
		close(clientfd);
	}
	if (rp == NULL) printf("Connect to host %s failed\n",host);
	*/
	rio_readinitb(&rio, clientfd);

	while(fgets(buf, MAXLINE, stdin) != NULL){
		rio_writen(clientfd, buf, strlen(buf));
		rio_readlineb(&rio, buf, MAXLINE);
		fputs(buf, stdout);
	}
	close(clientfd);
	exit(0);
}
