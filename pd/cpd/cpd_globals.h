#ifndef CPD_GLOBALS_H
#define CPD_GLOBALS_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern t_cpd_symbol* CPD_SYMBOL_PD;
extern t_cpd_symbol* CPD_SYMBOL_OBJ;
extern t_cpd_symbol* CPD_SYMBOL_DSP;
extern t_cpd_symbol* CPD_SYMBOL_EMPTY;

void cpd_globals_init();

#ifdef __cplusplus
}
#endif

#endif // CPD_GLOBALS_H
