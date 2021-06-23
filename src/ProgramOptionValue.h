
#ifndef PROGRAM_OPTION_VALUE_HEADER
#define PROGRAM_OPTION_VALUE_HEADER




/**
 * A CLI option's value
 */
typedef struct ProgramOptionValue ProgramOptionValue;




/**
 * ProgramOptionValue methods table
 */
typedef struct
{
    /**
     * Constructor
     * 
     * @return - a ProgramOptionValue instance if allocation succeeds, NULL otherwise
     */
    ProgramOptionValue * (* new)(void);

    /**
     * Destructor, sets the pointer to NULL
     * 
     * @param this - pointer to the instance to delete
     */
    void (* delete)(ProgramOptionValue ** this);

    /**
     * Stores a value
     * 
     * @param this - the instance to store value in
     */
    void (* store)(ProgramOptionValue * const this, char const * const valueString);

    /**
     * Returns the stored value as a string
     * 
     * @param this - the instance to get value from
     *
     * @return - the stored value as a string
     */
    char const * (* asString)(ProgramOptionValue const * const this);

    /**
     * Returns the stored value as a character
     * 
     * @param this - the instance to get value from
     *
     * @return - the stored value as a character, or -1 if no value is stored
     */
    char (* asCharacter)(ProgramOptionValue const * const this);

    /**
     * Returns the stored value as an integer
     * 
     * @param this - the instance to get value from
     *
     * @return - the stored value as a string
     */
    int (* asInteger)(ProgramOptionValue const * const this);

    /**
     * Returns the stored value as a float
     * 
     * @param this - the instance to get value from
     *
     * @return - the stored value as a string
     */
    double (* asFloat)(ProgramOptionValue const * const this);

} ProgramOptionValueMethods;




/**
 * ProgramOptionValue class methods table
 */
extern ProgramOptionValueMethods const * const _ProgramOptionValue;  




#endif /* PROGRAM_OPTION_VALUE_HEADER */

