
#include <signal.h>
#include <criterion/criterion.h>

#include "../../src/List.h"




Test(List, adding_on_null_list_returns_the_element) {
    // given a linked list
    List * list = _List->new();
    List * nextElement = _List->nextElement(list);

    // when adding a new element
    _List->add(& list, "foo");
    
    // then the address of the next element should have changed
    cr_assert_neq(
        list,
        nextElement,
        "Expected the address of the list to change"
    );
}


Test(List, adding_an_element_add_it_in_the_list) {
    // given a linked list with 1 only item
    List * firstElement = _List->new();
    List * secondElementBeforeAdd;
    _List->add(& firstElement, "foo");
    secondElementBeforeAdd = _List->nextElement(firstElement);
    
    // when adding another element
    _List->add(& firstElement, "bar");
    
    // then the address of the next element should have changed
    cr_assert_neq(
        _List->nextElement(firstElement),
        secondElementBeforeAdd,
        "Expected the address of the list to change"
    );
}


Test(List, returns_stored_data) {
    // given a linked list element
    List * element = _List->new();
    _List->add(& element, "foo");

    // when accessing the stored data
    char const * storedData = _List->data(element);

    // then it should match the stored value
    cr_assert_str_eq(
        storedData,
        "foo",
        "Expected the element to contain the value 'foo', got %s", storedData
    );
}


Test(List, deletes_further_elements_in_the_list, .signal = SIGSEGV) {
    // given a list with 2 elements
    List * firstElement = _List->new();
    List * secondElement;
    _List->add(& firstElement, "first element");
    _List->add(& firstElement, "second element");
    secondElement = _List->nextElement(firstElement);

    // when deleting from the first element
    _List->delete(& firstElement);

    // then the second element should be deleted too
    _List->add(& secondElement, "should raise a SIGSEGV");
}
