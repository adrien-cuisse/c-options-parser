
#include <criterion/criterion.h>

#include "../../src/ProgramOptionValue.h"




Test(ProgramOptionValue, stores_string_value) {
    // given an option's value
    ProgramOptionValue * value = _ProgramOptionValue->new();

    // when storing a value inside and requesting it
    char * valueString = "foo";
    _ProgramOptionValue->store(value, valueString);
    char const * storedValueString = _ProgramOptionValue->asString(value);

    // then it should match the one used for creation
    cr_assert_str_eq(
        storedValueString,
        valueString,
        "Expected value to store the value [%s], got [%s]", valueString, storedValueString
    );
}


Test(ProgramOptionValue, stores_character_value) {
    // given an option's value
    ProgramOptionValue * value = _ProgramOptionValue->new();

    // when storing a value inside and requesting it
    char * valueString = "d";
    _ProgramOptionValue->store(value, valueString);
    char storedValueCharacter = _ProgramOptionValue->asCharacter(value);

    // then it should match the one used for creation
    cr_assert_eq(
        storedValueCharacter,
        'd',
        "Expected value to store the value [%s], got [%c]", valueString, storedValueCharacter
    );
}


Test(ProgramOptionValue, stores_integer_value) {
    // given an option's value
    ProgramOptionValue * value = _ProgramOptionValue->new();

    // when storing a value inside and requesting it
    char * valueString = "42";
    _ProgramOptionValue->store(value, valueString);
    int storedValueInteger = _ProgramOptionValue->asInteger(value);

    // then it should match the one used for creation
    cr_assert_eq(
        storedValueInteger,
        42,
        "Expected value to store the value [%s], got [%c]", valueString, storedValueInteger
    );
}


Test(ProgramOptionValue, stores_float_value) {
    // given an option's value
    ProgramOptionValue * value = _ProgramOptionValue->new();

    // when storing a value inside and requesting it
    char * valueString = "42.84";
    _ProgramOptionValue->store(value, valueString);
    double storedValueFloat = _ProgramOptionValue->asFloat(value);

    // then it should match the one used for creation
    cr_assert_eq(
        storedValueFloat,
        42.84,
        "Expected value to store the value [%s], got [%c]", valueString, storedValueFloat
    );
}

// TODO stores_integer_value
// TODO stores_float_value
