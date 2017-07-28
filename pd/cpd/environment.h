#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "cpd_def.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

CPD_EXTERN int cpd_version_major();
CPD_EXTERN int cpd_version_minor();
CPD_EXTERN int cpd_version_bugfix();

#ifdef __cplusplus
}
#endif

#endif // ENVIRONMENT_H
