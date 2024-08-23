#include <cstddef>
#include <iostream>
namespace atl{
       template <typename T>
       struct Forward_Node{
       Forward_Node():value(), next(){};
       Forward_Node(T arg):value(arg), next(){};
       
       bool operator<(Forward_Node<T> other){
           return this->value < other.value; 
       }
       
       bool operator==(Forward_Node other){
        if(this->next == other->next){
            return true;
        }
        return false;
       }
       bool operator!=(Forward_Node other){
        return !(this->oprator==(other));
       }
       Forward_Node<T>& operator=(Forward_Node<T>& other){
          this->value = other.value;
          this->next = other.next;
       }
        T value;
        Forward_Node<T>* next;
       };
    template <typename T, typename Alock>
    class Forwart_list_base{
    public:
        typedef size_t syze_type;
    public:
       Forwart_list_base<T,Alock>():_impl(){};
       Forwart_list_base<T,Alock>(size_t count){
            while(count--){
                Forward_Node<T>* tmp = Alock::allocate();
                Alock::construct(tmp);
                tmp->next = _impl._start;
                _impl._start = tmp;

            }
       }
        Forwart_list_base<T,Alock>(size_t count, T value){
            while(count--){
                Forward_Node<T>* tmp = Alock::allocate();
                Alock::construct(tmp, value);
                tmp->next = _impl._start;
                _impl._start = tmp;

            }
       };
       
       struct forward_list_implementation{
            typename Alock::pointer _start; 
       };

       forward_list_implementation _impl;
    };
}
