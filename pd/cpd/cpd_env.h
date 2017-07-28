#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

CPD_EXTERN int cpd_version_major();
CPD_EXTERN int cpd_version_minor();
CPD_EXTERN int cpd_version_bugfix();

CPD_EXTERN void cpd_searchpath_append(const char* path);
CPD_EXTERN size_t cpd_searchpath_num();
CPD_EXTERN const char* cpd_searchpath_at(size_t idx);
CPD_EXTERN void cpd_searchpath_clear();

#ifdef __cplusplus
}
#endif

#endif // ENVIRONMENT_H
