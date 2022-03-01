#include <stdio.h>

#include <pqueue.h>

void print_pq(pqueue_t *pq);

int main(void) {
	pqueue_t *pq = create_pq(NULL);

	int a = 1, b = 2;

	pq_push(pq, &a, sizeof(int), 11, NULL);

	printf("size = %i\n", pq_elem_count(pq, NULL));

	pq_push(pq, &b, sizeof(int), 10, NULL);

	printf("size = %i\n", pq_elem_count(pq, NULL));

	print_pq(pq);
	putc('\n', stdout);
	int *c = pq_pop(pq, NULL);
	
	printf("size = %i\n", pq_elem_count(pq, NULL));

	print_pq(pq);

	free_pq(pq, NULL);
}

void print_pq(pqueue_t *pq) {
	if(pq == NULL) return;
	if(pq->head == NULL) {
		printf("pqueue is empty\n");
		return;
	}
	node_t *iter = pq->head;
	while(iter) {
		int *ptr = iter->data;
		printf("[%p]->[%d]\n", ptr, *ptr);
		iter = iter->next;
	}
}