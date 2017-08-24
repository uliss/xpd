#ifndef CPD_ARRAY_H
#define CPD_ARRAY_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get array pointer by name
 */

t_cpd_array* cpd_get_array(t_cpd_symbol* arrayname);

/**
 * Get array data - variant 1, yet disabled
 */
// void cpd_get_array_data(t_cpd_array* a, int* size, float** vec);

/**
 * Get array data - variant 2
 */
float* cpd_get_array_data(t_cpd_array* a);

/**
 * Get array size
 */
int cpd_get_array_size(t_cpd_array* a);

/**
 * Create new array
 */
t_cpd_array* cpd_new_array(t_cpd_canvas* c, t_cpd_symbol* name, t_cpd_float size, t_cpd_float save, t_cpd_float newgraph);

#ifdef __cplusplus
}
#endif

#endif // CPD_ATOM_H
