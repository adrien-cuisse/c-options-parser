
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ProgramOptionValue.h"
#include "Class.h"




struct ProgramOptionValue
{
    char const * valueString;
};




static ProgramOptionValue * new(void)
{
    ProgramOptionValue * this;

    this = Class->new("ProgramOptionValue", sizeof(* this));

    if (this != (void *)0) {
        this->valueString = (void *)0;
    }

    return this;
}


static void delete(ProgramOptionValue ** this)
{
    Class->delete((void **) this);
}


static void store(ProgramOptionValue * const this, char const * const valueString)
{
    if (this != (void *)0) {
        this->valueString = valueString;
    }
}


static char const * asString(ProgramOptionValue const * const this)
{
    if (this == (void *)0) {
        return (void *)0;
    }

    return this->valueString;
}


static char asCharacter(ProgramOptionValue const * const this)
{
    if (this->valueString != (void *)0) {
        return this->valueString[0];
    }

    return -1;
}


static int asInteger(ProgramOptionValue const * const this)
{
    if (this->valueString != (void *)0) {
        return atoi(this->valueString);
    }

    return -1;
}


static double asFloat(ProgramOptionValue const * const this)
{
    if (this->valueString != (void *)0) {
        return atof(this->valueString);
    }

    return -1;
}




/**
 * Init ProgramOptionValue methods table
 */
static ProgramOptionValueMethods methods = {
    new,
    delete,
    store,
    asString,
    asCharacter,
    asInteger,
    asFloat
};
ProgramOptionValueMethods const * const _ProgramOptionValue = & methods;
