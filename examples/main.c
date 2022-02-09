#include <stdio.h>

#include <pqueue.h>

void print_pq(pqueue_t *pq);

int main(void) {
	int vals[] = {4, 5, 1, 0, 2, 3, 7, 6};
	int prio[] = {4, 5, 1, 0, 2, 3, 7, 6};

	pqueue_t *pq = create_pq(NULL);

	printf("priority queue is %sempty\n", is_pq_empty(pq, NULL)?"":"not ");

	for(int i = 0; i < 8; ++i) {
		pq_push(pq, vals + i, sizeof(int), prio[i], NULL);
	}

	print_pq(pq);

	generic_t data = pq_peek(pq, NULL);
	printf("peeked: [%p]->[%d]\n", data.data, *(int*)data.data);

	print_pq(pq);

	data = pq_pop(pq, NULL);
	printf("poped: [%p]->[%d]\n", data.data, *(int*)data.data);
	free(data.data);
	++free_cnt;

	print_pq(pq);

	data = pq_peek(pq, NULL);
	printf("peeked: [%p]->[%d]\n", data.data, *(int*)data.data);

	print_pq(pq);

	printf("priority queue is %sempty\n", is_pq_empty(pq, NULL)?"":"not ");

	for(int i = 0; i < 7; ++i) {
		data = pq_pop(pq, NULL);
		printf("poped: [%p]->[%d]\n", data.data, *(int*)data.data);
		free(data.data);
		++free_cnt;
	}

	printf("priority queue is %sempty\n", is_pq_empty(pq, NULL)?"":"not ");

	print_pq(pq);

	free_pq(pq, NULL);
	fprintf(stderr, "malloc count: %lld\nfree count: %lld\n", malloc_cnt, free_cnt);
}

void print_pq(pqueue_t *pq) {
	if(pq == NULL) return;
	if(pq->head == NULL) {
		printf("pqueue is empty\n");
		return;
	}
	node_t *iter = pq->head;
	while(iter) {
		int *ptr = iter->data.data;
		printf("[%p]->[%d]\n", ptr, *ptr);
		iter = iter->next;
	}
}