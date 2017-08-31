#ifndef CPD_RECEIVRE_H
#define CPD_RECEIVRE_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _receiver t_receiver;
typedef void (*t_cpd_receiver_callback)(t_cpd_list* msg);

CPD_EXTERN void cpd_receiver_init();

static CPD_EXTERN t_cpd_object* cpd_receiver_new();
static CPD_EXTERN void cpd_receiver_set_callback(t_receiver* x, t_cpd_receiver_callback c);

#ifdef __cplusplus
}
#endif

#endif // CPD_receiver_H
