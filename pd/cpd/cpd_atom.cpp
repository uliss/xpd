#include "cpd_atom.h"
#include "pr_log.h"

#include "m_pd.h"

t_cpd_atom* cpd_atom_float_new(t_cpd_float f)
{
    t_atom* a = new t_atom;
    SETFLOAT(a, f);
    return a;
}

void cpd_atom_free(t_cpd_atom* a)
{
    delete a;
}

t_cpd_atom* cpd_atom_symbol_new(const t_cpd_symbol* s)
{
    t_atom* a = new t_atom;
    SETSYMBOL(a, const_cast<t_cpd_symbol*>(s));
    return a;
}

void cpd_atom_set_float(t_cpd_atom* a, t_cpd_float f)
{
    SETFLOAT(a, f);
}

void cpd_atom_set_string(t_cpd_atom* a, const char* s)
{
    SETSYMBOL(a, gensym(s));
}

int cpd_atom_is_float(const t_cpd_atom* a)
{
    if (!a)
        return 0;

    return a->a_type == A_FLOAT ? 1 : 0;
}

int cpd_atom_is_symbol(const t_cpd_atom* a)
{
    if (!a)
        return 0;

    return a->a_type == A_SYMBOL ? 1 : 0;
}

t_cpd_float cpd_atom_get_float(const t_cpd_atom* a)
{
    return atom_getfloat(const_cast<t_cpd_atom*>(a));
}

void cpd_atom_set_atom(t_cpd_atom* a, const t_cpd_atom* src)
{
    if (!a || !src) {
        console()->error("cpd_atom_set_atom: NULL pointers given");
        return;
    }

    *a = *src;
}

t_cpd_atom* cpd_atom_string_new(const char* s)
{
    return cpd_atom_symbol_new(cpd_symbol_new(s));
}

void cpd_atom_set_symbol(t_cpd_atom* a, t_cpd_symbol* s)
{
    SETSYMBOL(a, s);
}

t_cpd_symbol* cpd_atom_get_symbol(const t_cpd_atom* a)
{
    if (cpd_atom_is_symbol(a))
        return a->a_w.w_symbol;

    return 0;
}