#pragma once

#include <cntlib/cntdef.h>

typedef struct STRUCTCNT_T {} classcnt_t;

typedef classcnt_t* objcnt_t;

objcnt_t cntcnst(cnttattr_t);
void cntdstr(objcnt_t);
void cntlink(objcnt_t, objcnt_t, cnttattr_t);

void cntinit(objcnt_t this, char* start, cntsize_t stepsz, cntsize_t limit);
void cntrst(objcnt_t);
void cntpp(objcnt_t);
void cntadd(objcnt_t, cntsize_t);
void cntidx(objcnt_t, cntsize_t);
void cntset(objcnt_t, objcnt_t);
void cntcpy(objcnt_t, objcnt_t);

cntsize_t cntvalue(objcnt_t);
void* cntaddr(objcnt_t);