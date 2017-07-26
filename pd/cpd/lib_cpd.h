#ifndef LIB_CMP_H
#define LIB_CMP_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _atom;
struct _text;
struct _glist;

typedef struct _glist t_cpd_canvas;
typedef struct _text t_cpd_object;
typedef struct _atom t_cpd_atom;

typedef struct _cpd_atomlist {
    size_t n;
    t_cpd_atom* data;
} t_cpd_atomlist;

t_cpd_atom* cpd_atom_float_new(float f);
t_cpd_atom* cpd_atom_symbol_new(const char* s);
void cpd_atom_set_float(t_cpd_atom* a, float f);
void cpd_atom_set_symbol(t_cpd_atom* a, const char* s);
int cpd_atom_is_float(t_cpd_atom* a);
int cpd_atom_is_symbol(t_cpd_atom* a);
float cpd_atom_float(t_cpd_atom* a);
const char* cpd_atom_symbol(t_cpd_atom* a);
void cpd_atom_free(t_cpd_atom* a);

t_cpd_atomlist* cpd_atomlist_new(size_t n);
void cpd_atomlist_free(t_cpd_atomlist* l);

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

/**
 * Creates new object on specified canvas
 * @param c - parent canvas
 * @param name - object name
 * @param args - arguments list structure
 * @param x - X-position on canvas
 * @param y - Y-position on canvas
 * @return pointer to new object or NULL
 */
t_cpd_object* cpd_object_new(t_cpd_canvas* c, const char* name, t_cpd_atomlist* args, int x, int y);

/**
 * @brief Removed object from canvas and frees it
 * @param cnv - object canvas
 * @param obj - obj pointer
 */
void cpd_object_free(t_cpd_canvas* cnv, t_cpd_object* obj);

/**
 * @brief Returns object name
 * @param obj - pointer to object
 * @return object name or empty string on error
 */
const char* cpd_object_name(t_cpd_object* obj);

int cpd_object_xpos(t_cpd_object* obj);
int cpd_object_ypos(t_cpd_object* obj);
void cpd_object_set_xpos(t_cpd_object* obj, int x);
void cpd_object_set_ypos(t_cpd_object* obj, int y);

size_t cpd_object_inlet_count(t_cpd_object* obj);
size_t cpd_object_outlet_count(t_cpd_object* obj);

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
int cpd_is_canvas(t_cpd_object* x);

////
///
///
////
void cpd_error(const char* msg, ...);

#ifdef __cplusplus
}
#endif

#endif // LIB_CMP_H
