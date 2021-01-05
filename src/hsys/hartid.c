#include <hsys.h>
#include "fns.h"

unsigned long
hartid(void)
{
    return llhartid();
}