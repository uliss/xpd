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
    cpd_atomlist_free(lst_);
}

void PdArguments::operator=(const PdArguments& a)
{
    args_ = a.args_;
    cpd_atomlist_free(lst_);
    lst_ = cpd_atomlist_copy(a.lst_);
}

void PdArguments::parseString(const std::string& s)
{
}

void PdArguments::clear()
{
    Arguments::clear();
    cpd_atomlist_clear(lst_);
}

} // namespace xpd
