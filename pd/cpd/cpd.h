#ifndef LIB_CMP_H
#define LIB_CMP_H

#include <stddef.h>

#include "cpd_atom.h"
#include "cpd_canvas.h"
#include "cpd_env.h"
#include "cpd_list.h"
#include "cpd_object.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief initializes pd library
 * @return 1 on success, 0 on error
 */
CPD_EXTERN int cpd_init();

CPD_EXTERN int cpd_stop();

/** 
 * standard pd hook for print function
 */
typedef void (*t_printhook)(const char* s);

/**
 * @brief connects to print hook function
 * @param h - pointer to function
 */
CPD_EXTERN void cpd_setprinthook(t_printhook h);

/**
 * @brief check if canvas given
 * @param x - pointer to object
 * @return 1 is given object is canvas, otherwise 0
*/
CPD_EXTERN int cpd_is_canvas(t_cpd_object* x);

/**
 * Print Pd error message to console
 * @param msg - formatted messages
 */
CPD_EXTERN void cpd_error(const char* msg, ...);

#ifdef __cplusplus
}
#endif

#endif // LIB_CMP_H
