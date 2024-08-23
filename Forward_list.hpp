#include "Forward_list_base.hpp"
#include "allocator.hpp"
namespace atl{
    
template <typename T>
    class Iterator{ 
    typedef T& referance;
    public:
        Iterator():node(){};
        Iterator(atl::Forward_Node<T>* ptr): node(ptr){};

        Iterator& operator++(int){
            this->node = this->node->next;
            return *this;
        }
        Iterator operator++(){
            Iterator tmp = *this;
            this->node = this->node->next;
            return tmp;
        }
        
        referance operator*(){
            return this->node->value; 
        }
        referance operator->(){
            return this->node->value;
        }
        bool operator==(Iterator& other){
            return this->node == other.node;
        }
        bool operator!=(Iterator& other){
            return !this->operator==(other);
        }

        bool operator<(Iterator& other){
            return this->node < other.node;
        }
    private:
        atl::Forward_Node<T>* node;     
    };

    template <typename T, typename Alock = atl::Alocator<atl::Forward_Node<T>>, typename iter = Iterator<T>>
    class Forward_list:public atl::Forwart_list_base<T,Alock>{
    public:
        typedef size_t size_type;
        typedef iter Iterator;
        typedef atl::Forward_Node<T> Node;
    
        Forward_list(){};
        Forward_list(size_type count):atl::Forwart_list_base<T,Alock>(count){};
        Forward_list(size_type count, T value):atl::Forwart_list_base<T,Alock>(count, value){};
    public:
        void push_front(T value){
           Node* newNode = Alock::allocate();
           Alock::construct(newNode, value);

           newNode->next = this->_impl._start;
           this->_impl._start = newNode;
        }
        void pop_front(){
            Node* tmp = this->_impl._start->next;
            Alock::destroy(this->_impl._start);
            Alock::dealocate(this->_impl._start);
            this->_impl._start =  tmp;
        }
        bool empty(){
            return this->_impl._start == nullptr;
        }
        void swap(atl::Forward_list<T> other){
            Node* tmp = this->_impl._start;
            this->_impl._start = other._impl._start;
            other._impl._start = tmp;
        }
        void revers(){
            this->_impl._start = _revers(this->_impl._start);
        }
        Node* _revers(Node* head){
            if(!head || !head->next){
                return head;
            }
            Node* newHead = _revers(head->next);
            head->next->next = head;
            head->next = nullptr;
            return newHead;
        }
        void print(){
            auto start = beagin();
            auto finish = end();
            while(start++ != finish){
                std::cout << *start << " ";
            }
            std::cout << std::endl;
        }
        void sort(){
            auto _end = end();
            

            for(auto i = beagin(); beagin() != _end; ++i){
                for(auto j = i; j != _end; ++j){
                auto fast = j;
                j++;
                    if(j < fast){
                        std::cout << "swap" << std::endl;
                        print();
                        Iterator tmp = j;
                        j = fast;
                        fast = tmp;
                    }
                }
            }
        }
        Iterator beagin(){
            return Iterator(this->_impl._start);
        }
        Iterator end(){
            return Iterator(0);
        }
};

}