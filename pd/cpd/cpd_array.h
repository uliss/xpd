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
 * Returns array size
 * @param a - pointer to array
 * @return array size or 0 on error
 */
CPD_EXTERN size_t cpd_array_size(t_cpd_array* a);

/**
 * Create new array
 * @param c - parent canvas
 * @param name - array name
 * @param size - array size (>0)
 * @param flags - t_cpd_array_flags
 * @return pointer to new array 
 */
CPD_EXTERN t_cpd_array* cpd_array_new(t_cpd_canvas* c, t_cpd_symbol* name, size_t size, int flags);

/**
 * Free array
 * @param c - pointer to parent canvas
 * @param arr - pointer to array
 */
CPD_EXTERN void cpd_array_free(t_cpd_canvas* c, t_cpd_array* arr);

/**
 * Returns array graph line width
 * @param arr - pointer to array
 * @return linewidth (currently 1 or 2) or 0 on error
 */
CPD_EXTERN t_cpd_float cpd_array_linewidth(t_cpd_array* arr);

/**
 * Sets array graph line width
 * @param arr - pointer to array
 * @param wd - new line width
 * @return 1 on success, 0 on error
 */
CPD_EXTERN int cpd_array_set_linewidth(t_cpd_array* arr, t_cpd_float wd);

/**
 * Returns array plot style: CPD_ARRAY_STYLE_POLY, CPD_ARRAY_STYLE_POINTS or CPD_ARRAY_STYLE_BEZIER
 * @param arr - pointer to array
 * @return on error returns 0
 */
CPD_EXTERN t_cpd_array_flags cpd_array_plotstyle(t_cpd_array* arr);

/**
 * Returns value of named float field
 * @param arr - pointer to array
 * @param name - field name
 * @return 0 on error
 */
t_cpd_float cpd_array_float_field(t_cpd_array* arr, t_cpd_symbol* name);

/**
 * Sets value of named float field
 * @param arr - pointer to array
 * @param name - field name
 * @return 0 on error, 1 on success
 */
int cpd_array_set_float_field(t_cpd_array* arr, t_cpd_symbol* name, t_cpd_float val);

#ifdef __cplusplus
}
#endif

#endif // CPD_ATOM_H
