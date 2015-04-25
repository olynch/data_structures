#ifndef ASSOC_ARRAY_H
#define ASSOC_ARRAY_H
#define DEFAULT_NUM_BUCKETS 20
#define DEFAULT_NUM_PAIRS 10

typedef struct {
	char *key;
	int val;
} pair;

typedef struct {
	pair *data;
	int size;
	int end;
} bucket;

typedef struct {
	bucket *buckets;
	int num_buckets;
} HashMap;

HashMap * HashMap_alloc(void);
void HashMap_dealloc(HashMap *self);

void HashMap_set(HashMap *self, char *key, int val);
int HashMap_get(HashMap *self, char *key);

int hash(char *key, int range);

#endif
