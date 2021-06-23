
#ifndef PROGRAM_OPTION_HEADER
#define PROGRAM_OPTION_HEADER

#include "ProgramOptionValue.h"




/**
 * A CLI option
 */
typedef struct ProgramOption ProgramOption;




/**
 * ProgramOption methods table
 */
typedef struct
{
    /**
     * Constructor
     * 
     * @param shortName - the short name of the option
     * @param longName - the long name of the option
     * @param expectsValue - whether or not the option expects a value
     * 
     * @return - a ProgramOption instance if allocation succeeds, NULL otherwise
     */
    ProgramOption * (* new)(
        char const * const shortName,
        char const * const longName,
        int expectsValue
    );

    /**
     * Destructor, sets the pointer to NULL
     * 
     * @param this - pointer to the instance to delete
     */
    void (* delete)(ProgramOption ** this);

    /**
     * Returns the short name of the option
     * 
     * @param this - the instance to get short name for
     *
     * @return - the short name of the option
     */
    char const * (* shortName)(ProgramOption const * const this);

    /**
     * Returns the long name of the option
     * 
     * @param this - the instance to get long name for
     *
     * @return - the long name of the option
     */
    char const * (* longName)(ProgramOption const * const this);

    /**
     * Checks if the option expects a value to work
     * 
     * @param this - the instance to check for value expectation for
     * 
     * @return - 1 if the option expects a value, 0 otherwise
     */
    int (* expectsValue)(ProgramOption const * const this);

    /**
     * Stores a value in the option
     * 
     * @param this - the option to store a value in
     * @param valueString - the string-value to store
     */
    void (* store)(ProgramOption * const this, char const * const valueString);

    /**
     * Activates the option
     * 
     * @param this - the option to activate
     */
    void (* activate)(ProgramOption * const this);

    /**
     * Checks if the option is activated
     * 
     * @param this - the option to check activation for
     * 
     * @return -
     *  - 0 if the option is NULL, or not activated
     *  - 1 the option is activated
     */
    int (* isActivated)(ProgramOption const * const this);

    /**
     * Returns the value-object
     * 
     * @param this - the instance to get value for
     * 
     * @return - the value-object, or NULL if none is stored
     */
    ProgramOptionValue const * (* value)(ProgramOption const * const this);


} ProgramOptionMethods;




/**
 * ProgramOption class methods table
 */
extern ProgramOptionMethods const * const _ProgramOption;  




#endif /* PROGRAM_OPTION_HEADER */
