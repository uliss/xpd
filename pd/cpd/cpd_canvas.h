#ifndef CPD_CANVAS_H
#define CPD_CANVAS_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates new patch
 * @return pointer to new top-level canvas or NULL on error
 * @see cpd_canvas_free()
 */
CPD_EXTERN t_cpd_canvas* cpd_patch_new();

/**
 * Loads patch from filesystem
 * @param name - name of file
 * @param path - patch directory (if NULL given search file in strandart search paths)
 * @return pointer to loaded canvas or NULL on error
 */
CPD_EXTERN t_cpd_canvas* cpd_patch_load(const char* name, const char* path);

/** 
 * @return pointer to last opened patch or NULL if not found
 * @see cpd_patchlist_next(), cpd_patchlist_count()
 */
CPD_EXTERN t_cpd_canvas* cpd_patchlist_last();

/**
 * Returns number of opened patches
 */
CPD_EXTERN size_t cpd_patchlist_count();

/**
  * Returns pointer to next opened patch in list
  * @see cpd_patchlist_last()
  */
CPD_EXTERN t_cpd_canvas* cpd_patchlist_next(t_cpd_canvas* cnv);

/**
 * Returns pointer to opened patch by specified number
 */
CPD_EXTERN t_cpd_canvas* cpd_patchlist_at(size_t n);

/**
  * Returns root canvas directory path or "" on error
  */
CPD_EXTERN const char* cpd_patch_dir(t_cpd_canvas* cnv);

CPD_EXTERN int cpd_patch_xpos(t_cpd_canvas* cnv);
CPD_EXTERN int cpd_patch_ypos(t_cpd_canvas* cnv);

/**
 * Returns root canvas width
 * @param cnv - pointer to canvas
 * @return width or 0 on error
 * @see cpd_patch_height()
 */
CPD_EXTERN int cpd_patch_width(t_cpd_canvas* cnv);

/**
 * Returns root canvas height
 * @param cnv - pointer to canvas
 * @return height or 0 on error
 * @see cpd_patch_width()
 */
CPD_EXTERN int cpd_patch_height(t_cpd_canvas* cnv);

CPD_EXTERN t_cpd_canvas* cpd_subpatch_new(t_cpd_canvas* parent,
    const char* name, t_cpd_list* args, int x, int y);

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
 * @see cpd_canvas_first_object()
 */
CPD_EXTERN size_t cpd_canvas_object_count(t_cpd_canvas* cnv);

/**
 * Returns pointer to first object on canvas
 * @param cnv - pointer to canvas
 * @return pointer to object or NULL if not found
 * @see cpd_canvas_object_count()
 */
CPD_EXTERN t_cpd_object* cpd_canvas_first_object(t_cpd_canvas* cnv);

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
