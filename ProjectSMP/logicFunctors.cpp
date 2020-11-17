#ifndef def
   #include "def.h"
#endif

class land
{
public:
    SMP_word operator() (const SMP_word* x1, const SMP_word* x2) { return *x1 & *x2; }
};
class lxor
{
public:
    SMP_word operator() (const SMP_word* x1, const SMP_word* x2) { return (~(*x1) & *x2) | (~(*x2) & *x1); }
};
class lors
{
public:
    SMP_word operator() (const SMP_word* x1, const SMP_word* x2) { return *x1 | *x2; }
};
class ladd
{
public:
    SMP_word operator() (const SMP_word* x1, const SMP_word* x2) { return *x1 + *x2; }
};
class lsbc
{
public:
    SMP_word operator() (const SMP_word* x1, const SMP_word* x2) { return *x1 | *x2; }
};
class lror
{
public:
    SMP_word operator() (const SMP_word* x1, const SMP_word* x2) 
    {
        SMP_word temp = *x1;
        SMP_word res = *x1;
        res = res << *x2;
        temp = temp >> (sizeof(SMP_word) - *x2);
        return res & temp;
    }
};


