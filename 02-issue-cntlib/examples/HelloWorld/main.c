#include <stdio.h>
#include <cntlib.h>
#include <assert.h>
#include <ctype.h>

#define PRINTER_MOD_LIST { printer_caps, printer_lower, printer_show, NULL }

cntany_t printer_show(cntany_t p, ...)
{
    objcnt_t this = (objcnt_t)p;

    putchar(*(char*)cntread(this));

    return NULL;
}

cntany_t printer_lower(cntany_t p, ...)
{
    objcnt_t this = (objcnt_t)p;

    putchar(tolower(*(char*)cntread(this)));

    return NULL;
}

cntany_t printer_caps(cntany_t p, ...)
{
    objcnt_t this = (objcnt_t)p;

    putchar(toupper(*(char*)cntread(this)));

    return NULL;
}

cntany_t printer_chstyle(cntany_t p, ...)
{
    objcnt_t this = (objcnt_t)p;

    static cntmethod_t mod_list[] = PRINTER_MOD_LIST;
    static cntmethod_t* methodptr = mod_list;

    cntev_disable(this);
    if (*methodptr != NULL)
    {
        cntev_step(this, *methodptr);
        cntev_enable(this);
    }

    methodptr += 1;

    return NULL;
}

objcnt_t printer_init(void)
{
    static char message[] = "Hello World!\n";
    static cntint_t message_sz = sizeof(message) / sizeof(*message);

    objcnt_t printer;
    printer = cntcnst(CNT_LOCATION | CNT_LIMITATION);
    assert(!(printer == NULL));

    cntinit(printer, 1, message, message_sz);

    cntev_overflow(printer, printer_chstyle);
    printer_chstyle(printer);

    return printer;
}

void printer_dstr(objcnt_t this)
{
    cntdstr(this);
}

int main()
{
    static objcnt_t printer;
    
    printer = printer_init();

    cntrun(printer);

    cntdstr(printer);

    return 0;
}
