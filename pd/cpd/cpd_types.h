#ifndef CPD_TYPES_H
#define CPD_TYPES_H

#include "cpd_def.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef float t_cpd_float;

struct _atom;
typedef struct _atom t_cpd_atom;

struct _symbol;
typedef struct _symbol t_cpd_symbol;

struct _text;
typedef struct _text t_cpd_object;

struct _glist;
typedef struct _glist t_cpd_canvas;

struct _cpd_list;
typedef struct _cpd_list t_cpd_list;

struct _garray;
typedef struct _garray t_cpd_array;

struct _cpd_connection;
typedef struct _cpd_connection t_cpd_connection;

struct _cpd_audio_devlist;
typedef struct _cpd_audio_devlist t_cpd_audio_devlist;

typedef enum _cpd_conn_type {
    CPD_CONNECTION_CONTROL = 0,
    CPD_CONNECTION_SIGNAL = 1
} t_cpd_conn_type;

typedef enum _cpd_array_flags {
    // do not change values
    CPD_ARRAY_SAVE_CONTENT = 1,
    CPD_ARRAY_STYLE_POLY = 2,
    CPD_ARRAY_STYLE_POINTS = 4,
    CPD_ARRAY_STYLE_BEZIER = 6,
    CPD_ARRAY_HIDE_NAME = 1 << 3
} t_cpd_array_flags;

/**
 * Creates new symbol from given string. Caller should NOT free result pointer
 * @param str - symbol string
 * @return pointer to internal PureData hash table
 */
CPD_EXTERN t_cpd_symbol* cpd_symbol(const char* str);

/**
 * Returns symbol name. Caller should NOT free result pointer
 * @return pointer to internal PureData string
 */
CPD_EXTERN const char* cpd_symbol_name(const t_cpd_symbol* s);

#ifdef __cplusplus
}
#endif

#endif // CPD_TYPES_H
