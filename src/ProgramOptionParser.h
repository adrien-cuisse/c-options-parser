
#ifndef PROGRAM_OPTION_PARSER_HEADER
#define PROGRAM_OPTION_PARSER_HEADER

#include "ProgramOption.h"




/**
 * A CLI options parser
 */
typedef struct ProgramOptionParser ProgramOptionParser;




/**
 * ProgramOptionParser methods table
 */
typedef struct
{
    /**
     * Constructor
     * 
     * @return - a ProgramOptionParser instance if allocation succeeds, NULL otherwise
     */
    ProgramOptionParser * (* new)(void);

    /**
     * Destructor, sets the pointer to NULL
     * 
     * @param this - pointer to the instance to delete
     */
    void (* delete)(ProgramOptionParser ** this);

    /**
     * Register a new option in the parser
     * 
     * @param this - the parser to store the option in
     * @param optionLabel - label for the option, will be used to retrieve it back
     * @param shortName - the short name of the option, @see ProgramOption
     * @param longName - the long name of the option, @see ProgramOption
     * @param expectsValue - whether or not the option expects a value (eg., '-c 1', '--count=1')
     */ 
    void (* store)(
        ProgramOptionParser * const this,
        char * const optionLabel,
        char const * const shortName,
        char const * const longName,
        int expectsValue
    );

    /**
     * Retrieves an option from the parser
     * 
     * @param this - the parser to retrieve option from
     * @param optionLabel - the label of the option to retrieve
     * 
     * @return - the requested option, or null if not found
     */
    ProgramOption const * (* get)(
        ProgramOptionParser const * const this,
        char const * const optionLabel
    );

    /**
     * Parses the arguments of the program and updates options stored in the parser
     * 
     * @param this - the parser containing the options to update
     * @param programArguments - arguments of the program to find options in
     * @param argumentsCount - number of arguments in the arguments array
     */
    void (* parse)(
        ProgramOptionParser const * const this,
        char * programArguments[],
        unsigned int argumentsCount
    );

} ProgramOptionParserMethods;




/**
 * ProgramOptionParser class methods table
 */
extern ProgramOptionParserMethods const * const _ProgramOptionParser;  




#endif /* PROGRAM_OPTION_PARSER_HEADER */
