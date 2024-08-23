#include <iostream>
namespace atl{

template <typename T>
class Alocator{
public:
    using pointer = T*;
   
    static pointer allocate(size_t size = 1){
        pointer newPlace = (pointer)malloc(size * sizeof(T));
        if(newPlace == NULL){
            throw std::bad_alloc();
        }
        return newPlace;
    }
    static void dealocate(pointer addres, int size = 0){
        for(int i = 0; i < size; ++i){
            destroy(addres + i);
        }
        free(addres);
    }
    static void destroy(pointer addres){
       addres->~T();   
    }
    static void construct(void* ptr){
        new(ptr)T();
    } 
    static void construct(pointer ptr, T other){
        new(ptr)T(other);
    } 

};
}