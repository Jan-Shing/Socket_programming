#include "csapp.h"
int open_clientfd(char *hostname, char *port){
	int clientfd;
	struct addrinfo hints, *listp, *p;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM; /*	Open with connection	*/
	hints.ai_flags = AI_NUMERICSERV; /*	Using a numeric port arg	*/
//	hints.ai_family = AF_UNSPEC;     /* Allows IPV4 or IPC6*/
	hints.ai_flags |= AI_ADDRCONFIG; /*	Recommended for connections	*/

	if ( getaddrinfo(hostname, port, &hints, &listp) != 0) printf("Error in getaddrinfo\n");

	for (p = listp; p; p = p->ai_next){
		if((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
			continue; /*Socket failed, try the next*/
		if(connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) break;
		close(clientfd); /* Connect failed, try another*/
	}
	
	
	
	if (p == NULL) printf("Connect to host %s failed\n",hostname);
	
	/* Clean up*/
	freeaddrinfo(listp);
	if (!p) return -1; /* All connection failed*/
	else return clientfd; /* The last connect succedded*/
}
int open_listenfd(char *port){
	int listenfd, optval = 1;
	struct addrinfo hints, *listp, *p;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM; /*	Open with connection	*/
	hints.ai_flags = AI_NUMERICSERV; /*	Using a numeric port arg	*/
	hints.ai_flags |= AI_ADDRCONFIG; /*	Recommended for connections	*/
	hints.ai_flags |= AI_PASSIVE; /* on any IP address , wildcard IP*/

	getaddrinfo(NULL, port, &hints, &listp);
	for (p = listp; p; p = p->ai_next){
		if((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol) < 0))
		 continue;
		 /*	Eliminates "Address already in use" error from bind*/
		 setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

		if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) break;
		close(listenfd);
	}
		/* Clean up*/
		freeaddrinfo(listp);
		if(!p) return -1;
		if(listen(listenfd, LISTENQ) < 0) {
			close(listenfd);
			return -1;
		}
		return listenfd;
	
}
