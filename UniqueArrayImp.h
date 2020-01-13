#ifndef EX3_UNIQUEARRAYIMP_H

#include <iostream>


using std::cout;
//constructor
template <class Element,class Compare>
UniqueArray<Element,Compare>::UniqueArray(unsigned int size):
    size(size), arr(new Element*[size]) {
        for (unsigned int i = 0; i < size; ++i) {
            arr[i] = nullptr;
    }
}

//copy constructor
template <class Element,class Compare>
UniqueArray<Element,Compare>::UniqueArray(const UniqueArray& other):
    size(other.size), arr(new Element*[other.size]) {
    for (int i = 0; i < size; i++) {

        if (other.arr[i] != nullptr) {
            arr[i] = new Element(*other.arr[i]);
        }
        else {
            arr[i] = nullptr;
        }
    }
}
//destructor
template <class Element,class Compare>
UniqueArray<Element,Compare>::~UniqueArray() {

    for (int i = 0; i < size; ++i) {

        if (arr[i] != nullptr){
            delete arr[i];
            arr[i] = nullptr;
        }
    }
    delete[] arr;
}

template <class Element,class Compare>
bool UniqueArray<Element,Compare>::getIndex(const Element& element, unsigned int& index) const{
    Compare compFunc;
//    if (compFunc(element, NULL)) { // or ==
//        return false;
//    }
    for (int i = 0; i<size; i++){
        if (arr[i] != nullptr && compFunc(element, *arr[i])){
            index = i;
            return true;
        }
    }
    return false;
}

template <class Element,class Compare>
unsigned int UniqueArray<Element,Compare>::find_first_empty() {
    for (int i=0; i<size; i++){
        if (arr[i] == nullptr){
            return i;
        }
    }
    // if we got here so full and need need to throw error
    throw UniqueArrayIsFullException{};
}

template <class Element,class Compare>
unsigned int UniqueArray<Element,Compare>::insert(const Element& element){
    unsigned int i;
    if (getIndex(element, i)){
        return i;
    }
    unsigned int j = find_first_empty();
    arr[j] = new Element(element);
    return j;
}

template <class Element,class Compare>
const Element* UniqueArray<Element,Compare>::operator[] (const Element& element) const { // CONST on an copy???
//    Compare compFunc;
//    if (compFunc(element, NULL)) { // or ==
//        return nullptr;
//    }
    unsigned int i = 0;
    if(getIndex(element, i)){
        return arr[i];
    }
    return nullptr;
}

template <class Element,class Compare>
Element* UniqueArray<Element,Compare>::get_ptr_to_elem_for_index (unsigned int i) const{
    if (i>=size){
        return nullptr;
    }
    return arr[i];
}


template <class Element,class Compare>
bool UniqueArray<Element,Compare>::remove(const Element& element){
//    Compare compFunc;
//    if (compFunc(element, NULL)) { // or == ???
//        return false;
//    }
    unsigned int i = 0;
    if(getIndex(element, i)){
        delete arr[i];
        arr[i] = nullptr;
        return true;
    }
    return false;
}

template <class Element,class Compare>
unsigned int UniqueArray<Element,Compare>::getCount() const{
    unsigned int counter = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] != nullptr){
            counter++;
        }
    }
    return counter;
}

template <class Element,class Compare>
unsigned int UniqueArray<Element,Compare>::getSize() const{
    return size;
}


template <class Element,class Compare>
UniqueArray<Element,Compare> UniqueArray<Element,Compare>::filter(const Filter& f) const {
    UniqueArray ua = UniqueArray(size);
    for (int i = 0; i < size ; ++i) {
        if (arr[i] != nullptr && (f(*(arr[i])))){
            ua.arr[i] = new Element(*(arr[i]));
        } else{
            ua.arr[i] = nullptr;
        }
    }
    return ua;
}


template <class Element,class Compare>
void UniqueArray<Element,Compare>::printTest(){
    for (int i = 0; i < size; ++i) {
        cout << "[" << i << "]: ";
        if (arr[i] == nullptr) {
            cout << "nullptr, ";
        }
        else {
            cout << *arr[i] << ", ";
        }
    }
    cout << std::endl;
}


            #define EX3_UNIQUEARRAYIMP_H
#endif //EX3_UNIQUEARRAYIMP_H
