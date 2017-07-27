#ifndef ATOMLIST_H
#define ATOMLIST_H

#include "atom.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _cpd_atomlist;
typedef struct _cpd_atomlist t_cpd_atomlist;

t_cpd_atomlist* cpd_atomlist_new(size_t n);
t_cpd_atomlist* cpd_atomlist_copy(const t_cpd_atomlist* l);
void cpd_atomlist_free(t_cpd_atomlist* l);
void cpd_atomlist_clear(t_cpd_atomlist* l);
t_cpd_atomlist* cpd_atomlist_new_from_string(const char* s);
size_t cpd_atomlist_size(const t_cpd_atomlist* l);
t_cpd_atom* cpd_atomlist_at(t_cpd_atomlist* l, size_t n);
void cpd_atomlist_append(t_cpd_atomlist* l, const t_cpd_atom* a);

#ifdef __cplusplus
}
#endif

#endif // ATOMLIST_H
