#include "cpd_list.h"

#include "m_pd.h"
#include "pr_log.h"

#include <vector>

struct _cpd_list {
    std::vector<t_cpd_atom> data;
};

t_cpd_atomlist* cpd_atomlist_new(size_t n)
{
    t_cpd_atomlist* lst = new t_cpd_atomlist;
    if (n) {
        lst->data.assign(n, t_cpd_atom());
    }

    for (size_t i = 0; i < n; i++) {
        SETFLOAT(&lst->data[i], 0);
    }

    return lst;
}

void cpd_atomlist_free(t_cpd_atomlist* l)
{
    if (!l) {
        console()->error("cpd_atomlist_free: NULL pointer given");
        return;
    }

    delete l;
}

t_cpd_atomlist* cpd_atomlist_new_from_string(const char* s)
{
    t_binbuf* b = binbuf_new();
    binbuf_text(b, s, strlen(s));

    auto ret = new t_cpd_atomlist;

    size_t n = binbuf_getnatom(b);
    t_atom* a = binbuf_getvec(b);

    std::copy(a, a + n, std::back_inserter(ret->data));

    binbuf_free(b);

    return ret;
}

t_cpd_atom* cpd_atomlist_at(t_cpd_atomlist* l, size_t n)
{
    if (!l)
        return 0;

    if (n >= l->data.size())
        return 0;

    return &l->data[n];
}

void cpd_atomlist_clear(t_cpd_atomlist* l)
{
    if (!l)
        return;

    l->data.clear();
}

void cpd_atomlist_append(t_cpd_atomlist* l, const t_cpd_atom* a)
{
    if (!l || !a)
        return;

    l->data.push_back(*a);
}

size_t cpd_atomlist_size(const t_cpd_atomlist* l)
{
    return l ? l->data.size() : 0;
}

t_cpd_atomlist* cpd_atomlist_copy(const t_cpd_atomlist* l)
{
    return l ? new t_cpd_atomlist(*l) : 0;
}

int cpd_atomlist_set_atom(t_cpd_atomlist* l, size_t idx, const t_cpd_atom* a)
{
    if (!l || !a) {
        console()->error("cpd_atomlist_set_atom: NULL arguments");
        return 0;
    }

    if (idx >= l->data.size()) {
        console()->error("cpd_atomlist_set_atom: invalid atomlist index {}", idx);
        return 0;
    }

    l->data[idx] = *a;
    return 1;
}

void cpd_atomlist_append_float(t_cpd_atomlist* l, float f)
{
    if (!l) {
        console()->error("cpd_atomlist_append_float: NULL argument");
        return;
    }

    t_atom a;
    SETFLOAT(&a, f);
    l->data.push_back(a);
}

void cpd_atomlist_append_symbol(t_cpd_atomlist* l, const char* s)
{
    if (!l) {
        console()->error("cpd_atomlist_append_float: NULL argument");
        return;
    }

    t_atom a;
    SETSYMBOL(&a, gensym(s));
    l->data.push_back(a);
}

float cpd_atomlist_float_at(t_cpd_atomlist* l, size_t idx)
{
    if (!l) {
        console()->error("cpd_atomlist_append_float: NULL argument");
        return 0;
    }

    if (idx >= l->data.size()) {
        console()->error("cpd_atomlist_set_atom: invalid atomlist index {}", idx);
        return 0;
    }

    return atom_getfloat(&l->data[idx]);
}
