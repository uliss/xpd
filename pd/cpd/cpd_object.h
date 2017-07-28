#ifndef CPD_OBJECT_H
#define CPD_OBJECT_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates new object on specified canvas
 * @param c - parent canvas
 * @param name - object name
 * @param args - arguments list structure
 * @param x - X-position on canvas
 * @param y - Y-position on canvas
 * @return pointer to new object or NULL
 */
CPD_EXTERN t_cpd_object* cpd_object_new(t_cpd_canvas* c, const char* name, const t_cpd_list* args, int x, int y);

/**
 * @brief Removed object from canvas and frees it
 * @param cnv - object canvas
 * @param obj - obj pointer
 */
CPD_EXTERN void cpd_object_free(t_cpd_canvas* cnv, t_cpd_object* obj);

/**
 * @brief Returns object name
 * @param obj - pointer to object
 * @return object name or empty string on error
 */
CPD_EXTERN const char* cpd_object_name(t_cpd_object* obj);

/**
 * Returns object arguments. Caller should free result
 * @param obj - pointer to object
 */
CPD_EXTERN t_cpd_list* cpd_object_arguments(t_cpd_object* obj);

/**
 * Returns object string representation. 
 * @note Caller should free result string
 * @return empty string on error
 */
CPD_EXTERN const char* cpd_object_text(t_cpd_object* obj);

/**
 * Object x-coord within toplevel
 */
CPD_EXTERN int cpd_object_xpos(t_cpd_object* obj);

/**
 * Object y-coord within toplevel
 */
CPD_EXTERN int cpd_object_ypos(t_cpd_object* obj);

/**
 * Set object x-coord within toplevel
 */
CPD_EXTERN void cpd_object_set_xpos(t_cpd_object* obj, int x);

/**
 * Set object x-coord within toplevel
 */
CPD_EXTERN void cpd_object_set_ypos(t_cpd_object* obj, int y);

/**
 * Number of inlets in object
 * @param obj - pointer to object
 */
CPD_EXTERN size_t cpd_object_inlet_count(t_cpd_object* obj);

/**
 * Number of outlets in object
 * @param obj - pointer to object
 */
CPD_EXTERN size_t cpd_object_outlet_count(t_cpd_object* obj);

/**
 * Connects two objects
 * @return 1 on success, 0 on error
 */
CPD_EXTERN int cpd_connect(t_cpd_object* obj1, size_t outno, t_cpd_object* obj2, size_t inno);

/**
 * Sends bang to object
 */
CPD_EXTERN void cpd_send_bang(t_cpd_object* obj);

/**
 * Sends float to object
 */
CPD_EXTERN void cpd_send_float(t_cpd_object* obj, t_cpd_float f);

/**
 * Sends symbol to object
 */
CPD_EXTERN void cpd_send_symbol(t_cpd_object* obj, t_cpd_symbol* s);

#ifdef __cplusplus
}
#endif

#endif // CPD_OBJECT_H
