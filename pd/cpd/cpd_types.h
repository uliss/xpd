#ifndef CPD_TYPES_H
#define CPD_TYPES_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef float t_cpd_float;

struct _atom;
typedef struct _atom t_cpd_atom;

struct _cpd_list;
typedef struct _cpd_list t_cpd_atomlist;

#ifdef __cplusplus
}
#endif

#endif // CPD_TYPES_H
