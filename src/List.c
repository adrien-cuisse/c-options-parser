
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Class.h"




struct List
{
    /**
     * The short name of the option (eg., "h")
     */
    void * data;

    /**
     * The long name of the option (eg., "help")
     */
    List * nextElement;
};




/**
 * Creates a list-element
 * 
 * @param data - the data to store in the element
 * 
 * @return - the created element
 */ 
static List * __createElement(void * data);




static List * new(void)
{
    return (void *)0;
}


static void delete(List ** this)
{
    if (((* this) != (void *)0) && ((* this)->nextElement != (void *)0)) {
        _List->delete(& (* this)->nextElement);
    }

    Class->delete((void **) this);
}


static void add(List ** this, void * data)
{
    if (this == (void *)0) {
        return;
    } else if ((* this) == (void *)0) {
        * this = __createElement(data);
    } else if ((* this)->nextElement != (void *)0) {
        _List->add(& (* this)->nextElement, data);
    } else {
        (* this)->nextElement = __createElement(data);
    }
}


static List * nextElement(List const * const this)
{
    if (this == (void *) 0) {
        return (void *)0;
    }

    return this->nextElement;
}


static void * data(List const * const this)
{
    if (this == (void *)0) {
        return (void *)0;
    }

    return this->data;
}




static List * __createElement(void * data)
{
    List * this = Class->new("List", sizeof(* this));

    if (this != (void *) 0) {
        this->data = data;
    }

    return this;
}




/**
 * Init List methods table
 */
static ListMethods methods = {
    new,
    delete,
    add,
    nextElement,
    data
};
ListMethods const * const _List = & methods;
