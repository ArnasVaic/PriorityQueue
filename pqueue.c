#include <pqueue.h>

size_t malloc_cnt = 0;
size_t free_cnt = 0;

node_t* create_node(void *data, size_t size, int64_t prio, int *errnum) {
	node_t *node = (node_t*) malloc(sizeof(node_t));
	++malloc_cnt;

	if(node == NULL) {
		if(errnum != NULL) *errnum = 1;
		return NULL;
	}
	
	node->data = malloc(size);
	++malloc_cnt;
	
	if(node->data == NULL) {
		if(errnum != NULL) *errnum = 1;
		return NULL;
	}
	
	memcpy(node->data, data, size);
	
	node->next = NULL;
	node->prio = prio;
	
	return node;
}

void free_node(node_t **node, int* errnum) {
	if((node == NULL) || (*node == NULL)) {
		if(errnum != NULL) *errnum = 2;
		return;
	}
	if((*node)->data != NULL) {
		free((*node)->data);
		++free_cnt;
	}
	free(*node);
	++free_cnt;

	*node = NULL;
}

pqueue_t* create_pq(int *errnum) {
	pqueue_t *pq = (pqueue_t*) malloc(sizeof(pqueue_t));
	++malloc_cnt;

	if(pq == NULL) {
		if(errnum != NULL) *errnum = 1;
		return NULL;
	}
	pq->head = NULL;
	return pq;
}

uint8_t is_pq_empty(pqueue_t *pq, int *errnum) {
	if(pq == NULL) {
		if(errnum != NULL) *errnum = 2;
		return 0;
	}
	return (pq->head == NULL);
}

void pq_push(pqueue_t *pq, void* data, size_t size, int64_t prio, int *errnum) {
	if(pq == NULL) {
		if(errnum != NULL) *errnum = 2;
		return;
	}
	
	if((pq->head == NULL) || (pq->head->prio < prio)) {
		node_t *temp = pq->head;
		pq->head = create_node(data, size, prio, errnum);
		pq->head->next = temp;
		return;
	}
	
	node_t *iter = pq->head;
	while(iter->next && (iter->next->prio > prio)) {
		iter = iter->next;
	}
	node_t *node = create_node(data, size, prio, errnum);
	if(node == NULL) return;
	node_t* temp = iter->next;
	iter->next = node;
	node->next = temp;
}

void* pq_pop(pqueue_t *pq, int *errnum) {
	if(pq == NULL) {
		if(errnum != NULL) *errnum = 2;
		return NULL;
	}
	if(pq->head == NULL) {
		if(errnum != NULL) *errnum = 3;
		return NULL;
	}
	
	node_t *temp = pq->head;
	void* data = temp->data;
	pq->head = pq->head->next;
	free(temp);
	++free_cnt;
	return data;
}

void* pq_peek(pqueue_t *pq, int *errnum) {
	if(pq == NULL) {
		if(errnum != NULL) *errnum = 2;
		return NULL;
	}
	if(pq->head == NULL) {
		if(errnum != NULL) *errnum = 3;
		return NULL;
	}
	return pq->head->data;
}

size_t pq_elem_count(pqueue_t *pq, int *errnum) {
	if(pq == NULL) {
		if(errnum != NULL) *errnum = 2;
		return 0;
	}
	size_t i;
	node_t *iter = pq->head;
	for(i = 0; iter; ++i) {
		iter = iter->next;
	}
	return i;
}

void free_pq(pqueue_t *pq, int *errnum) {
	if(pq == NULL) {
		if(errnum != NULL) *errnum = 2;
		return;
	}
	node_t *iter = pq->head;
	while(iter) {
		node_t *temp = iter;
		iter = iter->next;
		free_node(&temp, errnum);
	}
	free(pq);
	++free_cnt;
}