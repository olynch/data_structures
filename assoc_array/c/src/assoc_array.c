#include "assoc_array.h"
#include <stdlib.h>
#include <string.h>

HashMap * HashMap_alloc(void) {
	HashMap *self = (HashMap *) malloc(sizeof(HashMap));
	if (self == NULL) /* do something */;
	self->buckets = (bucket *) malloc(sizeof(bucket) * DEFAULT_NUM_BUCKETS);
	self->num_buckets = DEFAULT_NUM_BUCKETS;
	for (int i = 0; i < DEFAULT_NUM_BUCKETS; ++i) {
		self->buckets[i].data = (pair *) calloc(sizeof(pair) * DEFAULT_NUM_PAIRS, sizeof(pair));
		self->buckets[i].end = 0;
		self->buckets[i].end = DEFAULT_NUM_PAIRS;
	}
	return self;
}

void HashMap_dealloc(HashMap *self) {
	for (int i = 0; i < self->num_buckets; ++i) {
		free(self->buckets[i].data);
	}
	free(self);
}

void HashMap_set(HashMap *self, char *key, int val) {
	int index = hash(key, self->num_buckets);
	bucket *cur = self->buckets + index;
	for (int i = 0; i < cur->end; ++i) {
		if (strcmp(key, cur->data[i].key)) {
			cur->data[i].val = val;
			return;
		}
	}
	/* grow-shrink if needed */
	if (cur->end >= cur->size) {
		cur->size *= 2;
		cur->data = realloc((void *) cur->data, sizeof(pair) * cur->size);
	}
	if (cur->end <= cur->size / 3 && cur->size > DEFAULT_NUM_PAIRS) {
		cur->size /= 2;
		cur->data = realloc((void *) cur->data, sizeof(pair) * cur->size);
	}
	cur->end++;
	cur->data[cur->end].key = malloc(strlen(key));
	strcpy(key, cur->data[cur->end].key);
	cur->data[cur->end].val = val;
}

int HashMap_get(HashMap *self, char *key) {
	int index = hash(key, self->num_buckets);
	bucket *cur = self->buckets + index;
	for (int i  = 0; i < cur->end; ++i) {
		if (strcmp(key, cur->data[i].key)) {
			return cur->data[i].val;
		}
	}
	return -1;
}

int hash(char *key, int range) {
	char c;
	int sum = 0;
	while (c != '\0') {
		c = *(key++);
		sum += c;
	}
	return (sum % range);
}
