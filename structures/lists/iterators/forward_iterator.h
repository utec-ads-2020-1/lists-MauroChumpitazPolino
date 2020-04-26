#ifndef FORWARD_ITERATOR_H
#define FORWARD_ITERATOR_H

#include "../node.h"
#include <stdexcept>
// TODO: Implement all methods
template <typename T> 
class ForwardIterator {
    private:
        Node<T> *current;

    public:
        ForwardIterator(){
            this->current = nullptr;
        }
        
        ForwardIterator(Node<T>* listNode){
            this->current = listNode;
        }

        ForwardIterator<T> operator=(ForwardIterator<T> eqItr){
            if(this->current != eqItr.current){
                this->current = eqItr.current; 
            }
            return this->current;
        }

        bool operator!=(ForwardIterator<T> neqItr){
            return this->current != neqItr.current;
        }

        ForwardIterator<T> operator++(){
            if(this->current == nullptr){
                throw out_of_range("ForwardIterator is not initialized.");
            }
            else{
                this->current = this->current->next;
                return this->current;
            }
        }

        T operator*(){
            if(this->current == nullptr){
                throw out_of_range("ForwardIterator is not initialized.");
            }
            return this->current->data;
        }
};

#endif