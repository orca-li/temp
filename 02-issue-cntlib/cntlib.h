#pragma once

#include <cntlib/cntdef.h>

typedef cntany_t (* const cntmethod_t)(cntany_t, ...);
typedef struct STRUCTCNT_T {
    struct STRUCTCNT_T* const parent;
    struct STRUCTCNT_T* const child;

    cntmethod_t start;
    cntmethod_t step;
    cntmethod_t mark;
    cntmethod_t overflow;
    cntmethod_t reset;
    cntmethod_t stop;
} classcnt_t;

typedef classcnt_t* objcnt_t;

objcnt_t cntcnst(cntattr_t);
void cntdstr(objcnt_t);
void cntinit(objcnt_t, cntint_t, ...);

cntstatus_t cntlink(objcnt_t, cntattr_t, objcnt_t);

void cntpp(objcnt_t);
void cntrun(objcnt_t);
void cntrst(objcnt_t);

void cntev_enable(objcnt_t);
void cntev_disable(objcnt_t);

void cntev_start(objcnt_t, cntmethod_t);
void cntev_step(objcnt_t, cntmethod_t);
void cntev_overflow(objcnt_t, cntmethod_t);
void cntev_reset(objcnt_t, cntmethod_t);
void cntev_stop(objcnt_t, cntmethod_t);

cntint_t cntvalue(objcnt_t);
cntptr_t cntread(objcnt_t);