#include "pd_arguments.h"

namespace xpd {

PdArguments::PdArguments()
    : lst_(cpd_atomlist_new(0))
{
}

PdArguments::PdArguments(const PdArguments& a)
    : Arguments(a)
    , lst_(cpd_atomlist_copy(a.lst_))
{
}

PdArguments::PdArguments(float v)
    : Arguments(v)
    , lst_(cpd_atomlist_new(1))
{
    cpd_atom_set_float(cpd_atomlist_at(lst_, 0), v);
}

PdArguments::PdArguments(const std::string& s)
    : Arguments(s)
    , lst_(cpd_atomlist_new(1))
{
    cpd_atom_set_symbol(cpd_atomlist_at(lst_, 0), s.c_str());
}

PdArguments::~PdArguments()
{
    free();
}

void PdArguments::operator=(const PdArguments& a)
{
    args_ = a.args_;
    cpd_atomlist_free(lst_);
    lst_ = cpd_atomlist_copy(a.lst_);
}

void PdArguments::parseString(const std::string& s)
{
    free();
    lst_ = cpd_atomlist_new_from_string(s.c_str());
    const size_t N = cpd_atomlist_size(lst_);

    for (size_t i = 0; i < N; i++) {
        auto a = cpd_atomlist_at(lst_, i);

        if (cpd_atom_is_float(a))
            args_.push_back(cpd_atom_float(a));

        if (cpd_atom_is_symbol(a))
            args_.push_back(std::string(cpd_atom_symbol(a)));
    }
}

void PdArguments::clear()
{
    args_.clear();
    cpd_atomlist_clear(lst_);
}

void PdArguments::free()
{
    args_.clear();
    cpd_atomlist_free(lst_);
    lst_ = 0;
}

} // namespace xpd
