#include "formula.h"

Formula::Formula(string s)
{
    str=s;
    e=strToTree(s, 0, s.length() - 1);
}

Formula::~Formula()
{
    if(e!=NULL) formuleDestroy(e);
}
