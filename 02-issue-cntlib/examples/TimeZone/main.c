#include <stdio.h>
#include <cntlib.h>
#include <assert.h>
#include <stdlib.h>

typedef struct CLASS_TIMEZONE_T
{
    objcnt_t hours, minutes, seconds;
} classtzone_t;

typedef classtzone_t* objtzone_t;

cntany_t tzone_sec_step(cntany_t p, ...)
{
    objcnt_t this = (objcnt_t)p;

    cntint_t sec, min, hours;

    sec = cntvalue(this);
    min = cntvalue(this->parent);
    hours = cntvalue(this->parent->parent);

    printf("time %ld:%ld:%ld\n", hours, min, sec);

    return NULL;
}

cntany_t tzone_program_exit(cntany_t p, ...)
{
    objcnt_t this = (objcnt_t)p;

    cntev_disable(this);
    cntev_disable(this->child);
    cntev_disable(this->child->child);

    return NULL;
}

static objtzone_t tzone_cnst(void)
{
    objtzone_t this = (objtzone_t)malloc(sizeof(classtzone_t));

    assert(!(this == NULL));

    this->hours = cntcnst(CNT_OBJECT | CNT_LIMITATION | (CNT_CHILD_DEP));
    this->minutes = cntcnst(CNT_OBJECT | CNT_LIMITATION | (CNT_PARENT_INF | CNT_CHILD_DEP));
    this->seconds = cntcnst(CNT_OBJECT | CNT_LIMITATION | (CNT_PARENT_INF));

    assert(!(this->hours == NULL || this->minutes == NULL || this->seconds == NULL));

    cntinit(this->hours, 1, 24);
    cntinit(this->minutes, 1, 60);
    cntinit(this->seconds, 1, 60);

    assert(!(cntlink(this->hours, (CNT_ROOT | CNT_PARENT_CHILD), this->minutes) == CNT_ERROR));
    assert(!(cntlink(this->minutes, (CNT_ROOT | CNT_PARENT_CHILD), this->seconds) == CNT_ERROR));

    cntev_overflow(this->hours, tzone_program_exit);
    cntev_step(this->seconds, tzone_sec_step);

    cntev_enable(this->hours);
    cntev_enable(this->seconds);

    return this;
}

static void tzone_dstr(objtzone_t this)
{
    if (!this) return;

    cntdstr(this->hours);
    cntdstr(this->minutes);
    cntdstr(this->seconds);

    free(this);
}

int main()
{
    objtzone_t Moscow = tzone_cnst();
    objtzone_t Tokyo = tzone_cnst();
    objtzone_t London = tzone_cnst();
    objtzone_t New_York = tzone_cnst();

    cntrun(Moscow->seconds);
    cntrun(Tokyo->seconds);
    cntrun(London->seconds);
    cntrun(New_York->seconds);

    tzone_dstr(Moscow);

    return 0;
}
