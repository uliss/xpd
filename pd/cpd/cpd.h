#ifndef LIB_CMP_H
#define LIB_CMP_H

#include <stddef.h>

#include "cpd_atom.h"
#include "cpd_env.h"
#include "cpd_list.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _text;
struct _glist;

typedef struct _glist t_cpd_canvas;
typedef struct _text t_cpd_object;

/**
 * Creates new root (top-level) canvas
 * @return pointer to new canvas or NULL on error
 */
CPD_EXTERN t_cpd_canvas* cpd_root_canvas_new();

/** 
 * \return pointer to last root (top) canvas or 0 if not found
 */
CPD_EXTERN t_cpd_canvas* cpd_root_canvas_last();

/**
 * Returns number of root (top) canvases
 */
CPD_EXTERN size_t cpd_root_canvas_count();

/**
  * Returns pointer to next canvas in list
  */
CPD_EXTERN t_cpd_canvas* cpd_root_canvas_next(t_cpd_canvas* cnv);

/**
 * Returns pointer to root canvas at given position
 */
CPD_EXTERN t_cpd_canvas* cpd_root_canvas_at(size_t n);

/**
  * Returns root canvas directory path or "" on error
  */
CPD_EXTERN const char* cpd_root_canvas_dir(t_cpd_canvas* cnv);

CPD_EXTERN int cpd_root_canvas_x(t_cpd_canvas* cnv);
CPD_EXTERN int cpd_root_canvas_y(t_cpd_canvas* cnv);
CPD_EXTERN int cpd_root_canvas_width(t_cpd_canvas* cnv);
CPD_EXTERN int cpd_root_canvas_height(t_cpd_canvas* cnv);

/**
 * Returns canvas name
 */
CPD_EXTERN const char* cpd_canvas_name(t_cpd_canvas* c);

/**
 * Returns canvas font size or -1 on error
 */
CPD_EXTERN int cpd_canvas_fontsize(t_cpd_canvas* c);

/**
 * Returns pointer to root (top level) parent canvas or 0 if already top
 */
CPD_EXTERN t_cpd_canvas* cpd_canvas_root(t_cpd_canvas* c);

/**
 * Returns pointer to current canvas
 */
CPD_EXTERN t_cpd_canvas* cpd_canvas_current();

/**
  * Removes canvas
  */
CPD_EXTERN int cpd_canvas_free(t_cpd_canvas* c);

/**
 * Checks if canvas is root (top-level)
 */
CPD_EXTERN int cpd_canvas_is_root(t_cpd_canvas* c);

/**
 * Creates new object on specified canvas
 * @param c - parent canvas
 * @param name - object name
 * @param args - arguments list structure
 * @param x - X-position on canvas
 * @param y - Y-position on canvas
 * @return pointer to new object or NULL
 */
CPD_EXTERN t_cpd_object* cpd_object_new(t_cpd_canvas* c, const char* name, const t_cpd_atomlist* args, int x, int y);

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
CPD_EXTERN t_cpd_atomlist* cpd_object_arguments(t_cpd_object* obj);

CPD_EXTERN const char* cpd_object_text(t_cpd_object* obj);

CPD_EXTERN int cpd_object_xpos(t_cpd_object* obj);
CPD_EXTERN int cpd_object_ypos(t_cpd_object* obj);
CPD_EXTERN void cpd_object_set_xpos(t_cpd_object* obj, int x);
CPD_EXTERN void cpd_object_set_ypos(t_cpd_object* obj, int y);

CPD_EXTERN size_t cpd_object_inlet_count(t_cpd_object* obj);
CPD_EXTERN size_t cpd_object_outlet_count(t_cpd_object* obj);

CPD_EXTERN int cpd_connect(t_cpd_object* obj1, size_t outno, t_cpd_object* obj2, size_t inno);

CPD_EXTERN void cpd_send_bang(t_cpd_object* obj);
CPD_EXTERN void cpd_send_float(t_cpd_object* obj, float f);

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
