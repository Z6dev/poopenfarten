#ifndef PF_VEC_H
#define PF_VEC_H

// --------------- poopenfarten vector ------------------- //
// ---------------      pf_vec.h       ------------------- //

// Single header vector library made by Z6dev
// The Unlicense, please do not credit me.
// Who would use it anyway?
// Define PF_VEC_IMPLEMENTATION in only ONE source file to use this library

#include <stdlib.h>

typedef struct {
	size_t capacity;
	size_t size;
} _pf__vec_header;

#define _pf_getVectorHeader(vector) ((_pf__vec_header*)((char*)(vector) - sizeof(_pf__vec_header)))

#define pf_vectorSize(vector) ((vector) ? _pf_getVectorHeader(vector)->size : 0)
#define pf_vectorCapacity(vector) ((vector) ? _pf_getVectorHeader(vector)->capacity : 0)

// Create a new vector
#define pf_vectorCreate(T, cap) \
	((T*)vec__create(sizeof(T), cap))

// Push a new element
#define pf_vectorPush(vector, value)                             \
	do {                                                         \
		if (pf_vectorSize(vector) == pf_vectorCapacity(vector))  \
			(vector) = vec__grow(vector, sizeof(*(vector)));     \
		(vector)[_pf_getVectorHeader(vector)->size++] = (value); \
	} while (0)

// Free vector
#define pf_vectorFree(vector)                          \
	do {                                               \
		if (vector) free(_pf_getVectorHeader(vector)); \
		vector = NULL;                                 \
	} while (0)


#ifdef PF_VECTOR_IMPLEMENTATION

// Internal helpers
static void* _pf__vec__create(size_t elem_size, size_t capacity) {
	_pf__vec_header* h = malloc(sizeof(_pf__vec_header) + elem_size * capacity);
	h->size = 0;
	h->capacity = capacity;
	return (void*)(h + 1);
}

static void* _pf__vec__grow(void* vector, size_t elem_size) {
	size_t new_cap = pf_vectorCapacity(vector) ? pf_vectorCapacity(vector) * 2 : 4;
	_pf__vec_header* old_h = _pf_getVectorHeader(vector);
	_pf__vec_header* new_h = realloc(old_h, sizeof(_pf__vec_header) + elem_size * new_cap);
	new_h->capacity = new_cap;
	return (void*)(new_h + 1);
}
#endif // PF_VECTOR_IMPLEMENTATION

#endif // PF_VEC_H
