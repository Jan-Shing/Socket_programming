#include<csapp.h>

#define NTHREADS 4
#define SBUFSIZE 16

void echo_cnt(int );
void *thread(void *);

sbuf_t sbuf; /* shared buffer of connected descriptors*/

int main(int argc, char **argv){
	int i, listenfd, connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	pthread_t tid;

	if(argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}
	listenfd = open_listenfd(argv[1]);
	sbuf_init(&sbuf, SBUFSIZE);
	for(i = 0; i < NTHREADS; i++)
		pthread_create(&tid, NULL, thread, NULL);
	printf("Create %d threads for working\n", NTHREADS);
	while(1){
		clientlen = sizeof(struct sockaddr_storage);
		connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
		sbuf_insert(&sbuf, connfd);
		printf("insert connection with fd is %d\n",connfd);
	}
}

void *thread (void *vargp){
	pthread_detach(pthread_self());
	printf("thread detach ok\n");
	while(1){
		int connfd = sbuf_remove(&sbuf);
		printf("connection of %d is removed\n",connfd);
		echo_cnt(connfd);
		close(connfd);
	}
}

