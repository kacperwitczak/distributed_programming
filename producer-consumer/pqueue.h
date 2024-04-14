typedef struct pqueue pqueue;
struct pqueue {
	int k;
	void *data;
	pqueue *next;
	pqueue *prev;
};

void qinsert(pqueue **phead, void *data, int k);

void qlist(pqueue *head, void (*print_data)(void *));

void qremove(pqueue **phead, int k);

pqueue *qpop(pqueue **phead);

void qserialize(pqueue *head, size_t ndata, char *filename);

void qunserialize(pqueue **phead, size_t ndata, char *filename);
