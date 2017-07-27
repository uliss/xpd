#ifndef ATOM_H
#define ATOM_H

#ifdef __cplusplus
extern "C" {
#endif

struct _atom;
typedef struct _atom t_cpd_atom;

t_cpd_atom* cpd_atom_float_new(float f);
t_cpd_atom* cpd_atom_symbol_new(const char* s);
void cpd_atom_set_float(t_cpd_atom* a, float f);
void cpd_atom_set_symbol(t_cpd_atom* a, const char* s);
int cpd_atom_is_float(t_cpd_atom* a);
int cpd_atom_is_symbol(t_cpd_atom* a);
float cpd_atom_float(t_cpd_atom* a);
const char* cpd_atom_symbol(t_cpd_atom* a);
void cpd_atom_free(t_cpd_atom* a);

#ifdef __cplusplus
}
#endif

#endif // ATOM_H
