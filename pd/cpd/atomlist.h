#ifndef ATOMLIST_H
#define ATOMLIST_H

#include "atom.h"
#include "cpd_def.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _cpd_atomlist;
typedef struct _cpd_atomlist t_cpd_atomlist;

/**
 * Creates new atomlist of given size initialized with zeroes.
 * @param n - list size
 * @return pointer to allocated list. You should free it with cpd_atomlist_free()
 */
CPD_EXTERN t_cpd_atomlist* cpd_atomlist_new(size_t n);

/**
 * Creates atomlist copy
 * @param l - source atomlist
 * @return pointer to new allocated atomlist or NULL on error
 */
CPD_EXTERN t_cpd_atomlist* cpd_atomlist_copy(const t_cpd_atomlist* l);

/**
 * Free atomlist. NULL pointers are valid
 */
CPD_EXTERN void cpd_atomlist_free(t_cpd_atomlist* l);

/**
 * Removes all element from atomlist, but not frees it
 * @param l - pointer to atomlist
 */
CPD_EXTERN void cpd_atomlist_clear(t_cpd_atomlist* l);

/**
 * Creates new atomlist from given string, parsing it to separate atoms
 * @param s - string
 * @return pointer to alloacted atomlist. You should free it.
 */
CPD_EXTERN t_cpd_atomlist* cpd_atomlist_new_from_string(const char* s);

/**
 * Returns number of elements in atomlist or 0 on error. 
 */
CPD_EXTERN size_t cpd_atomlist_size(const t_cpd_atomlist* l);

/**
 * Returns pointer to element at specified position in atomlist
 * @param l - pointer to list
 * @param n - list position
 * @return pointer to element or NULL on error
 */
CPD_EXTERN t_cpd_atom* cpd_atomlist_at(t_cpd_atomlist* l, size_t n);

/**
 * Appends copy of given atom to the end of atomlist
 * @param l - pointer to list
 * @param a - pointer to attom
 */
CPD_EXTERN void cpd_atomlist_append(t_cpd_atomlist* l, const t_cpd_atom* a);

/**
 * Appends float value to list
 * @param l - pointer to list
 * @param f - float value
 */
CPD_EXTERN void cpd_atomlist_append_float(t_cpd_atomlist* l, float f);

/**
 * Appends symbol value to list
 * @param l - pointer to list
 * @param f - float value
 */
CPD_EXTERN void cpd_atomlist_append_symbol(t_cpd_atomlist* l, const char* f);

/**
 * Set atomlist element at specified position
 * @param l - pointer to list
 * @param idx - element position
 * @param a - pointer to source atom
 * @return 1 on success and 0 on error
 */
CPD_EXTERN int cpd_atomlist_set_atom(t_cpd_atomlist* l, size_t idx, const t_cpd_atom* a);

#ifdef __cplusplus
}
#endif

#endif // ATOMLIST_H
