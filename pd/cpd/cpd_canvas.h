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
 * @see cpd_canvas_free()
 */
CPD_EXTERN t_cpd_canvas* cpd_root_canvas_new();

/**
 * Loads patch from filesystem
 * @param name - name of file
 * @param path - patch directory (if NULL given search file in strandart search paths)
 * @return pointer to root canvas or NULL on error
 */
CPD_EXTERN t_cpd_canvas* cpd_root_canvas_load(const char* name, const char* path);

/** 
 * @return pointer to last root (top) canvas or 0 if not found
 * @see cpd_root_canvas_next(), cpd_root_canvas_count()
 */
CPD_EXTERN t_cpd_canvas* cpd_root_canvas_last();

/**
 * Returns number of root (top) canvases
 */
CPD_EXTERN size_t cpd_root_canvas_count();

/**
  * Returns pointer to next canvas in list
  * @see cpd_root_canvas_last()
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
CPD_EXTERN const char* cpd_canvas_name(t_cpd_canvas* cnv);

/**
 * Returns canvas font size or -1 on error
 */
CPD_EXTERN int cpd_canvas_fontsize(t_cpd_canvas* cnv);

/**
 * Returns pointer to root (top level) parent canvas or 0 if already top
 * @see cpd_canvas_is_root()
 */
CPD_EXTERN t_cpd_canvas* cpd_canvas_root(t_cpd_canvas* cnv);

/**
 * Returns pointer to current canvas
 * @see cpd_canvas_set_current()
 */
CPD_EXTERN t_cpd_canvas* cpd_canvas_current();

/**
 * Push current canvas to current canvas stack
 * @param cnv - pointer to canvas
 * @see cpd_canvas_current()
 */
CPD_EXTERN void cpd_canvas_set_current(t_cpd_canvas* cnv);

/**
 * Pops current canvas from canvas stack
 * @param cnv - pointer to canvas
 * @see cpd_canvas_current()
 */
CPD_EXTERN void cpd_canvas_unset_current(t_cpd_canvas* cnv);

/**
  * Removes canvas
  * @param c - pointer to canvas
  * @see cpd_canvas_new
  */
CPD_EXTERN int cpd_canvas_free(t_cpd_canvas* cnv);

/**
 * Checks if canvas is root (top-level)
 * @return 1 if given canvas is root, 0 otherwise
 * @see cpd_canvas_root()
 */
CPD_EXTERN int cpd_canvas_is_root(t_cpd_canvas* cnv);

/**
 * Returns number of child element on canvas 
 * @see cpd_canvas_object_first()
 */
CPD_EXTERN size_t cpd_canvas_object_count(t_cpd_canvas* cnv);

/**
 * Returns pointer to first object on canvas
 * @param cnv - pointer to canvas
 * @return pointer to object or NULL if not found
 * @see cpd_canvas_object_count()
 */
CPD_EXTERN t_cpd_object* cpd_canvas_object_first(t_cpd_canvas* cnv);

/**
 * Converts pointer to canvas to pointer to object
 * @param cnv - pointer to canvas
 * @return pointer to object or NULL on error
 */
CPD_EXTERN t_cpd_object* cpd_canvas_to_object(t_cpd_canvas* cnv);

#ifdef __cplusplus
}
#endif

#endif // CPD_CANVAS_H
