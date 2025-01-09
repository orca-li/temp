#pragma once

#include "cntdef.h"

#define CNT_CHECK_MASK(_value, _mask) ((_value & _mask) == _mask)

typedef struct STRUCTCNT_T
{
    struct STRUCTCNT_T* parent;
    struct STRUCTCNT_T* child;
    struct STRUCTCNT_T* prev;
    struct STRUCTCNT_T* next;

    cntsize_t stepsz;
    cntsize_t index;
    cntsize_t limit;
    char* position;
    char* reset;

    cnttattr_t attr;
} classcnt_t;

typedef classcnt_t* objcnt_t;