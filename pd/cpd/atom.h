#ifndef ATOM_H
#define ATOM_H

#include "cpd_def.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _atom;
typedef struct _atom t_cpd_atom;

/**
 * Create float atom
 * @param f - atom value
 * @returns pointer to new atom, it should be free via cpd_atom_free 
 */
CPD_EXTERN t_cpd_atom* cpd_atom_float_new(float f);

/**
 * Create symbol atom
 * @param s - string value, that is converted to symbol via gensym() call
 * @return  pointer to new atom
 */
CPD_EXTERN t_cpd_atom* cpd_atom_symbol_new(const char* s);

/**
 * Sets atom float value and set it's type to float
 * @param a - pointer to atom
 * @param f - float value
 */
CPD_EXTERN void cpd_atom_set_float(t_cpd_atom* a, float f);

/**
 * Sets atom symbol value and set it's type to symbol
 * @param a - pointer to atom
 * @param s - string value
 */
CPD_EXTERN void cpd_atom_set_symbol(t_cpd_atom* a, const char* s);

/**
 * Checks if float atom
 * @param a - pointer to atom
 * @return 1 if float, otherwise 0
 */
CPD_EXTERN int cpd_atom_is_float(t_cpd_atom* a);

/**
 * Checks if symbol atom
 * @param a - pointer to atom
 * @return 1 if symbol, otherwise 0
 */
CPD_EXTERN int cpd_atom_is_symbol(t_cpd_atom* a);

/**
 * Returns float atom value
 * @param a - pointer to atom
 * @returns float value or 0 if not float, or NULL
 */
CPD_EXTERN float cpd_atom_float(t_cpd_atom* a);

/**
 * Returns symbol atom value
 * @param a - pointer to atom
 * @return C-string value or NULL if not symbol or NULL
 */
CPD_EXTERN const char* cpd_atom_symbol(t_cpd_atom* a);

/**
 * Destruct atom, created via cpd_atom_float etc.
 * @param a - pointer to atom
 */
CPD_EXTERN void cpd_atom_free(t_cpd_atom* a);

#ifdef __cplusplus
}
#endif

#endif // ATOM_H
