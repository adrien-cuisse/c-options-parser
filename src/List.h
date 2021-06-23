
#ifndef LIST_HEADER
#define LIST_HEADER




/**
 * A simply linked list
 */
typedef struct List List;





/**
 * List methods table
 */
typedef struct
{
    /**
     * Constructor
     * 
     * @return - a list instance if the allocation succeeds, NULL otherwise
     */
    List * (* new)(void);

    /**
     * Destructor, sets the pointer to NULL
     * 
     * @param this - pointer to the instance to delete
     */
    void (* delete)(List ** this);

    /**
     * Adds an element to the list
     * 
     * @param this - pointer to the instance to add an element in
     * @param data - pointer to the data to add
     */
    void (* add)(List ** this, void * data);

    /**
     * Returns the next element in the list
     * 
     * @param this - the instance to get the next element from
     *
     * @return - the next element
     */
    List * (* nextElement)(List const * const this);

    /**
     * Returns the data stored in the element
     * 
     * @param this - the element to get stored data for
     * 
     * @return - the data stored in the element, or NULL if the element is null
     */
    void * (* data)(List const * const this);

} ListMethods;




/**
 * List class methods table
 */
extern ListMethods const * const _List; 




#endif /* LIST_HEADER */
