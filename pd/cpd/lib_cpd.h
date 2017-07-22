#ifndef LIB_CMP_H
#define LIB_CMP_H

#ifdef __cplusplus
extern "C" {
#endif

struct _glist;
#define t_canvas struct _glist

////
/// \brief initializes pd library
/// \return 1 on success, 0 on error
///
int cpd_init();

////
/// \brief creates new t_canvas
/// \return new canvas or 0 if failed
///
t_canvas* cpd_new_patch(int x, int y, int w, int h, int font_size);

////
///
///
////
void cpd_error(const char* msg, ...);

#ifdef __cplusplus
}
#endif

#endif // LIB_CMP_H
