#ifndef CPD_TYPES_H
#define CPD_TYPES_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef float t_cpd_float;

struct _atom;
typedef struct _atom t_cpd_atom;

struct _symbol;
typedef struct _symbol t_cpd_symbol;

struct _cpd_list;
typedef struct _cpd_list t_cpd_list;

/**
 * Creates new symbol from given string. Caller should NOT free result pointer
 * @param str - symbol string
 * @return pointer to internal PureData hash table
 */
t_cpd_symbol* cpd_symbol(const char* str);

/**
 * Returns symbol name. Caller should NOT free result pointer
 * @return pointer to internal PureData string
 */
const char* cpd_symbol_name(const t_cpd_symbol* s);

#ifdef __cplusplus
}
#endif

#endif // CPD_TYPES_H
