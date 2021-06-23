
#include <criterion/criterion.h>

#include "../../src/ProgramOptionParser.h"
#include "../../src/ProgramOption.h"
#include "../../src/ProgramOptionValue.h"




Test(ProgramOptionParser, retrieving_option_returns_null_when_not_found) {
    // given a new parser
    ProgramOptionParser * parser = _ProgramOptionParser->new();
    
    // when retrieving a non-existing option
    ProgramOption const * storedOption = _ProgramOptionParser->get(parser, "option not found");

    // then no option should be returned
    cr_assert_null(
        storedOption,
        "Expected the parser to return no option, got one"
    );
}


Test(ProgramOptionParser, stores_and_retrieves_option_by_label) {
    // given a new parser
    ProgramOptionParser * parser = _ProgramOptionParser->new();
    ProgramOption const * storedOption;

    // when registering a new option and retrieving it back
    _ProgramOptionParser->store(
        parser,
        "version number",
        "v",
        "version",
        0
    );
    storedOption = _ProgramOptionParser->get(parser, "version number");

    // then the stored option should be returned
    cr_assert_not_null(
        storedOption,
        "Expected to retrieve the stored option, got null"
    );
}


Test(ProgramOptionParser, parses_short_option_which_doesnt_expect_value) {
    // given a parser with options stored inside and some program arguments
    ProgramOptionParser * parser = _ProgramOptionParser->new();
    _ProgramOptionParser->store(parser, "do it recursively", "r", "recursive", 0);
    char * programArguments[] = { "./chown", "-r", "some user", "some directory", "another directory" };

    // when parsing the program arguments
    _ProgramOptionParser->parse(parser, programArguments, 5);

    // then the stored option should be activated
    ProgramOption const * storedOption = _ProgramOptionParser->get(parser, "do it recursively");
    cr_assert_eq(
        _ProgramOption->isActivated(storedOption),
        1,
        "Expected the parser to activate the stored option"
    );
}


Test(ProgramOptionParser, parses_short_option_which_expects_value) {
    // given a parser with options stored inside and some program arguments
    ProgramOptionParser * parser = _ProgramOptionParser->new();
    _ProgramOptionParser->store(parser, "number of repetitions", "c", "count", 1);
    char * programArguments[] = { "./program", "foo", "-c", "2", "bar" };

    // when parsing the program arguments
    _ProgramOptionParser->parse(parser, programArguments, 5);

    // then the stored option should have appropriate value
    ProgramOption const * storedOption = _ProgramOptionParser->get(parser, "number of repetitions");
    ProgramOptionValue const * value = _ProgramOption->value(storedOption);
    
    cr_assert_eq(
        _ProgramOptionValue->asInteger(value),
        2,
        "Expected the parser to store the value 2, got %d", _ProgramOptionValue->asInteger(value)
    );
}


Test(ProgramOptionParser, parses_long_option_which_doesnt_expect_value) {
    // given a parser with options stored inside and some program arguments
    ProgramOptionParser * parser = _ProgramOptionParser->new();
    _ProgramOptionParser->store(parser, "do it recursively", "r", "recursive", 0);
    char * programArguments[] = { "./chown", "--recursive", "some user", "some directory", "another directory" };

    // when parsing the program arguments
    _ProgramOptionParser->parse(parser, programArguments, 5);

    // then the stored option should be activated
    ProgramOption const * storedOption = _ProgramOptionParser->get(parser, "do it recursively");

    cr_assert_eq(
        _ProgramOption->isActivated(storedOption),
        1,
        "Expected the parser to activate the stored option"
    );
}


Test(ProgramOptionParser, parses_long_option_which_expects_value) {
    // given a parser with options stored inside and some program arguments
    ProgramOptionParser * parser = _ProgramOptionParser->new();
    _ProgramOptionParser->store(parser, "number of repetitions", "c", "count", 1);
    char * programArguments[] = { "./program", "foo", "--count=3", "bar" };

    // when parsing the program arguments
    _ProgramOptionParser->parse(parser, programArguments, 4);

    // then the stored option should have appropriate value
    ProgramOption const * storedOption = _ProgramOptionParser->get(parser, "number of repetitions");
    ProgramOptionValue const * value = _ProgramOption->value(storedOption);
    
    cr_assert_eq(
        _ProgramOptionValue->asInteger(value),
        3,
        "Expected the parser to store the value 3, got %d", _ProgramOptionValue->asInteger(value)
    );
}
