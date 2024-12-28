#include <stdlib.h>
#include <stdarg.h>
#include "cntlib.p"

#define if_null_return(_value) if (this == NULL) return _value
#define if_this_or_peer_null_return(_value) if (this == NULL || peer == NULL) return _value

objcnt_t cntcnst(cnttattr_t attr)
{
    objcnt_t this;
    this = (objcnt_t)malloc(sizeof(classcnt_t));

    if_null_return(NULL);

    this->parent = NULL;
    this->child = NULL;
    this->next = this;
    this->prev = this;
    this->attr = attr;

    return this;
}

void cntdstr(objcnt_t this)
{
    if_null_return();

    /* peer unlink */
    cntdstr(this->child);
    free(this);
}

void cntinit(objcnt_t this, char* start, cntsize_t stepsz, cntsize_t limit)
{
    if_null_return();

    this->reset = start;
    this->position = start;
    this->stepsz = stepsz;
    this->index = 0;
    this->limit = limit;
}

static void peeradd(objcnt_t head, objcnt_t tail, objcnt_t add)
{
    if (tail == NULL || head == NULL || add == NULL)   
    {
        return;
    }

    if (!(tail->next == NULL || tail->next == head))
    {
        peeradd(head, tail->next, add);
        return;
    }

    tail->next = add;
    add->prev = tail;
    add->next = head;
    head->prev = add;
}

void cntlink(objcnt_t this, objcnt_t peer, cnttattr_t type)
{
    if_this_or_peer_null_return();

    switch (type)
    {
    case CNT_PARENT_CHILD:
        this->child = peer;
        peer->parent = this;
        break;

    case CNT_CHILD_PARENT:
        this->parent = peer;
        peer->child = this;
        break;

    case CNT_PEER_TO_PEER:
        peeradd(this, this, peer);
        break;
    
    default:
        break;
    }
}

void cntrst(objcnt_t this)
{
    if_null_return();

    this->position = this->reset;
    this->index = 0;

    if (!CNT_CHECK_MASK(this->attr, CNT_OBJECT))
    {
        cntrst(this->child);
    }
}

void cntpp(objcnt_t this);
static void _cntpp(objcnt_t head, objcnt_t prev, objcnt_t peer);

static void _cntpptodo(objcnt_t this)
{
    if_null_return();

    this->index++;
    if (!CNT_CHECK_MASK(this->attr, CNT_OBJECT))
    {
        this->position += this->stepsz;
        cntrst(this->child);
    }

    if (this->index >= this->limit && this->limit != CNT_UNLIMIT)
    {
        cntpp(this->parent);
        cntrst(this);
    }
}

static void _cntpp(objcnt_t head, objcnt_t prev, objcnt_t peer)
{
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

void cntmm(objcnt_t this)
{
    if_null_return();

    this->position -= this->stepsz;
    this->index -= 1;

    if (!CNT_CHECK_MASK(this->attr, CNT_OBJECT))
    {
        cntrst(this->child);
    }

    if (this->index >= this->limit && this->limit != 0)
    {
        cntmm(this->parent);
        cntrst(this);
    }
}

void cntadd(objcnt_t this, long addend)
{
    if_null_return();

    if (addend > 0)
    {
        while (addend)
        {
            cntpp(this);
            addend--;
        }
    }

    if (addend < 0)
    {
        while (addend)
        {
            cntmm(this);
            addend++;
        }
    }
}

void cntidx(objcnt_t this, cntsize_t index)
{
    if_null_return();

    cntrst(this);
    cntadd(this, index);
}

void cntset(objcnt_t, objcnt_t);

cntsize_t cntvalue(objcnt_t this)
{
    if_null_return(0);

    return this->index;
}

void* cntread(objcnt_t this)
{
    if_null_return(NULL);

    return this->position;
}