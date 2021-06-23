
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ProgramOptionParser.h"
#include "ProgramOption.h"
#include "List.h"
#include "Class.h"




struct ProgramOptionParser
{
    /**
     * The list of stored options
     */
    List * options;

    /**
     * The list of options label
     */
    List * labels;
};




/**
 * Parses a short option
 * 
 * @param option - the option to store value / activation in
 * @param programArguments - the list of program arguments
 * @param argumentsCount - the number of arguments in the previous array
 * @param argumentPosition - the position in the array of the argument to parse
 * 
 * @return
 *  - 2 on success and value extracted from next argument,
 *  - 1 on activation success, 
 *  - 0 on failure: no more argument to extract value, argument doesn't start with '-', name mismatch
 */
static int __parseShortOption(
    ProgramOption * const option,
    char * programArguments[],
    unsigned int argumentsCount,
    unsigned int argumentPosition
);


/**
 * Parses a short option
 * 
 * @param option - the option to store value / activation in
 * @param programArguments - the list of program arguments
 * @param argumentsCount - the number of arguments in the previous array
 * @param argumentPosition - the position in the array of the argument to parse
 * 
 * @return 
 *  - 2 on success and value extracted
 *  - 1 on activation success,
 *  - 0 on failure: no more argument to extract value, argument doesn't start with '-', name mismatch
 */
static int __parseLongOption(
    ProgramOption * const option,
    char * programArguments[],
    unsigned int argumentsCount,
    unsigned int argumentPosition
);




static ProgramOptionParser * new(void)
{
    ProgramOptionParser * this = Class->new("ProgramOptionParser", sizeof(* this));

    if (this != (void *)0) {
        this->options = _List->new();
        this->labels = _List->new();
    }

    return this;
}


static void delete(ProgramOptionParser ** this)
{
    if ((* this) != (void *)0) {
        if ((* this)->options != (void *)0) {
            _List->delete(& (* this)->options);
        }

        if ((* this)->labels != (void *)0) {
            _List->delete(& (* this)->labels);
        }
    }

    Class->delete((void **) this);
}


static void store(
    ProgramOptionParser * const this,
    char * const optionLabel,
    char const * const shortName,
    char const * const longName,
    int expectsValue
) {
    if (this == (void *)0) {
        return;
    }

    _List->add(& this->labels, optionLabel);

    _List->add(& this->options, _ProgramOption->new(
        shortName,
        longName,
        expectsValue
    ));
}


static ProgramOption const * get(ProgramOptionParser const * const this, char const * const optionLabel)
{
    List * currentLabelElement;
    List * currentOptionElement;
    unsigned int labelFound = 0;

    if (this == (void *)0) {
        return (void *)0;
    }

    currentLabelElement = this->labels;
    currentOptionElement = this->options;

    while ((currentLabelElement != (void *)0) && (currentOptionElement != (void *)0)) {

        if (strcmp((char *) _List->data(currentLabelElement), optionLabel) == 0) {
            labelFound = 1;
            break;
        }

        currentLabelElement = _List->nextElement(currentLabelElement);
        currentOptionElement = _List->nextElement(currentOptionElement);
    }

    if (labelFound == 0) {
        return (void *)0;
    }

    return _List->data(currentOptionElement);
}


static void parse(
    ProgramOptionParser const * const this,
    char * programArguments[],
    unsigned int argumentsCount
) {
    unsigned int argumentIndex;
    List * currentOptionElement;
    ProgramOption * currentOption;

    currentOptionElement = this->options;
    while (currentOptionElement != (void *)0) {

        currentOption = _List->data(currentOptionElement);

        for (argumentIndex = 0; argumentIndex < argumentsCount; argumentIndex++) {
            
            if (__parseLongOption(currentOption, programArguments, argumentsCount, argumentIndex)) {
                /* nothing to do */
            } else if (__parseShortOption(currentOption, programArguments, argumentsCount, argumentIndex) == 2) {
                argumentIndex++; /* skip next argument, value extracted from it */
            }
        }

        currentOptionElement = _List->nextElement(currentOptionElement);
    }
}




static int __parseShortOption(
    ProgramOption * const option,
    char * programArguments[],
    unsigned int argumentsCount,
    unsigned int argumentPosition
) {
    char * optionShortName;
    char * argument = programArguments[argumentPosition];
    int optionExpectsValue;

    optionShortName = _ProgramOption->shortName(option);
    if (optionShortName == (void *)0) {
        return 0;
    }

    optionExpectsValue = _ProgramOption->expectsValue(option);

    if (strstr(argument, "-") != argument)  {
        return 0;
    } else if (strcmp(argument + 1, optionShortName) != 0) {
        return 0;
    } else if (optionExpectsValue) {
        if (argumentPosition < argumentsCount - 1) {
            _ProgramOption->store(option, programArguments[argumentPosition + 1]);
            return 2;
        }

        return 0;
    }

    _ProgramOption->activate(option);

    return 1;
}


static int __parseLongOption(
    ProgramOption * const option,
    char * programArguments[],
    unsigned int argumentsCount,
    unsigned int argumentPosition
) {
    char * optionLongName;
    char * argument = programArguments[argumentPosition];
    int optionExpectsValue;
    unsigned int optionLongNameLength;

    optionLongName = _ProgramOption->longName(option);
    if (optionLongName == (void *)0) {
        return 0;
    }

    optionLongNameLength = strlen(optionLongName);
    optionExpectsValue = _ProgramOption->expectsValue(option);

    if (strstr(argument, "--") != argument) {
        return 0;
    } else if (strstr(argument, optionLongName) != argument + 2) {
        return 0;
    } else if (optionExpectsValue) {
        if (argument[optionLongNameLength + 2] == '=') {
            _ProgramOption->store(option, argument + 2 + optionLongNameLength + 1);
            return 2;
        }

        printf(stderr, "Unrecognized format, expected to find '=' after --%s=\n", optionLongName);
        return 0;
    }

    _ProgramOption->activate(option);

    return 1;
}




/**
 * Init ProgramOptionParser methods table
 */
static ProgramOptionParserMethods methods = {
    new,
    delete,
    store,
    get,
    parse
};
ProgramOptionParserMethods const * const _ProgramOptionParser = & methods;
