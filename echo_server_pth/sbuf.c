#include "csapp.h"

void P (sem_t *s){
	sem_wait(s);
}
void V(sem_t * s){
	sem_post(s);
}

void sbuf_init(sbuf_t *sp, int n){
	sp->buf = calloc(n, sizeof(int));
	sp->n = n;                          /* Buffer holds max of n items*/
	sp->front = sp->rear = 0;			/*Empty buffer front==rear*/
	/*the second parameter of sem_init indicate the sem shared by threads*/
	sem_init(&sp->mutex, 0, 1);			/*Binary semaphore for locking*/
	sem_init(&sp->slots, 0, n);			/*Initially, buf has n empty slots*/
	sem_init(&sp->items, 0, 0); 		/*Initially, buf has zero data items*/
	printf("sbuf Initializing finishing\n");
}

/* Clean up buffer sp*/
void sbuf_deinit(sbuf_t *sp){
	free(sp->buf);
}

/*Insert item onto the rear of shared buffer sp*/
void sbuf_insert(sbuf_t *sp, int item){
	P(&sp->slots);                        /*Wait for available slot*/
	P(&sp->mutex);						   /*Lock the buffer*/
	printf("can do intsert\n");
	sp->buf[(++sp->rear)%(sp->n)] = item; /* Insert the item*/
	printf("can do intsert 2\n");
	V(&sp->mutex);						  /*Unlock the buffer*/
	V(&sp->items);						  /* Announce available item*/
	printf("finish intsert 2\n");
}

int sbuf_remove(sbuf_t *sp){
	int item;
	P(&sp->items);                         /*Wait for available item*/
	P(&sp->mutex);                        /* Lock the buffer*/
	item = sp->buf[(++sp->front)%(sp->n)];/*Remove the item*/
	V(&sp->mutex);                        /*Unlock the buffer*/
	V(&sp->slots);                        /*Announce available slot*/
	return item;
}
