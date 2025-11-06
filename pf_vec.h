#ifndef PF_VEC_H
#define PF_VEC_H

// --------------- poopenfarten vector ------------------- //
// ---------------      pf_vec.h       ------------------- //

// Single header vector library made by Z6dev
// The Unlicense, please do not credit me.
// Who would use it anyway?

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Use this bruh HEHE BOI
#define pf_vec_t(T)                                                                                \
	struct {                                                                                       \
		T *data;                                                                                   \
		size_t size;                                                                               \
		size_t capacity;                                                                           \
	}

// Syntactic Sugar
#define pf_vec(T) pf_vec_t(T)

// Implementation
//------------------------------------------------------------

#define pf_vec_init()                                                                              \
	{ NULL, 0, 0 }

#define pf_vec_push(vec, value)                                                                    \
	do {                                                                                           \
		if ((vec).size == (vec).capacity) {                                                        \
			(vec).capacity = (vec).capacity ? (vec).capacity * 2 : 4;                              \
			(vec).data = realloc((vec).data, (vec).capacity * sizeof(*(vec).data));                \
			if (!(vec).data) {                                                                     \
				fprintf(stderr, "Out of memory in pf_vec_push!\n");                                \
				exit(1);                                                                           \
			}                                                                                      \
		}                                                                                          \
		(vec).data[(vec).size++] = (value);                                                        \
	} while (0)

#define pf_vec_free(vec)                                                                           \
	do {                                                                                           \
		free((vec).data);                                                                          \
		(vec).data = NULL;                                                                         \
		(vec).size = (vec).capacity = 0;                                                           \
	} while (0)

#define pf_vec_get(vec, i) ((vec).data[(i)])
#define pf_vec_len(vec) ((vec).size)
#define pf_vec_cap(vec) ((vec).capacity)

#endif // PF_VEC_H