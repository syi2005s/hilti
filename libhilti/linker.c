
// Weak versions of functions that are generated by the HILTI linker. These
// exist so that one can link JITing host applications against the library.
// However, these versions should never actually execute.

#include <stdio.h>
#include <stdlib.h>

#include "linker.h"

__attribute__((weak)) void __hlt_modules_init(void* ctx)
{
}

__attribute__((weak)) void __hlt_globals_init(void* ctx)
{
}

__attribute__((weak)) void __hlt_globals_dtor(void* ctx)
{
}

__attribute__((weak)) uint64_t __hlt_globals_size()
{
    return 0;
}
