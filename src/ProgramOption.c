
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ProgramOption.h"
#include "Class.h"




struct ProgramOption
{
    /**
     * The short name of the option (eg., "h")
     */
    char const * shortName;

    /**
     * The long name of the option (eg., "help")
     */
    char const * longName;

    /**
     * Whether or not the option expects a value (eg., has the form [./binary -t file] or [./bninary --type=file])
     */
    int expectsValue;

    /**
     * The raw string that was used to create the token
     */
    int isActivated;

    /**
     * The value stored for the option, if it requires one
     */
    ProgramOptionValue * value;
};




static ProgramOption * new(
    char const * const shortName,
    char const * const longName,
    int expectsValue
) {
    ProgramOption * this;

    this = Class->new("ProgramOption", sizeof(* this));

    if (this != NULL) {
        this->shortName = shortName;
        this->longName = longName;
        this->expectsValue = expectsValue;
        this->isActivated = 0;
        this->value = NULL;
    }

    return this;
}


static void delete(ProgramOption ** this)
{
    Class->delete((void **) this);
}


static char const * shortName(ProgramOption const * const this)
{
    if (this == (void *)0) {
        return (void *)0;
    }

    return this->shortName;
}


static char const * longName(ProgramOption const * const this)
{
    if (this == (void *)0) {
        return (void *)0;
    }

    return this->longName;
}


static int expectsValue(ProgramOption const * const this)
{
    if (this == (void *)0) {
        return 0;
    }

    return this->expectsValue;
}


static void store(ProgramOption * const this, char const * const valueString)
{
    if (this->value == (void *)0) {
        this->value = _ProgramOptionValue->new();
    }

    _ProgramOptionValue->store(this->value, valueString);
}


static void activate(ProgramOption * const this)
{
    if (this != (void *)0) {
        this->isActivated = 1;
    }
}


static int isActivated(ProgramOption const * const this)
{
    if (this != (void *)0) {
        return this->isActivated;
    }

    return 0;
}


static ProgramOptionValue const * value(ProgramOption const * const this)
{
    if (this == (void *)0) {
        return (void *)0;
    } else if (this->expectsValue == 0) {
        return (void *)0;
    }

    return this->value;
}




/**
 * Init ProgramOption methods table
 */
static ProgramOptionMethods methods = {
    new,
    delete,
    shortName,
    longName,
    expectsValue,
    store,
    activate,
    isActivated,
    value
};
ProgramOptionMethods const * const _ProgramOption = & methods;
