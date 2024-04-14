#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <pqueue.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <pthread.h>
#include <fcntl.h>


const char *sem_name = "my_sem";

char *filename = "queue.dat";

//sem_t sem_id;

int itemId = 0;

typedef struct item item;
struct item {
	int id;
};


item * produce() {
	int time = rand() % 5 + 1;
	item *it = (item *)malloc(sizeof(item));
	sleep(time);
	it->id = itemId;
	itemId += 1;
	return it;
}

void consume(item *it) {
	int time = rand() % 5 + 1;
	sleep(time);
	free(it);
}


void producer(pid_t childPid) {
	sem_t *sem_id = sem_open(sem_name, O_CREAT, 0600, 1);
	pqueue *qu = NULL;
    while (1) {
        item *it = produce();
        printf("\nprodukuje %d\n", it->id);
        sem_wait(sem_id);
        qunserialize(&qu, sizeof(item), filename);
        qinsert(&qu, it, 1);
        qserialize(qu, sizeof(item), filename);
        sem_post(sem_id);
		sleep(1);
	}
}

void consumer() {
	sem_t *sem_id = sem_open(sem_name, O_CREAT, 0600, 1);

    pqueue *qu = NULL;
	while (1) {
        item *it = NULL;
        sem_wait(sem_id);
        qunserialize(&qu, sizeof(item), filename);
		pqueue *el = NULL;
		if (qu != NULL) {
			el = qpop(&qu);
        	qserialize(qu, sizeof(item), filename);
        	it = el->data;
        	printf("\nkonsumuje %d\n", it->id);
		}

        sem_post(sem_id);
		if (it != NULL) {
        	consume(it);
		}
    }
}

int main(int argc, char **argv) {
	pid_t pid;
	pqueue *qu = NULL;
	/* watch -n 1 ps -l --forest */
	
	/* create empty queue */
    qserialize(qu, sizeof(item), filename);


	//sem_init(&sem_id, 1, 1);
	pid = fork();

	if (pid < 0) {
		printf("BLAD FORK\n");
		return 1;
	} else if (pid == 0) {
		//child
		printf("Child FORK\n");
		consumer();

	} else {
		//parent
		printf("Parent FORK\n");
		producer(pid);

	}

	

	return 0;
}

