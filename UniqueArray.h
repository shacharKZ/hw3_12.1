#ifndef MTMPARKINGLOT_UNIQUEARRAY_H
#define MTMPARKINGLOT_UNIQUEARRAY_H

#include <iostream>

/**
* @brief A generic unique array (like a set based on array)
*
*/
template <class Element, class Compare = std::equal_to<Element>>
class UniqueArray {
    unsigned int size; // the amount of object the array can hold
    Element** arr; // pointer-arr hold the elements

    /**
     * @brief helps to assign elements into arr
     *
     * @throw UniqueArrayIsFullException in case of full arr
     * @return returns the index of the first empty cell inside arr
     */
    unsigned int find_first_empty();

public:
    explicit UniqueArray(unsigned int size);
    UniqueArray(const UniqueArray& other);
    ~UniqueArray();
    UniqueArray& operator=(const UniqueArray&) = delete;
    unsigned int insert(const Element& element);
    bool getIndex(const Element& element, unsigned int& index) const;
    const Element* operator[] (const Element& element) const;

    /**
     * @brief return the ptr to the object in i-cell inside arr
     *
     * @pram i index to i-cell inside arr
     * @return returns pointer to the element in the i cell
     * i case i is out of index for arr size return nullptr
     */
    Element* get_ptr_to_elem_for_index (unsigned int i) const;

    bool remove(const Element& element);
    unsigned int getCount() const;
    unsigned int getSize() const;

    class Filter {
    public:
        virtual bool operator() (const Element&) const = 0;
    };
    UniqueArray filter(const Filter& f) const;
    class UniqueArrayIsFullException{};

    void printTest();
};
#include "UniqueArrayImp.h"


#endif //MTMPARKINGLOT_UNIQUEARRAY_H
