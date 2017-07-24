#ifndef LIB_CMP_H
#define LIB_CMP_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _text;
struct _glist;

typedef struct _glist t_cpd_canvas;
typedef struct _text t_object;

/**
 * Creates new root (top-level) canvas
 * @return pointer to new canvas or NULL on error
 */
t_cpd_canvas* cpd_root_canvas_new();

/** 
 * \return pointer to last root (top) canvas or 0 if not found
 */
t_cpd_canvas* cpd_root_canvas_last();

/**
 * Returns number of root (top) canvases
 */
size_t cpd_root_canvas_count();

/**
  * Returns pointer to next canvas in list
  */
t_cpd_canvas* cpd_root_canvas_next(t_cpd_canvas* cnv);

/**
 * Returns pointer to root canvas at given position
 */
t_cpd_canvas* cpd_root_canvas_at(size_t n);

/**
  * Returns root canvas directory path or "" on error
  */
const char* cpd_root_canvas_dir(t_cpd_canvas* cnv);

int cpd_root_canvas_x(t_cpd_canvas* cnv);
int cpd_root_canvas_y(t_cpd_canvas* cnv);
int cpd_root_canvas_width(t_cpd_canvas* cnv);
int cpd_root_canvas_height(t_cpd_canvas* cnv);

/**
 * Returns canvas name
 */
const char* cpd_canvas_name(t_cpd_canvas* c);

/**
 * Returns canvas font size or -1 on error
 */
int cpd_canvas_fontsize(t_cpd_canvas* c);

/**
 * Returns pointer to root (top level) parent canvas or 0 if already top
 */
t_cpd_canvas* cpd_canvas_root(t_cpd_canvas* c);

/**
 * Returns pointer to current canvas
 */
t_cpd_canvas* cpd_canvas_current();

/**
  * Removes canvas
  */
int cpd_canvas_free(t_cpd_canvas* c);

/**
 * Checks if canvas is root (top-level)
 */
int cpd_canvas_is_root(t_cpd_canvas* c);

////
/// \brief initializes pd library
/// \return 1 on success, 0 on error
///
int cpd_init();

int cpd_stop();

////
/// \brief check if canvas given
/// \param x - pointer to object
/// \return 1 is given object is canvas, otherwise 0
///
int cpd_is_canvas(t_object* x);

////
///
///
////
void cpd_error(const char* msg, ...);

#ifdef __cplusplus
}
#endif

#endif // LIB_CMP_H
