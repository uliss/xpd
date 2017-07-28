#ifndef CPD_CANVAS_H
#define CPD_CANVAS_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates new root (top-level) canvas
 * @return pointer to new canvas or NULL on error
 */
CPD_EXTERN t_cpd_canvas* cpd_root_canvas_new();

/** 
 * @return pointer to last root (top) canvas or 0 if not found
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
 * Returns number of child element on canvas 
 */
CPD_EXTERN size_t cpd_canvas_object_count(t_cpd_canvas* cnv);

#ifdef __cplusplus
}
#endif

#endif // CPD_CANVAS_H
