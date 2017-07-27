#include "atom.h"

#include "m_pd.h"

t_cpd_atom* cpd_atom_float_new(float f)
{
    t_atom* a = new t_atom;
    SETFLOAT(a, f);
    return a;
}

void cpd_atom_free(t_cpd_atom* a)
{
    delete a;
}

t_cpd_atom* cpd_atom_symbol_new(const char* s)
{
    t_atom* a = new t_atom;
    SETSYMBOL(a, gensym(s));
    return a;
}

void cpd_atom_set_float(t_cpd_atom* a, float f)
{
    SETFLOAT(a, f);
}

void cpd_atom_set_symbol(t_cpd_atom* a, const char* s)
{
    SETSYMBOL(a, gensym(s));
}

int cpd_atom_is_float(t_cpd_atom* a)
{
    return a->a_type == A_FLOAT ? 1 : 0;
}

int cpd_atom_is_symbol(t_cpd_atom* a)
{
    return a->a_type == A_SYMBOL ? 1 : 0;
}

float cpd_atom_float(t_cpd_atom* a)
{
    if (cpd_atom_is_float(a))
        return a->a_w.w_float;

    return 0;
}

const char* cpd_atom_symbol(t_cpd_atom* a)
{
    if (cpd_atom_is_symbol(a))
        return a->a_w.w_symbol->s_name;

    return 0;
}
