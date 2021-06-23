
#include <stdio.h>
#include <stdlib.h>

#include "Class.h"




static void * Class_allocate(char const * className, unsigned int blockSize)
{
    void * this = calloc(1, blockSize);

    if (this == NULL) {
        if (className == NULL) {
            className = "[Unknown]";
        } 

        fprintf(stderr, "Memory allocation failed for class %s\n", className);
    }

    return this;
}


static void Class_deallocate(void ** this)
{
    if ((this == NULL) || (* this == NULL)) {
        return;
    }

    free(* this);
    * this = NULL;
}




/**
 * Init Class methods table
 */
static ClassMethods methods = {
    Class_allocate,
    Class_deallocate
};
ClassMethods const * const Class = & methods;
