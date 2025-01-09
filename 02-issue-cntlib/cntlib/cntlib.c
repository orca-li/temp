#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "cntlib.p"

#define if_null_return(_value) \
    if (this == NULL)          \
    return _value

#define CNT_RESET_BIT(_value, _bit) _value &= ~_bit
#define CNT_SET_BIT(_value, _bit) _value |= _bit;
#define CNT_EXCEPTION_MASK(_value, _attr) !CNT_CHECK_MASK(_value, _attr)

#define CNT_ALL_METHOD_NULL()  \
    do                         \
    {                          \
        this->start = NULL;    \
        this->step = NULL;     \
        this->mark = NULL;     \
        this->overflow = NULL; \
        this->reset = NULL;    \
        this->stop = NULL;     \
    } while (0)

objcnt_t cntcnst(cntattr_t attr)
{
    objcnt_t this;
    this = (objcnt_t)malloc(sizeof(classcnt_t));

    if_null_return(NULL);

    this->parent = NULL;
    this->child = NULL;
    this->next = this;
    this->prev = this;
    this->attr = attr;

    CNT_ALL_METHOD_NULL();

    return this;
}

void cntdstr(objcnt_t this)
{
    if_null_return();

    cntdstr(this->child);
    free(this);
}

void cntinit(objcnt_t this, cntint_t stepsz, ...)
{
    if_null_return();

    va_list args;
    va_start(args, stepsz);

    if (CNT_EXCEPTION_MASK(this->attr, CNT_OBJECT))
    {
        this->position = va_arg(args, char *);
        this->rstval = this->position;
    }

    if (CNT_CHECK_MASK(this->attr, CNT_LIMITATION))
    {
        this->limit = va_arg(args, cntint_t);
    }

    this->stepsz = stepsz;
    this->index = 0;

    va_end(args);
}

cntstatus_t cntlink(objcnt_t this, cntattr_t role, objcnt_t node)
{
    if (!this || !node) return CNT_ERROR;

    if (CNT_CHECK_MASK(role, CNT_PARENT_CHILD))
    {
        if (CNT_CHECK_MASK(role, CNT_ROOT))
        {
            this->child = (CNT_CHECK_MASK(this->attr, CNT_CHILD_INF)) ? node : NULL;
            node->parent = (CNT_CHECK_MASK(this->attr, CNT_CHILD_DEP)) ? this : node->parent;
            return CNT_SUCCESS;
        }
        
        if (CNT_CHECK_MASK(this->attr, CNT_CHILD_INF) && CNT_CHECK_MASK(node->attr, CNT_PARENT_DEP))
        {
            this->child = node;
            node->parent = this;
            return CNT_SUCCESS;
        }
        
        return CNT_ERROR;
    }

    if (CNT_CHECK_MASK(role, CNT_CHILD_PARENT))
    {
        if (CNT_CHECK_MASK(role, CNT_ROOT))
        {
            this->parent = (CNT_CHECK_MASK(this->attr, CNT_PARENT_DEP)) ? node : NULL;
            node->child = (CNT_CHECK_MASK(this->attr, CNT_PARENT_INF)) ? this : node->child;
            return CNT_SUCCESS;
        }

        if (CNT_CHECK_MASK(this->attr, CNT_PARENT_DEP) && CNT_CHECK_MASK(node->attr, CNT_PARENT_DEP))
        {
            this->parent = node;
            node->child = this;
            return CNT_SUCCESS;
        }

        return CNT_ERROR;
    }

    if (CNT_CHECK_MASK(role, CNT_PEER_TO_PEER))
    {
        return CNT_SUCCESS;
    }

    return CNT_ERROR;
}

void cntpp(objcnt_t this);
static void _cntpp(objcnt_t head, objcnt_t prev, objcnt_t peer);
static void check_event(objcnt_t this);
void cntrst(objcnt_t this);
static void _cntpptodo(objcnt_t this)
{
    if_null_return();

    if (CNT_CHECK_MASK(this->attr, CNT_EVENT))
    {
        check_event(this);
    }

    if (CNT_EXCEPTION_MASK(this->attr, CNT_OBJECT))
    {
        this->position += this->stepsz;
        cntrst(this->child);
    }

    this->index++;

    if (CNT_CHECK_MASK(this->attr, CNT_LIMITATION) && this->index >= this->limit)
    {
        if (this->overflow && CNT_CHECK_MASK(this->attr, CNT_EVENT))
        {
            this->overflow(this);
        }
        cntrst(this);
    }
}

static void _cntpp(objcnt_t head, objcnt_t prev, objcnt_t peer)
{
    if (head == NULL)
        return;

    if (peer == head)
    {
        _cntpptodo(head);
        return;
    }

    if (peer == NULL)
    {
        prev->next = head;
        head->prev = prev;
        _cntpptodo(head);
        return;
    }

    _cntpptodo(peer);
    _cntpp(head, peer, peer->next);
}

void cntpp(objcnt_t this)
{
    if_null_return();

    _cntpp(this, this, this->next);
}

void cntrun(objcnt_t this)
{
    if_null_return();

    if (this->start)
    {
        this->start(this);
    }

    while (CNT_CHECK_MASK(this->attr, CNT_EVENT))
    {
        cntpp(this);
    }

    if (this->stop)
    {
        this->stop(this);
    }
}

void cntrst(objcnt_t this)
{
    if_null_return();

    this->position = this->rstval;
    this->index = 0;

    if (!CNT_CHECK_MASK(this->attr, CNT_OBJECT))
    {
        cntrst(this->child);
    }

    if (CNT_CHECK_MASK(this->attr, CNT_EVENT) && this->reset)
    {
        this->reset(this);
    }
}

void cntev_enable(objcnt_t this)
{
    if_null_return();

    CNT_SET_BIT(this->attr, CNT_EVENT);
}

void cntev_disable(objcnt_t this)
{
    if_null_return();

    CNT_RESET_BIT(this->attr, CNT_EVENT);
}

static void check_event(objcnt_t this)
{
    if_null_return();

    if (CNT_EXCEPTION_MASK(this->attr, CNT_EVENT))
    {
        return;
    }

    if (this->step)
    {
        this->step(this);
    }
}

void cntev_start(objcnt_t this, cntmethod_t method)
{
    if_null_return();

    this->start = method;
}

void cntev_step(objcnt_t this, cntmethod_t method)
{
    if_null_return();

    this->step = method;
}

void cntev_overflow(objcnt_t this, cntmethod_t method)
{
    if_null_return();

    this->overflow = method;
}

void cntev_reset(objcnt_t this, cntmethod_t method)
{
    if_null_return();

    this->reset = method;
}

void cntev_stop(objcnt_t this, cntmethod_t method)
{
    if_null_return();

    this->stop = method;
}

cntint_t cntvalue(objcnt_t this)
{
    if_null_return(0);

    return this->index;
}

cntptr_t cntread(objcnt_t this)
{
    if_null_return(NULL);

    return this->position;
}