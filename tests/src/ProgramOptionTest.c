
#include <criterion/criterion.h>

#include "../../src/ProgramOption.h"




Test(ProgramOption, stores_short_name) {
    // given an option with a short name
    char * shortName = "h";
    ProgramOption * option = _ProgramOption->new(shortName, (void *)0, 0);

    // when requesting its short name
    char const * storedShortName = _ProgramOption->shortName(option);

    // then it should match the one used for creation
    cr_assert_str_eq(
        storedShortName,
        shortName,
        "Expected option to store the short name [%s], got [%s]", shortName, storedShortName
    );
}


Test(ProgramOption, stores_long_name) {
    // given an option with a long name
    char * longName = "help";
    ProgramOption * option = _ProgramOption->new((void *)0, longName, 0);

    // when requesting its long name
    char const * storedLongName = _ProgramOption->longName(option);

    // then it should match the one used for creation
    cr_assert_str_eq(
        storedLongName,
        longName,
        "Expected option to store the long name [%s], got [%s]", longName, storedLongName
    );
}


Test(ProgramOption, stores_value_expectation) {
    // given an option which expects a value
    int expectsValue = 1;
    ProgramOption * option = _ProgramOption->new((void *)0, (void *)0, expectsValue);

    // when requesting its expectation
    int storedValueExpectation = _ProgramOption->expectsValue(option);

    // then it should match the one used for creation
    cr_assert_eq(
        storedValueExpectation,
        expectsValue,
        "Expected option to store its value expectation"
    );
}


Test(ProgramOption, has_no_value_by_default) {
    // given an option
    ProgramOption * option = _ProgramOption->new((void *)0, (void *)0, 1);

    // when requesting its value
    ProgramOptionValue const * storedValue = _ProgramOption->value(option);
    
    // then there should be none
    cr_assert_null(
        storedValue,
        "Expected the option to contain no value-object, found one"
    );
}


Test(ProgramOption, stores_value) {
    // given an option
    ProgramOption * option = _ProgramOption->new((void *)0, (void *)0, 1);

    // when storing a value inside
    _ProgramOption->store(option, "foo");
    ProgramOptionValue const * storedValue = _ProgramOption->value(option);
    
    // then the returned value-object should exist
    cr_assert_not_null(
        storedValue,
        "Expected the option to store a value-object, found none"
    );
}


Test(ProgramOption, is_not_activated_by_default) {
    // given a new option
    ProgramOption * option = _ProgramOption->new(NULL, NULL, 0);

    // when checking its activity
    int isActivated = _ProgramOption->isActivated(option);

    // then it should be deactivated
    cr_assert_eq(
        isActivated,
        0,
        "Expected the option to be deactivated by default"
    );
}


Test(ProgramOption, goes_activated) {
    // given a new option
    ProgramOption * option = _ProgramOption->new(NULL, NULL, 0);
    int isActivated;

    // when activating it and checking its activity
    _ProgramOption->activate(option);
    isActivated = _ProgramOption->isActivated(option);

    // then it should be deactivated
    cr_assert_eq(
        isActivated,
        1,
        "Expected the option to be activated"
    );
}
