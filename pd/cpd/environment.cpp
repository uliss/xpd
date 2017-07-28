#include "environment.h"
#include "m_pd.h"

int cpd_version_major()
{
    return PD_MAJOR_VERSION;
}

int cpd_version_minor()
{
    return PD_MINOR_VERSION;
}

int cpd_version_bugfix()
{
    return PD_BUGFIX_VERSION;
}
